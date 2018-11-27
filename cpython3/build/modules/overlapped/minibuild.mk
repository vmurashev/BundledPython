#include "../../../pymod_shared.inc"

module_type = 'lib-shared'
module_name = 'python{}_overlapped'.format(BUNDLED_PYTHON_VERSION)

build_list = [
  'overlapped.c',
]

export = ['PyInit__overlapped']

src_search_dir_list = [
  '../../../vendor/Modules',
]

include_dir_list = [
  '../../../vendor/Include',
  '../../../config',
]

lib_list = [
  '../../core',
]

prebuilt_lib_list_windows = ['ws2_32']
