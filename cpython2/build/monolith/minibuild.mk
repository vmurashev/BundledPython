#include "../../py_version.inc"

module_type = 'executable'
module_name = 'python{}_static'.format(BUNDLED_PYTHON_VERSION)

build_list = ['interpreter.c']
win_console = 1
win_stack_size = 2000000

include_dir_list = [
  '../../config',
  '../../vendor/Include',
]

lib_list = [
  '../core/static',
  '../stdlib/static',
  '../modules/ctypes/static',
  '../modules/elementtree/static',
  '../modules/hashlib/static',
  '../modules/multiprocessing/static',
  '../modules/socket/static',
  '../modules/ssl/static',
  '../modules/sqlite/static',
  '../modules/pyexpat/static',
  '../modules/select/static',
  '../modules/unicodedata/static',
  '../modules/bz2/static',
  '../modules/crypt/static',
  '${@project_root}/zlib',
  '${@project_root}/pyffi',
  '${@project_root}/openssl/build/crypto_static',
  '${@project_root}/openssl/build/ssl_static',
  '${@project_root}/openssl_posix_crypt/contrib/static',
  '${@project_root}/sqlcipher/src',
  '${@project_root}/bzip2',
]

explicit_depends = ['resource']
zip_section = '${@project_output}/obj/pymonolith_zrc/noarch/zsection.zip'

definitions_windows = ['Py_NO_ENABLE_SHARED']
prebuilt_lib_list_windows = ['advapi32', 'user32', 'shell32', 'ole32', 'oleaut32', 'crypt32', 'ws2_32']
prebuilt_lib_list_linux = ['dl', 'pthread', 'util', 'nsl']
macosx_framework_list = ['CoreFoundation', 'SystemConfiguration']
