#include "../../../pymod_shared.inc"

module_type = 'lib-shared'
module_name = 'python{}_socket'.format(BUNDLED_PYTHON_VERSION)

build_list = ['socketmodule.c']
export = ['init_socket']

src_search_dir_list = [
  '../../../vendor/Modules'
]

include_dir_list = [
  '../../../config',
  '../../../vendor/Include',
]

lib_list = [
  '../../core',
]

prebuilt_lib_list_windows = ['ws2_32']
