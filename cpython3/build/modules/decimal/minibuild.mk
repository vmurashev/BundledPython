#include "../../../pymod_shared.inc"

module_type = 'lib-shared'
module_name = 'python{}_decimal'.format(BUNDLED_PYTHON_VERSION)

build_list = [
  '_decimal.c',
]

export = ['PyInit__decimal']

src_search_dir_list = [
  '../../../vendor/Modules/_decimal',
]

include_dir_list = [
  '../../../vendor/Include',
  '../../../config',
  '${@project_root}/mpdecimal/include',
]

lib_list = [
  '../../core',
  '${@project_root}/mpdecimal',
]
