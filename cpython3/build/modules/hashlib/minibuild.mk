#include "../../../pymod_shared.inc"

module_type = 'lib-shared'
module_name = 'python{}_hashlib'.format(BUNDLED_PYTHON_VERSION)

build_list = ['_hashopenssl.c']
export = ['PyInit__hashlib']

src_search_dir_list = [
  '../../../vendor/Modules'
]

include_dir_list = [
  '../../../vendor/Include',
  '../../../config',
  '${@project_root}/openssl/include',
]

lib_list = [
  '../../core',
  '${@project_root}/openssl/build/crypto_static',
  '${@project_root}/zlib',
]

prebuilt_lib_list_windows = ['crypt32','ws2_32', 'advapi32', 'user32']
prebuilt_lib_list_linux = ['dl', 'pthread']
