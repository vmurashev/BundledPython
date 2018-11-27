#include "../../../pymod_shared.inc"

module_type = 'lib-shared'
module_name = 'python{}_testcapi'.format(BUNDLED_PYTHON_VERSION)

build_list = [
  '_testcapimodule.c',
]

export = ['PyInit__testcapi']

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
