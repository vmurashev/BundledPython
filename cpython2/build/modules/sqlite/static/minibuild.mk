#include "../../../../py_version.inc"

module_type = 'lib-static'
module_name = 'python{}_sqlite3_static'.format(BUNDLED_PYTHON_VERSION)

src_search_dir_list = [
  '../../../../vendor/Modules/_sqlite'
]

build_list = [
  'cache.c',
  'connection.c',
  'cursor.c',
  'microprotocols.c',
  'module.c',
  'prepare_protocol.c',
  'row.c',
  'statement.c',
  'util.c',
]

include_dir_list = [
  '../../../../config',
  '../../../../vendor/Include',
  '${@project_root}/sqlcipher/include',
]

definitions += ['MODULE_NAME="sqlite3"']
