#include "../../../pymod_shared.inc"

import os.path

module_type = 'lib-shared'
module_name = 'python{}bz2'.format(BUNDLED_PYTHON_VERSION)

build_list = ['bz2module.c']
export = ['initbz2']

src_search_dir_list = [
  '../../../vendor/Modules'
]

if os.path.isdir(os.path.join(BUILDSYS_MAKEFILE_DIRNAME, '../../../config')):
    include_dir_list += [ '../../../config']

include_dir_list += [
  '../../../vendor/Include',
  '${@project_root}/bzip2/include',
]

lib_list = [
  '../../core',
  '${@project_root}/bzip2',
]
