#include "../../../pymod_shared.inc"

module_type = 'lib-shared'
module_name = 'python{}_bz2'.format(BUNDLED_PYTHON_VERSION)

build_list = ['_bz2module.c']
export = ['PyInit__bz2']

src_search_dir_list = [
  '../../../vendor/Modules'
]

include_dir_list = [
  '../../../vendor/Include',
  '../../../config',
  '${@project_root}/bzip2/include',
]

lib_list = [
  '../../core',
  '${@project_root}/bzip2',
]
