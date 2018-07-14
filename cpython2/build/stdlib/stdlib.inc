[
    {
        'dirname': '../../vendor/Lib',
        'exclude-dir': {
            'if-arcname-startswith': ['plat-'],
            'if-arcname-equals': ['bsddb', 'curses', 'distutils', 'ensurepip', 'idlelib', 'lib2to3', 'msilib', 'lib-tk', 'pydoc_data', 'tkinter',
                'test', 'tests', 'site-packages',
             ],
        },
        'exclude-file': {
            'if-not-arcname-endswith': ['.py'],
            'if-arcpath-equals': ['this.py', 'site.py', 'sysconfig.py', '__phello__.foo.py', '_osx_support.py', 'dbhash.py', 'antigravity.py', 'user.py',
            ]
        }
    },
    {
        'catalog': ['site.py', 'sysconfig.py', '_sysconfigdata.py', '_sitebuiltins.py'],
        'dirname': '.',
    },
    {
        'catalog': ['crypt.py'],
        'dirname': '../modules/crypt',
    },
]
