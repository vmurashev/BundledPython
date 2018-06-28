#include "../../../pymod_shared.inc"

module_type = 'lib-shared'
module_name = 'python{}pyexpat'.format(BUNDLED_PYTHON_VERSION)

build_list = [
  'xmlparse.c',
  'xmlrole.c',
  'xmltok.c',
  'pyexpat.c',
]

build_list_windows = [
  'loadlibrary.c'
]

export = ['initpyexpat']

src_search_dir_list = [
  '../../../vendor/Modules',
  '../../../vendor/Modules/expat',
]

include_dir_list = [
  '../../../config',
  '../../../vendor/Include',
  '../../../vendor/Modules/expat',
]

lib_list = [
  '../../core',
]

definitions_windows = ['UNICODE', 'XML_STATIC']
definitions_linux = ['HAVE_EXPAT_CONFIG_H', 'XML_DEV_URANDOM', 'XML_STATIC']
definitions_macosx = ['HAVE_EXPAT_CONFIG_H', 'HAVE_ARC4RANDOM_BUF', 'XML_STATIC']
