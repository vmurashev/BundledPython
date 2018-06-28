#include "../../../../py_version.inc"

module_type = 'lib-static'
module_name = 'python{}_crypt_static'.format(BUNDLED_PYTHON_VERSION)

build_list = [
  'cryptmodule.c',
]

src_search_dir_list = ['..']

include_dir_list = [
  '../../../../config',
  '../../../../vendor/Include',
  '${@project_root}/openssl_posix_crypt',
  '${@project_root}/openssl/include',
]
