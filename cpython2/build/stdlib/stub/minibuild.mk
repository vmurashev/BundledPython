#include "../../../py_version.inc"

module_type = 'zip-file'
module_name = 'python{}_zipped_stdlib_stub'.format(BUNDLED_PYTHON_VERSION)

zip_file = 'python{}.zip'.format(BUNDLED_PYTHON_VERSION)
spec_file = '../stdlib.inc'
