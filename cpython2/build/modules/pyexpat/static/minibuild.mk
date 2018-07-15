#include "../../../../py_version.inc"

import os.path

module_type = 'lib-static'
module_name = 'python{}pyexpat_static'.format(BUNDLED_PYTHON_VERSION)

build_list = [
  'xmlparse.c',
  'xmlrole.c',
  'xmltok.c',
  'pyexpat.c',
]

build_list_windows = [
  'loadlibrary.c'
]

src_search_dir_list = [
  '../../../../vendor/Modules',
  '../../../../vendor/Modules/expat',
]

if os.path.isdir(os.path.join(BUILDSYS_MAKEFILE_DIRNAME, '../../../../config')):
    include_dir_list += [ '../../../../config']

include_dir_list += [
  '../../../../vendor/Include',
  '../../../../vendor/Modules/expat',
]

definitions_windows = ['UNICODE', 'XML_STATIC']
definitions_linux = ['HAVE_EXPAT_CONFIG_H', 'XML_DEV_URANDOM', 'XML_STATIC']
definitions_macosx = ['HAVE_EXPAT_CONFIG_H', 'HAVE_ARC4RANDOM_BUF', 'XML_STATIC']
