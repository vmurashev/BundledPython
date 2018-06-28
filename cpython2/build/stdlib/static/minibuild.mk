#include "../../../py_version.inc"
#import "../../pyfreeze"

module_type = 'lib-static'
module_name = 'python{}_stdlib_static'.format(BUNDLED_PYTHON_VERSION)

spec_file = '../stdlib.inc'
spec_post_build = ['pyfreeze']
spec_file_entails = {'pyfreeze_export': '_PyImport_FrozenStdlibModules'}

include_dir_list = [
  '../../../config',
  '../../../vendor/Include',
]

build_list = ['py_frozen.c', 'py_frozen_impl.c'] # auto-generated files via pyfreeze
