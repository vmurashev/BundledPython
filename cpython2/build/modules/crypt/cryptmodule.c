#include "Python.h"
#include <openssl_posix_crypt.h>

static PyObject *crypt_crypt(PyObject *self, PyObject *args)
{
    char *word, *salt;
    char dest[OPENSSL_POSIX_CRYPT_BUFSIZ];

    if (!PyArg_ParseTuple(args, "ss:crypt", &word, &salt)) {
        return NULL;
    }

    return Py_BuildValue("s", openssl_posix_crypt(word, salt, dest, OPENSSL_POSIX_CRYPT_BUFSIZ));

}

PyDoc_STRVAR(crypt_crypt__doc__,
"crypt(word, salt) -> string\n\
Hash a word with the given salt and return the hashed password.\n\
word will usually be a user's password. salt (either a random 2 or 16\n\
character string, possibly prefixed with $digit$ to indicate the method)\n\
will be used to perturb the encryption algorithm and produce distinct\n\
results for a given word.");

static PyMethodDef crypt_methods[] = {
    {"crypt",           crypt_crypt, METH_VARARGS, crypt_crypt__doc__},
    {NULL,              NULL}           /* sentinel */
};

PyMODINIT_FUNC
init_crypt(void)
{
    Py_InitModule("_crypt", crypt_methods);
}
