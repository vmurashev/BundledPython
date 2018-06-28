#include "../../py_version.inc"

#include "bundled_python.inc"

module_type = 'composite'
module_name = 'bundled_python{}'.format(BUNDLED_PYTHON_VERSION)

composite_spec += [
  ['../../build/stdlib', PYCORE_PROPERTIES ],
]
