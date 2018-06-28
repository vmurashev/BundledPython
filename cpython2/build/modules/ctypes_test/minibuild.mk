#include "../../../pymod_shared.inc"

module_type = 'lib-shared'
module_name = 'python{}_ctypes_test'.format(BUNDLED_PYTHON_VERSION)

build_list = [
  '_ctypes_test.c',
]

src_search_dir_list = [
  '../../../vendor/Modules/_ctypes',
]

include_dir_list = [
  '../../../config',
  '../../../vendor/Include',
]

lib_list = [
  '../../core',
]

prebuilt_lib_list_windows = ['oleaut32']