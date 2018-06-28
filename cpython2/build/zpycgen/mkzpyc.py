import argparse
import json
import imp
import marshal
import os.path
import struct
import zipfile


def compile_data(py_data, codename, mtime):
    if type(mtime) is type(0.0):
        if mtime < 0x7fffffff:
            mtime = int(mtime)
        else:
            mtime = int(-0x100000000L + long(mtime))
    ast = compile(py_data, codename, 'exec', 0, 1)
    data = marshal.dumps(ast, marshal.version)
    pyc = imp.get_magic() + struct.pack("<i", int(mtime)) + data
    return pyc


def mkzpyc(zspec_fname):
    with open(zspec_fname) as fh:
        zspec = json.load(fh)
    zip_fname = zspec['zip_file']
    zip_catalog = zspec['spec_file']

    if not os.path.isabs(zip_fname):
        zspec_dname = os.path.dirname(zspec_fname)
        zip_fname = os.path.join(zspec_dname, zip_fname)
    zip_fname = os.path.normpath(zip_fname)
    if not os.path.exists(zip_fname):
        raise Exception("Zip file not found: {}".format(zip_fname))
    if not zipfile.is_zipfile(zip_fname):
        raise Exception("Not a zip file: {}".format(zip_fname))

    with zipfile.ZipFile(zip_fname, "a", zipfile.ZIP_DEFLATED) as fzip:
        for fsrc, arcname in zip_catalog:
            if not arcname.endswith('.py'):
                continue
            with open(fsrc, mode='rb') as fh:
                py_data = fh.read()
            st = os.stat(fsrc)
            py_obj = compile_data(py_data, arcname, st.st_mtime)
            pyc_name = ''.join([os.path.splitext(arcname)[0], '.pyc'])
            fzip.writestr(pyc_name, py_obj)


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--zipspec', required=True)
    args = parser.parse_args()
    mkzpyc(args.zipspec)


if __name__ == '__main__':
    main()
