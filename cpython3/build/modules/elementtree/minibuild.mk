#include "../../../pymod_shared.inc"

module_type = 'lib-shared'
module_name = 'python{}_elementtree'.format(BUNDLED_PYTHON_VERSION)

build_list = [
  '_elementtree.c',
]

export = ['PyInit__elementtree']

src_search_dir_list = [
  '../../../vendor/Modules'
]

include_dir_list = [
  '../../../vendor/Include',
  '../../../config',
  '../../../vendor/Modules/expat',
]

lib_list = [
  '../../core',
]

definitions += ['USE_PYEXPAT_CAPI']
