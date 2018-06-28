#include "../../../../py_version.inc"

module_type = 'lib-static'
module_name = 'python{}bz2_static'.format(BUNDLED_PYTHON_VERSION)

build_list = [
  'bz2module.c'
]

src_search_dir_list = [
  '../../../../vendor/Modules',
]

include_dir_list = [
  '../../../../config',
  '../../../../vendor/Include',
  '${@project_root}/bzip2/include',
]
