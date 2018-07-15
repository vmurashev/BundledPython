#include "../../../pymod_shared.inc"

import os.path

module_type = 'lib-shared'
module_name = 'python{}_testcapi'.format(BUNDLED_PYTHON_VERSION)

build_list = [
  '_testcapimodule.c',
]

export = ['init_testcapi']

src_search_dir_list = [
  '../../../vendor/Modules',
]

if os.path.isdir(os.path.join(BUILDSYS_MAKEFILE_DIRNAME, '../../../config')):
    include_dir_list += [ '../../../config']

include_dir_list += [
  '../../../vendor/Include',
]

lib_list = [
  '../../core',
]
