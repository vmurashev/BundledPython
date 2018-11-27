#include "../../../pymod_shared.inc"

module_type = 'lib-shared'
module_name = 'python{}_testmultiphase'.format(BUNDLED_PYTHON_VERSION)

build_list = [
  '_testmultiphase.c',
]

export = [
    'PyInit__testmultiphase',
    'PyInit__testmultiphase_nonmodule',
    'PyInit__testmultiphase_nonmodule_with_methods',
    'PyInitU__testmultiphase_zkouka_naten_evc07gi8e',
    'PyInitU_eckzbwbhc6jpgzcx415x',
    'PyInit_x',
    'PyInit__testmultiphase_null_slots',
    'PyInit__testmultiphase_bad_slot_large',
    'PyInit__testmultiphase_bad_slot_negative',
    'PyInit__testmultiphase_create_int_with_state',
    'PyInit__testmultiphase_negative_size',
    'PyInit__testmultiphase_export_uninitialized',
    'PyInit__testmultiphase_export_null',
    'PyInit__testmultiphase_export_raise',
    'PyInit__testmultiphase_export_unreported_exception',
    'PyInit__testmultiphase_create_null',
    'PyInit__testmultiphase_create_raise',
    'PyInit__testmultiphase_create_unreported_exception',
    'PyInit__testmultiphase_nonmodule_with_exec_slots',
    'PyInit__testmultiphase_exec_err',
    'PyInit__testmultiphase_exec_raise',
    'PyInit__testmultiphase_exec_unreported_exception',
    'PyInit__testmultiphase_with_bad_traverse',
    'PyInit_imp_dummy',
]

src_search_dir_list = [
  '../../../vendor/Modules',
]

include_dir_list = [
  '../../../vendor/Include',
  '../../../config',
]

lib_list = [
  '../../core',
]
