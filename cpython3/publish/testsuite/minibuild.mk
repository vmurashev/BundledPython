#include "../../py_version.inc"
#include "../bundle/bundled_python.inc"

module_type = 'composite'
module_name = 'bundled_python{}_testsuite'.format(BUNDLED_PYTHON_VERSION)

if 'subdir' in PYCORE_PROPERTIES:
   PYSTDLIB_SUBDIR = '{}/python{}'.format(PYCORE_PROPERTIES['subdir'], BUNDLED_PYTHON_VERSION_DOT)
else:
   PYSTDLIB_SUBDIR = 'python{}'.format(BUNDLED_PYTHON_VERSION_DOT)

composite_spec += [
    ['stdlib_testsuite.inc', {'file': True, 'spec_file': True, 'subdir': PYSTDLIB_SUBDIR}],
    ['${@project_root}/cpython3/build/modules/testcapi', PYMOD_PROPERTIES],
    ['${@project_root}/cpython3/build/modules/ctypes_test', PYMOD_PROPERTIES],
    ['${@project_root}/cpython3/build/modules/testimportmultiple', PYMOD_PROPERTIES],
    ['${@project_root}/cpython3/build/modules/testmultiphase', PYMOD_PROPERTIES],
]

if BUILDSYS_TARGET_PLATFORM == 'windows':
    composite_spec += [
        ['${@project_root}/cpython3/build/modules/testconsole', PYMOD_PROPERTIES],
    ]
