#include "../../../pymod_shared.inc"

module_type = 'lib-shared'
module_name = 'python{}_testconsole'.format(BUNDLED_PYTHON_VERSION)

build_list = [
  'export.c',
]

export = ['PyInit__testconsole']

include_dir_list = [
  '../../../vendor/Include',
  '../../../config',
]

lib_list = [
  '../../core',
]
