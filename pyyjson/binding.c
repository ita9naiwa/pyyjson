#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include "yyjson.h"
#include "memory.h"
#include "serde.h"

static PyMethodDef yymethods[] = {
    {"_loads", loads, METH_VARARGS, "json loads"},
    {"_dumps", dumps, METH_VARARGS, "json dumps"},
    {NULL, NULL, 0, NULL}        /* Sentinel */
};

static PyModuleDef yymodule = {
    PyModuleDef_HEAD_INIT,
    "cserde",
    "Python bindings for the yyjson project.",
    -1,
    yymethods
};

PyMODINIT_FUNC
PyInit_cserde(void)
{
    PyObject *m;
    m = PyModule_Create(&yymodule);
    if (m == NULL) {
        return NULL;
    }
    return m;
}
