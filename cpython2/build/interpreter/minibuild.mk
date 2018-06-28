#include "../../py_version.inc"

module_type = 'executable'
module_name = 'python{}_python'.format(BUNDLED_PYTHON_VERSION)

build_list_windows = ['interpreter_winapi.c']
build_list_posix = ['interpreter_posix.c']

definitions_windows = ['PYTHON_DSO_REL_PATH=L"python{}.dll"'.format(BUNDLED_PYTHON_VERSION)]
definitions_posix = ['PYTHON_DSO_REL_PATH="libpython{}.so"'.format(BUNDLED_PYTHON_VERSION)]

prebuilt_lib_list_linux = ['dl']
win_console = 1
win_stack_size = 2000000
