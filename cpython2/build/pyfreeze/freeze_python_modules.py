from __future__ import print_function
import argparse
import json
import os.path
import marshal


def assemble_source(co_fname, mangled, source_file, output):
    with open(source_file, mode='rb') as source:
        py_data = source.read()
    ast = compile(py_data, co_fname, 'exec', 0, 1)
    code = marshal.dumps(ast)
    output.write('unsigned char {0}[] = {{'.format(mangled))
    for i in range(0, len(code), 16):
        output.write('\n    ')
        for c in code[i:i+16]:
            output.write('{: >3d}, '.format(ord(c)))
    output.write('\n};\n')
    return len(code)


class ModuleInfo:
    def __init__(self, py_name, c_name, frozen_size):
        self.py_name = py_name
        self.c_name = c_name
        self.frozen_size = frozen_size


def freeze_python_modules(freeze_spec_fname, output_dir):
    with open(freeze_spec_fname) as fh:
        freeze_spec = json.load(fh)
    var_name_for_export = freeze_spec['pyfreeze_export']
    fname_prefix = freeze_spec.get('pyfreeze_file_prefix', 'py')
    entries = freeze_spec['spec_file']

    inittab = []
    with open(os.path.join(output_dir, fname_prefix + '_frozen_impl.c'), mode='w') as fh:
        for source_file, fpath in entries:
            fbits = fpath.split('/')
            is_package = False
            if len(fbits) > 1 and fbits[-1] == '__init__.py':
                is_package = True
                mod_name = '.'.join(fbits[0: len(fbits) - 1])
            else:
                modbits = fbits[:]
                modbits[-1] = modbits[-1].partition('.')[0]
                mod_name = '.'.join(modbits)
            mangled = 'M_{}'.format(mod_name.replace('.', '_'))

            print('processing {} ...'.format(fpath))
            frozen_size = assemble_source(fpath, mangled, source_file, fh)
            if is_package:
                frozen_size = -frozen_size

            m = ModuleInfo(py_name=mod_name, c_name=mangled, frozen_size=frozen_size)
            inittab.append(m)

    with open(os.path.join(output_dir, fname_prefix + '_frozen.c'), mode='w') as fh:
        fh.write('#include <Python.h>\n\n')
        for m in inittab:
            fh.write('extern unsigned char {}[];\n'.format(m.c_name))
        fh.write('\nstruct _frozen ' + var_name_for_export + '[] = {\n')
        for m in inittab:
            fh.write('    {{"{}", {}, {}}},\n'.format(m.py_name, m.c_name, m.frozen_size))
        fh.write('    {0, 0, 0} /* sentinel */\n')
        fh.write('};\n')

    with open(os.path.join(output_dir, fname_prefix + '_frozen.h'), mode='w') as fh:
        fh.write('#pragma once\n')
        fh.write('#include <Python.h>\n\n')
        fh.write('extern struct _frozen ' + var_name_for_export + '[];\n')


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('--freeze-spec', required=True)
    parser.add_argument('--output-dir', required=True)
    args = parser.parse_args()

    freeze_python_modules(args.freeze_spec, args.output_dir)
