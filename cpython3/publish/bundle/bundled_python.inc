PYCORE_PROPERTIES = {}

if BUILDSYS_TARGET_PLATFORM == 'linux':
    PYCORE_PROPERTIES['subdir'] = 'shared'
    PY_INTERPRETER = '${@project_root}/cpython3/build/interpreter/shlib'
else:
    PY_INTERPRETER = '${@project_root}/cpython3/build/interpreter'

PY_INTERPRETER_PROPERTIES = {
  'strip-filename-prefix': 'python{}_'.format(BUNDLED_PYTHON_VERSION),
}

PYMOD_PROPERTIES = {
    'subdir': 'modules',
}

PYMOD_PROPERTIES_SITE = {
    'subdir': 'site-packages',
}

if BUILDSYS_TARGET_PLATFORM == 'windows':
    PYMOD_PROPERTIES['replace-ext'] = '.pyd'
    PYMOD_PROPERTIES_SITE['replace-ext'] = '.pyd'
    PYMOD_PROPERTIES['strip-filename-prefix'] = 'python{}'.format(BUNDLED_PYTHON_VERSION)
    PYMOD_PROPERTIES_SITE['strip-filename-prefix'] = 'python{}'.format(BUNDLED_PYTHON_VERSION)
else:
    PYMOD_PROPERTIES['replace-ext'] = '.so'
    PYMOD_PROPERTIES_SITE['replace-ext'] = '.so'
    PYMOD_PROPERTIES['strip-filename-prefix'] = 'libpython{}'.format(BUNDLED_PYTHON_VERSION)
    PYMOD_PROPERTIES_SITE['strip-filename-prefix'] = 'libpython{}'.format(BUNDLED_PYTHON_VERSION)


if BUILDSYS_TARGET_PLATFORM == 'linux':
    composite_spec += [
        ['${@project_root}/cpython3/build/interpreter/shlib/python', {'file': True, 'executable': True}]
    ]

if BUILDSYS_TARGET_PLATFORM == 'windows':
    composite_spec += [
        ['${@project_root}/cpython3/build/modules/overlapped', PYMOD_PROPERTIES],
    ]

composite_spec += [
  [PY_INTERPRETER, PY_INTERPRETER_PROPERTIES],
  ['${@project_root}/cpython3/build/core', PYCORE_PROPERTIES ],
  ['${@project_root}/cpython3/build/modules/ssl', PYMOD_PROPERTIES],
  ['${@project_root}/cpython3/build/modules/hashlib', PYMOD_PROPERTIES],
  ['${@project_root}/cpython3/build/modules/socket', PYMOD_PROPERTIES],
  ['${@project_root}/cpython3/build/modules/sqlite', PYMOD_PROPERTIES],
  ['${@project_root}/cpython3/build/modules/ctypes', PYMOD_PROPERTIES],
  ['${@project_root}/cpython3/build/modules/pyexpat', PYMOD_PROPERTIES],
  ['${@project_root}/cpython3/build/modules/elementtree', PYMOD_PROPERTIES],
  ['${@project_root}/cpython3/build/modules/multiprocessing', PYMOD_PROPERTIES],
  ['${@project_root}/cpython3/build/modules/select', PYMOD_PROPERTIES],
  ['${@project_root}/cpython3/build/modules/unicodedata', PYMOD_PROPERTIES],
  ['${@project_root}/cpython3/build/modules/bz2', PYMOD_PROPERTIES],
  ['${@project_root}/cpython3/build/modules/crypt', PYMOD_PROPERTIES],
  ['${@project_root}/cpython3/build/modules/asyncio', PYMOD_PROPERTIES],
  ['${@project_root}/cpython3/build/modules/contextvars', PYMOD_PROPERTIES],
  ['${@project_root}/cpython3/build/modules/decimal', PYMOD_PROPERTIES],
  ['${@project_root}/cpython3/build/modules/lzma', PYMOD_PROPERTIES],
  ['${@project_root}/cpython3/build/modules/queue', PYMOD_PROPERTIES],
]
