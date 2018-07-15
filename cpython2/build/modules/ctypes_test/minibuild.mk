#include "../../../pymod_shared.inc"

import os.path

module_type = 'lib-shared'
module_name = 'python{}_ctypes_test'.format(BUNDLED_PYTHON_VERSION)

build_list = [
  '_ctypes_test.c',
]

src_search_dir_list = [
  '../../../vendor/Modules/_ctypes',
]

if os.path.isdir(os.path.join(BUILDSYS_MAKEFILE_DIRNAME, '../../../config')):
    include_dir_list += [ '../../../config']

include_dir_list += [
  '../../../vendor/Include',
]

lib_list = [
  '../../core',
]

prebuilt_lib_list_windows = ['oleaut32']