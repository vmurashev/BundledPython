#include "../../../pymod_shared.inc"

module_type = 'lib-shared'
module_name = 'python{}_sqlite3'.format(BUNDLED_PYTHON_VERSION)

export = ['PyInit__sqlite3']

src_search_dir_list = [
  '../../../vendor/Modules/_sqlite'
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
  '../../../vendor/Include',
  '../../../config',
  '${@project_root}/sqlcipher/include',
]

lib_list = [
  '../../core',
  '${@project_root}/sqlcipher/src',
  '${@project_root}/openssl/build/crypto_static',
  '${@project_root}/zlib',
]

definitions += ['MODULE_NAME="sqlite3"']

prebuilt_lib_list_windows = ['crypt32','ws2_32', 'advapi32', 'user32']
prebuilt_lib_list_linux = ['dl', 'pthread']
