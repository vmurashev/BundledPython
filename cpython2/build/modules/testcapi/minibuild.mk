#include "../../../pymod_shared.inc"

module_type = 'lib-shared'
module_name = 'python{}_testcapi'.format(BUNDLED_PYTHON_VERSION)

build_list = [
  '_testcapimodule.c',
]

export = ['init_testcapi']

src_search_dir_list = [
  '../../../vendor/Modules',
]

include_dir_list = [
  '../../../config',
  '../../../vendor/Include',
]

lib_list = [
  '../../core',
]
