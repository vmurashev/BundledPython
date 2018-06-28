#include <Python.h>

extern struct _frozen _PyImport_FrozenStdlibModules[];

extern void init_ctypes(void);
extern void init_elementtree(void);
extern void init_hashlib(void);
extern void init_multiprocessing(void);
extern void init_socket(void);
extern void init_ssl(void);
extern void init_sqlite3(void);
extern void initpyexpat(void);
extern void initselect(void);
extern void initunicodedata(void);
extern void initbz2(void);
extern void init_crypt(void);

static struct _inittab extensions[] = {
  {"_ctypes", init_ctypes},
  {"_elementtree", init_elementtree},
  {"_hashlib", init_hashlib},
  {"_multiprocessing", init_multiprocessing},
  {"_socket", init_socket},
  {"_ssl", init_ssl},
  {"_sqlite3", init_sqlite3},
  {"pyexpat", initpyexpat},
  {"select", initselect},
  {"unicodedata", initunicodedata},
  {"bz2", initbz2},
  {"_crypt", init_crypt},
  {0, 0}
};

int main(int argc, char** argv)
{
  PyImport_FrozenModules = _PyImport_FrozenStdlibModules;
  PyImport_ExtendInittab(extensions);
  return Py_Main(argc, argv);
}
