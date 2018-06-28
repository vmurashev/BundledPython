#include "../../../pymod_shared.inc"

module_type = 'lib-shared'
module_name = 'python{}_ctypes'.format(BUNDLED_PYTHON_VERSION)

build_list = [
  'callbacks.c',
  'callproc.c',
  'cfield.c',
  'malloc_closure.c',
  'stgdict.c',
  '_ctypes.c',
]

export = ['init_ctypes']

src_search_dir_list = [
  '../../../vendor/Modules/_ctypes'
]

include_dir_list = [
  '../../../config',
  '../../../vendor/Include',
  '${@project_root}/pyffi/include',
]

lib_list = [
  '../../core',
  '${@project_root}/pyffi', 
]

prebuilt_lib_list_linux = ['dl']
prebuilt_lib_list_windows = ['ole32','oleaut32']
