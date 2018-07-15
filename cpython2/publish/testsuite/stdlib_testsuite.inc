[
    {
        'dirname': '../../vendor/Lib',
        'exclude-dir': {
            'if-arcname-startswith': ['plat-'],
            'if-arcname-equals': ['bsddb', 'curses', 'distutils', 'ensurepip', 'idlelib', 'lib2to3', 'msilib', 'lib-tk', 'pydoc_data', 'tkinter',
            ],
        },
        'exclude-file': {
            'if-arcpath-equals': ['this.py', 'site.py', 'sysconfig.py', '__phello__.foo.py', '_osx_support.py', 'dbhash.py', 'antigravity.py', 'user.py',
                'wsgiref.egg-info',
                'pdb.doc',
                'test/test_crypt.py',
                'test/test_platform.py',
                'test/test_signal.py',
                'test/test__osx_support.py',
                'test/test_distutils.py',
                'test/test_ensurepip.py',
                'test/test_lib2to3.py',
                'test/test_py3kwarn.py',
                'test/test_site.py',
                'test/test_sundry.py',
                'test/test_sysconfig.py',
                'test/test_bsddb.py',
                'test/test_bsddb185.py',
                'test/test_bsddb3.py',
                'test/test_dbm.py',
                'test/test_gdbm.py',
                'test/test_gdb.py',
                'test/test_idle.py',
                'test/test_msilib.py',
                'test/test_readline.py',
                'test/test_tcl.py',
                'test/test_tk.py',
                'test/test_tools.py',
                'test/test_ttk_guionly.py',
                'test/test_ttk_textonly.py',
                'test/test_turtle.py',

                'test/test_al.py',
                'test/test_cd.py',
                'test/test_cl.py',
                'test/test_dl.py',
                'test/test_gl.py',
                'test/test_aepack.py',
                'test/test_applesingle.py',
                'test/test_imageop.py',
                'test/test_imgfile.py',
                'test/test_linuxaudiodev.py',
                'test/test_macos.py',
                'test/test_macostools.py',
                'test/test_ossaudiodev.py',
                'test/test_sunaudiodev.py',
                'test/test_winsound.py',
                'test/test_scriptpackages.py',
                'test/test_curses.py',
                'test/test_zipfile64.py',
            ]
        }
    },
    {
        'catalog': ['site.py', 'sysconfig.py', '_sysconfigdata.py', '_sitebuiltins.py'],
        'dirname': '../../build/stdlib',
    },
    {
        'catalog': ['crypt.py', 'test/test_crypt.py'],
        'dirname': '../../build/modules/crypt',
    },
]