#include "../../../../py_version.inc"

import os.path

module_type = 'lib-static'
module_name = 'python{}_socket_static'.format(BUNDLED_PYTHON_VERSION)

build_list = ['socketmodule.c']

src_search_dir_list = [
  '../../../../vendor/Modules'
]

if os.path.isdir(os.path.join(BUILDSYS_MAKEFILE_DIRNAME, '../../../../config')):
    include_dir_list += [ '../../../../config']

include_dir_list += [
  '../../../../vendor/Include',
]
