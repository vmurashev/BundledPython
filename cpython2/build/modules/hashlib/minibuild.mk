#include "../../../pymod_shared.inc"

import os.path

module_type = 'lib-shared'
module_name = 'python{}_hashlib'.format(BUNDLED_PYTHON_VERSION)

build_list = ['_hashopenssl.c']
export = ['init_hashlib']

src_search_dir_list = [
  '../../../vendor/Modules'
]

if os.path.isdir(os.path.join(BUILDSYS_MAKEFILE_DIRNAME, '../../../config')):
    include_dir_list += [ '../../../config']

include_dir_list += [
  '../../../vendor/Include',
  '${@project_root}/openssl/include',
]

lib_list = [
  '../../core',
  '${@project_root}/openssl/build/crypto_static',
  '${@project_root}/zlib',
]

prebuilt_lib_list_windows = ['crypt32','ws2_32', 'advapi32', 'user32']
prebuilt_lib_list_linux = ['dl', 'pthread']
