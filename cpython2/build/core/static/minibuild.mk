#include "../build_list.inc"

import os.path

module_type = 'lib-static'
module_name = 'python_core_static'

if os.path.isdir(os.path.join(BUILDSYS_MAKEFILE_DIRNAME, '../pc_clinic')):
    include_dir_list += ['../pc_clinic']
    src_search_dir_list += ['../pc_clinic']
else:
    src_search_dir_list += ['../../vendor/PC']

if os.path.isdir(os.path.join(BUILDSYS_MAKEFILE_DIRNAME, '../../../config')):
    include_dir_list += [ '../../../config']


include_dir_list += [
  '../../../vendor/Include',
  '../../../vendor/Python',
  '${@project_root}/zlib/include',
]

src_search_dir_list += [
  '..',
  '../../../vendor/Python',
  '../../../vendor/Parser',
  '../../../vendor/Objects',
  '../../../vendor/Modules',
  '../../../vendor/Modules/cjkcodecs',
  '../../../vendor/Modules/_io',
  '../../../vendor/Mac/Modules',
]

definitions = ['Py_BUILD_CORE', 'NDEBUG']
definitions_windows = ['PLATFORM="win32"', 'Py_NO_ENABLE_SHARED']
definitions_linux = ['PLATFORM="linux2"']
definitions_macosx = ['PLATFORM="darwin"']
