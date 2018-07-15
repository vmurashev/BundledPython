#include "../../../../py_version.inc"

import os.path

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

if os.path.isdir(os.path.join(BUILDSYS_MAKEFILE_DIRNAME, '../../../../config')):
    include_dir_list += [ '../../../../config']

include_dir_list += [
  '../../../../vendor/Include',
]
