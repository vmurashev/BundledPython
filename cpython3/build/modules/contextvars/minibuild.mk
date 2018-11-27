#include "../../../pymod_shared.inc"

module_type = 'lib-shared'
module_name = 'python{}_contextvars'.format(BUNDLED_PYTHON_VERSION)

build_list = [
  '_contextvarsmodule.c',
]

export = ['PyInit__contextvars']

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
