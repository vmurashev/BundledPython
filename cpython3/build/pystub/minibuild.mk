#include "../../py_version.inc"

module_type = 'composite'
module_name = 'pystub{}'.format(BUNDLED_PYTHON_VERSION)

PYCORE_PROPERTIES = {}

if BUILDSYS_TARGET_PLATFORM == 'linux':
    PYCORE_PROPERTIES['subdir'] = 'shared'
    PY_INTERPRETER = '../interpreter/shlib'
else:
    PY_INTERPRETER = '../interpreter'

PY_INTERPRETER_PROPERTIES = {
  'strip-filename-prefix': 'python{}_'.format(BUNDLED_PYTHON_VERSION),
}

if BUILDSYS_TARGET_PLATFORM == 'linux':
    composite_spec += [
        ['../interpreter/shlib/python', {'file': True, 'executable': True}]
    ]

composite_spec += [
  ['../core', PYCORE_PROPERTIES ],
  ['../stdlib/stub', PYCORE_PROPERTIES],
  [PY_INTERPRETER, PY_INTERPRETER_PROPERTIES],
]
