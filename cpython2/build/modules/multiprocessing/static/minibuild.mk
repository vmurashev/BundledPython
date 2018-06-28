#include "../../../../py_version.inc"

module_type = 'lib-static'
module_name = 'python{}_multiprocessing_static'.format(BUNDLED_PYTHON_VERSION)

build_list = [
  'socket_connection.c',
  'multiprocessing.c',
  'semaphore.c',
]

build_list_windows = [
  'win32_functions.c',
  'pipe_connection.c',
]

src_search_dir_list = [
  '../../../../vendor/Modules/_multiprocessing',
]

include_dir_list = [
  '../../../../config',
  '../../../../vendor/Include',
]
