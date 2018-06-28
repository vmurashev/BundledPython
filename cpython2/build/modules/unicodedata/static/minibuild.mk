#include "../../../../py_version.inc"

module_type = 'lib-static'
module_name = 'python{}unicodedata_static'.format(BUNDLED_PYTHON_VERSION)

build_list = [
  'unicodedata.c',
]

src_search_dir_list = [
  '../../../../vendor/Modules',
]

include_dir_list = [
  '../../../../config',
  '../../../../vendor/Include',
]
