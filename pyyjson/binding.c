#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include "yyjson.h"
#include "memory.h"
#include "serde.h"

static PyMethodDef yymethods[] = {
    {"_load", load, METH_VARARGS | METH_KEYWORDS, "json load"},
    {"_loads", loads, METH_VARARGS | METH_KEYWORDS, "json loads"},
    {"_dumps", dumps, METH_VARARGS | METH_KEYWORDS, "json dumps"},
    {NULL, NULL, 0, NULL}        /* Sentinel */
};

static PyModuleDef yymodule = {
    PyModuleDef_HEAD_INIT,
    "serde",
    "Python bindings for the yyjson project.",
    -1,
    yymethods
};

PyMODINIT_FUNC
PyInit_serde(void)
{
    PyObject *m;
    m = PyModule_Create(&yymodule);
    if (m == NULL) {
        return NULL;
    }
    return m;
}
