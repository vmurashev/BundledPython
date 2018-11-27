build_list += [
  'config_universal.c',
  'getpath_universal.c',
]

# Python
build_list += [
  '_warnings.c',
  'asdl.c',
  'ast.c',
  'ast_unparse.c',
  'ast_opt.c',
  'bltinmodule.c',
  'bootstrap_hash.c',
  'ceval.c',
  'codecs.c',
  'compile.c',
  'context.c',
  'dynamic_annotations.c',
  'errors.c',
  'fileutils.c',
  'formatter_unicode.c',
  'frozen.c',
  'future.c',
  'getargs.c',
  'getcompiler.c',
  'getcopyright.c',
  'getopt.c',
  'getplatform.c',
  'getversion.c',
  'graminit.c',
  'hamt.c',
  'import.c',
  'importdl.c',
  'marshal.c',
  'modsupport.c',
  'mysnprintf.c',
  'mystrtoul.c',
  'pathconfig.c',
  'peephole.c',
  'pyarena.c',
  'pyctype.c',
  'pyfpe.c',
  'pyhash.c',
  'pylifecycle.c',
  'pymath.c',
  'pytime.c',
  'pystate.c',
  'pystrcmp.c',
  'pystrhex.c',
  'pystrtod.c',
  'dtoa.c',
  'Python-ast.c',
  'pythonrun.c',
  'structmember.c',
  'symtable.c',
  'sysmodule.c',
  'thread.c',
  'traceback.c',
]

# Parser
build_list += [
  'acceler.c',
  'bitset.c',
  'firstsets.c',
  'grammar.c',
  'grammar1.c',
  'listnode.c',
  'metagrammar.c',
  'myreadline.c',
  'node.c',
  'parser.c',
  'parsetok.c',
  'tokenizer.c'
]

# Objects
build_list += [
  'abstract.c',
  'accu.c',
  'boolobject.c',
  'bytes_methods.c',
  'bytearrayobject.c',
  'bytesobject.c',
  'call.c',
  'capsule.c',
  'cellobject.c',
  'classobject.c',
  'codeobject.c',
  'complexobject.c',
  'descrobject.c',
  'dictobject.c',
  'enumobject.c',
  'exceptions.c',
  'fileobject.c',
  'floatobject.c',
  'frameobject.c',
  'funcobject.c',
  'genobject.c',
  'iterobject.c',
  'listobject.c',
  'longobject.c',
  'memoryobject.c',
  'methodobject.c',
  'moduleobject.c',
  'namespaceobject.c',
  'object.c',
  'obmalloc.c',
  'odictobject.c',
  'rangeobject.c',
  'setobject.c',
  'sliceobject.c',
  'structseq.c',
  '_tracemalloc.c',
  'tupleobject.c',
  'typeobject.c',
  'unicodectype.c',
  'unicodeobject.c',
  'weakrefobject.c',
]

# Modules
build_list += [
  '_abc.c',
  'audioop.c',
  '_bisectmodule.c',
  '_codecsmodule.c',
  '_collectionsmodule.c',
  '_csv.c',
  '_functoolsmodule.c',
  'hashtable.c',
  '_heapqmodule.c',
  '_json.c',
  '_localemodule.c',
  '_lsprof.c',
  '_math.c',
  '_pickle.c',
  '_randommodule.c',
  '_sre.c',
  '_struct.c',
  '_weakref.c',
  'arraymodule.c',
  'atexitmodule.c',
  'binascii.c',
  'cmathmodule.c',
  '_datetimemodule.c',
  'errnomodule.c',
  'faulthandler.c',
  'gcmodule.c',
  'itertoolsmodule.c',
  'main.c',
  'mathmodule.c',
  'md5module.c',
  'mmapmodule.c',
  '_opcode.c',
  '_operator.c',
  'parsermodule.c',
  'posixmodule.c',
  'rotatingtree.c',
  'sha1module.c',
  'sha256module.c',
  'sha512module.c',
  'signalmodule.c',
  '_stat.c',
  'symtablemodule.c',
  '_threadmodule.c',
  'timemodule.c',
  'xxsubtype.c',
  'zipimport.c',
  'zlibmodule.c',
  'getbuildinfo.c',
]

# Modules/cjkcodecs
build_list += [
  '_codecs_cn.c',
  '_codecs_hk.c',
  '_codecs_iso2022.c',
  '_codecs_jp.c',
  '_codecs_kr.c',
  '_codecs_tw.c',
  'multibytecodec.c',
]

# Modules/_blake2
build_list += [
  'blake2b_impl.c',
  'blake2s_impl.c',
  'blake2module.c',
]

# Modules/_sha3
build_list += [
  'sha3module.c',
]

# Modules/_io
build_list += [
  '_iomodule.c',
  'textio.c',
  'iobase.c',
  'bufferedio.c',
  'stringio.c',
  'bytesio.c',
  'fileio.c',
]

build_list_windows += [
  'winreg.c',
  'dl_nt.c',
  'msvcrtmodule.c',
  'dynload_win.c',
  '_winapi.c',
  'invalid_parameter_handler.c',
  'winconsoleio.c',
]

build_list_posix += [
  'dynload_shlib.c',
  'fcntlmodule.c',
  '_posixsubprocess.c',
  'pwdmodule.c',
  'termios.c',
  'resource.c',
  'grpmodule.c',
  'syslogmodule.c',
  'nismodule.c',
]

if BUILDSYS_TARGET_PLATFORM != 'macosx':
    build_list_posix += [
      'spwdmodule.c',
    ]

build_list_macosx += [
  '_scproxy.c',
]
