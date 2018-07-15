#include "../../../../py_version.inc"

import os.path

module_type = 'lib-static'
module_name = 'python{}_ctypes_static'.format(BUNDLED_PYTHON_VERSION)

build_list = [
  'callbacks.c',
  'callproc.c',
  'cfield.c',
  'malloc_closure.c',
  'stgdict.c',
  '_ctypes.c',
]

src_search_dir_list = [
  '../../../../vendor/Modules/_ctypes'
]

if os.path.isdir(os.path.join(BUILDSYS_MAKEFILE_DIRNAME, '../../../../config')):
    include_dir_list += [ '../../../../config']

include_dir_list += [
  '../../../../vendor/Include',
  '${@project_root}/pyffi/include', 
]
