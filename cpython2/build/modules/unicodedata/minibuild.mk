#include "../../../pymod_shared.inc"

import os.path

module_type = 'lib-shared'
module_name = 'python{}unicodedata'.format(BUNDLED_PYTHON_VERSION)

build_list = [
  'unicodedata.c',
]

export = ['initunicodedata']

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
