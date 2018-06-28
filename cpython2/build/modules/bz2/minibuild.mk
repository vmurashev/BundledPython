#include "../../../pymod_shared.inc"

module_type = 'lib-shared'
module_name = 'python{}bz2'.format(BUNDLED_PYTHON_VERSION)

build_list = ['bz2module.c']
export = ['initbz2']

src_search_dir_list = [
  '../../../vendor/Modules'
]

include_dir_list = [
  '../../../config',
  '../../../vendor/Include',
  '${@project_root}/bzip2/include',
]

lib_list = [
  '../../core',
  '${@project_root}/bzip2',
]
