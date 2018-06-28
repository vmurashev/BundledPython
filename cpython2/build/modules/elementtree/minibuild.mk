#include "../../../pymod_shared.inc"

module_type = 'lib-shared'
module_name = 'python{}_elementtree'.format(BUNDLED_PYTHON_VERSION)

build_list = [
  '_elementtree.c',
]

export = ['init_elementtree']

src_search_dir_list = [
  '../../../vendor/Modules'
]

include_dir_list = [
  '../../../config',
  '../../../vendor/Include',
  '../../../vendor/Modules/expat',
]

lib_list = [
  '../../core',
]

definitions += ['USE_PYEXPAT_CAPI']
