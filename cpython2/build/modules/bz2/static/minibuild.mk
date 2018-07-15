#include "../../../../py_version.inc"

import os.path

module_type = 'lib-static'
module_name = 'python{}bz2_static'.format(BUNDLED_PYTHON_VERSION)

build_list = [
  'bz2module.c'
]

src_search_dir_list = [
  '../../../../vendor/Modules',
]

if os.path.isdir(os.path.join(BUILDSYS_MAKEFILE_DIRNAME, '../../../../config')):
    include_dir_list += [ '../../../../config']

include_dir_list += [
  '../../../../vendor/Include',
  '${@project_root}/bzip2/include',
]
