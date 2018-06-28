#include "../../py_version.inc"
#include "build_list.inc"

module_type = 'lib-shared'
module_name = 'python{}'.format(BUNDLED_PYTHON_VERSION)

include_dir_list = [
  'pc_clinic',
  '../../config',
  '../../vendor/Include',
  '../../vendor/Python',
  '${@project_root}/zlib/include',
]

src_search_dir_list = [
  'pc_clinic',
  '../../vendor/Python',
  '../../vendor/Parser',
  '../../vendor/Objects',
  '../../vendor/Modules',
  '../../vendor/Modules/cjkcodecs',
  '../../vendor/Modules/_io',
  '../../vendor/Mac/Modules',
]

definitions = ['Py_BUILD_CORE', 'Py_ENABLE_SHARED', 'NDEBUG']
definitions_windows = ['PLATFORM="win32"']
definitions_linux = ['PLATFORM="linux2"']
definitions_macosx = ['PLATFORM="darwin"']

lib_list = ['${@project_root}/zlib']

prebuilt_lib_list_windows = ['advapi32','user32', 'shell32']
prebuilt_lib_list_linux = ['dl', 'pthread', 'util', 'nsl']
macosx_framework_list = ['CoreFoundation', 'SystemConfiguration']
