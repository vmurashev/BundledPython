#include "../../../pymod_shared.inc"

module_type = 'lib-shared'
module_name = 'python{}_asyncio'.format(BUNDLED_PYTHON_VERSION)

build_list = [
  '_asynciomodule.c',
]

export = ['PyInit__asyncio']

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
