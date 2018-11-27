#include "../../../pymod_shared.inc"

module_type = 'lib-shared'
module_name = 'python{}_ssl'.format(BUNDLED_PYTHON_VERSION)

build_list = ['_ssl.c']
export = ['PyInit__ssl']

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
  '${@project_root}/openssl/build/ssl_static',
  '${@project_root}/openssl/build/crypto_static',
  '${@project_root}/zlib',
]

prebuilt_lib_list_windows = ['crypt32','ws2_32', 'advapi32', 'user32']
prebuilt_lib_list_linux = ['dl', 'pthread']
macosx_framework_list = ['CoreFoundation', 'Security']
