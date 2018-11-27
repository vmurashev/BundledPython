#include "../../../pymod_shared.inc"

module_type = 'lib-shared'
module_name = 'python{}_lzma'.format(BUNDLED_PYTHON_VERSION)

build_list = [
  '_lzmamodule.c',
]

export = ['PyInit__lzma']

src_search_dir_list = [
  '../../../vendor/Modules',
]

include_dir_list = [
  '../../../vendor/Include',
  '../../../config',
  '${@project_root}/xz/include',
]

lib_list = [
  '../../core',
  '${@project_root}/xz/build/static',
]
