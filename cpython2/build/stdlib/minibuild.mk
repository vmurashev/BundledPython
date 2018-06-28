#include "../../py_version.inc"
#import "../zpycgen"

module_type = 'zip-file'
module_name = 'python{}_zipped_stdlib'.format(BUNDLED_PYTHON_VERSION)

zip_file = 'python{}.zip'.format(BUNDLED_PYTHON_VERSION)
spec_file = 'stdlib.inc'
post_build = ['zpycgen']
