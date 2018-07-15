#include "../../../py_version.inc"

import os.path

module_type = 'executable'
module_name = 'python{}_python.bin'.format(BUNDLED_PYTHON_VERSION)

if os.path.isdir(os.path.join(BUILDSYS_MAKEFILE_DIRNAME, '../../../config')):
    include_dir_list += ['../../../config']

include_dir_list += [
  '../../../vendor/Include',
]

build_list = ['interpreter.c']

lib_list = [
  '../../core',
]
