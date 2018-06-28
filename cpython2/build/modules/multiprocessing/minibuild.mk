#include "../../../pymod_shared.inc"

module_type = 'lib-shared'
module_name = 'python{}_multiprocessing'.format(BUNDLED_PYTHON_VERSION)

build_list = [
  'socket_connection.c',
  'multiprocessing.c',
  'semaphore.c',
]

build_list_windows = [
  'win32_functions.c',
  'pipe_connection.c',
]

export = ['init_multiprocessing']

src_search_dir_list = [
  '../../../vendor/Modules/_multiprocessing',
]

include_dir_list = [
  '../../../config',
  '../../../vendor/Include',
]

lib_list = [
  '../../core',
]

prebuilt_lib_list_windows = ['ws2_32']
prebuilt_lib_list_linux = ['pthread']
