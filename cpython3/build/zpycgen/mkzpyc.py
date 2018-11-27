import argparse
import json
import imp
import io
import marshal
import os.path
import zipfile


def compile_data(py_data, codename, tmstamp, fsize):
    def wr_long(f, x):
        f.write(bytes([x & 0xff, (x >> 8)  & 0xff, (x >> 16) & 0xff, (x >> 24) & 0xff]))
    with io.BytesIO() as out:
        ast = compile(py_data, codename, 'exec')
        timestamp = int(tmstamp)
        size = fsize & 0xFFFFFFFF
        out.write(b'\0\0\0\0')
        wr_long(out, timestamp)
        wr_long(out, size)
        raw_data = marshal.dumps(ast, marshal.version)
        out.write(raw_data)
        out.flush()
        out.seek(0, 0)
        out.write(imp.get_magic())
        return out.getvalue()


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
            py_obj = compile_data(py_data, arcname, st.st_mtime, st.st_size)
            pyc_name = ''.join([os.path.splitext(arcname)[0], '.pyc'])
            fzip.writestr(pyc_name, py_obj)


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--zipspec', required=True)
    args = parser.parse_args()
    mkzpyc(args.zipspec)


if __name__ == '__main__':
    main()
