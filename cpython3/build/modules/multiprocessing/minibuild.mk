#include "../../../pymod_shared.inc"

module_type = 'lib-shared'
module_name = 'python{}_multiprocessing'.format(BUNDLED_PYTHON_VERSION)

build_list = [
  'multiprocessing.c',
  'semaphore.c',
]

export = ['PyInit__multiprocessing']

src_search_dir_list = [
  '../../../vendor/Modules/_multiprocessing',
]

include_dir_list = [
  '../../../vendor/Include',
  '../../../config',
]

lib_list = [
  '../../core',
]

prebuilt_lib_list_windows = ['ws2_32']
prebuilt_lib_list_linux = ['pthread']
