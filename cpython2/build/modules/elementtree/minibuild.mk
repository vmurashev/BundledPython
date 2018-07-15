#include "../../../pymod_shared.inc"

import os.path

module_type = 'lib-shared'
module_name = 'python{}_elementtree'.format(BUNDLED_PYTHON_VERSION)

build_list = [
  '_elementtree.c',
]

export = ['init_elementtree']

src_search_dir_list = [
  '../../../vendor/Modules'
]

if os.path.isdir(os.path.join(BUILDSYS_MAKEFILE_DIRNAME, '../../../config')):
    include_dir_list += [ '../../../config']

include_dir_list += [
  '../../../vendor/Include',
  '../../../vendor/Modules/expat',
]

lib_list = [
  '../../core',
]

definitions += ['USE_PYEXPAT_CAPI']
