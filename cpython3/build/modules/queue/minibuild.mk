#include "../../../pymod_shared.inc"

module_type = 'lib-shared'
module_name = 'python{}_queue'.format(BUNDLED_PYTHON_VERSION)

build_list = [
  '_queuemodule.c',
]

export = ['PyInit__queue']

src_search_dir_list = [
  '../../../vendor/Modules',
]

include_dir_list = [
  '../../../vendor/Include',
  '../../../config',
]

lib_list = [
  '../../core',
]
