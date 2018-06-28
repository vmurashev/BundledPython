#include "../../../../py_version.inc"

module_type = 'lib-static'
module_name = 'python{}_elementtree_static'.format(BUNDLED_PYTHON_VERSION)

build_list = [
  '_elementtree.c',
]

src_search_dir_list = [
  '../../../../vendor/Modules'
]

include_dir_list = [
  '../../../../config',
  '../../../../vendor/Include',
  '../../../../vendor/Modules/expat',
]

definitions += ['USE_PYEXPAT_CAPI']
