#include "../../../pymod_shared.inc"

module_type = 'lib-shared'
module_name = 'python{}_testimportmultiple'.format(BUNDLED_PYTHON_VERSION)

build_list = [
  '_testimportmultiple.c',
]

export = ['PyInit__testimportmultiple', 'PyInit__testimportmultiple_foo', 'PyInit__testimportmultiple_bar']

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
