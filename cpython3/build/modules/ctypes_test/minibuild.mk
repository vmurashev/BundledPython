#include "../../../pymod_shared.inc"

module_type = 'lib-shared'
module_name = 'python{}_ctypes_test'.format(BUNDLED_PYTHON_VERSION)

if BUILDSYS_TOOLSET_NAME == 'msvs': 
    export = ['PyInit__ctypes_test']
else:
    symbol_visibility_default = 1

build_list = [
  '_ctypes_test.c',
]

src_search_dir_list = [
  '../../../vendor/Modules/_ctypes',
]

include_dir_list = [
  '../../../vendor/Include',
  '../../../config',
]

lib_list = [
  '../../core',
]

prebuilt_lib_list_windows = ['oleaut32']
