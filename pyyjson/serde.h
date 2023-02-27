#define PY_SSIZE_T_CLEAN
#include "Python.h"
#include "object.h"
#include "yyjson.h"
#include "memory.h"

#include <stdio.h>

static inline PyObject *
yyjson_val_to_py_obj(yyjson_val * val);

static inline yyjson_mut_val*
mut_primitive_to_element(yyjson_mut_doc *doc, PyObject *obj);

static PyObject *
loads(PyObject *self, PyObject *args, PyObject *kwargs);

static PyObject *
dumps(PyObject *self, PyObject *args, PyObject *kwargs);

static inline PyObject *
yyjson_val_to_py_obj(yyjson_val * val)
{
    yyjson_type type = yyjson_get_type(val);

    switch (type) {
        case YYJSON_TYPE_NULL:
            Py_RETURN_NONE;
        case YYJSON_TYPE_BOOL:
            if (yyjson_get_subtype(val) == YYJSON_SUBTYPE_TRUE)
                Py_RETURN_TRUE;
            else
                Py_RETURN_FALSE;
        case YYJSON_TYPE_NUM: {
            switch (yyjson_get_subtype(val)) {
                case YYJSON_SUBTYPE_UINT:
                    return PyLong_FromUnsignedLongLong(yyjson_get_uint(val));
                case YYJSON_SUBTYPE_SINT:
                    return PyLong_FromLongLong(yyjson_get_sint(val));
                case YYJSON_SUBTYPE_REAL:
                    return PyFloat_FromDouble(yyjson_get_real(val));
            }
        }
        case YYJSON_TYPE_STR: {
            size_t str_len = yyjson_get_len(val);
            const char *str = yyjson_get_str(val);
            return PyUnicode_FromStringAndSize(str, str_len);
        }
        case YYJSON_TYPE_ARR: {
            PyObject *arr = PyList_New(yyjson_arr_size(val));
            if (!arr)
                return NULL;
            yyjson_val *obj_val;
            PyObject *py_val;

            yyjson_arr_iter iter = {0};
            yyjson_arr_iter_init(val, &iter);
            size_t idx = 0;
            while ((obj_val = yyjson_arr_iter_next(&iter))) {
                py_val = yyjson_val_to_py_obj(obj_val);
                if (!py_val) {
                    return NULL;
                }
                PyList_SET_ITEM(arr, idx++, py_val);
            }
            return arr;
        }
        case YYJSON_TYPE_OBJ: {
            PyObject *dict = PyDict_New();
            if (!dict)
                return NULL;
            yyjson_val *obj_key, *obj_val;
            PyObject *py_key, *py_val;
            yyjson_obj_iter iter = {0};
            yyjson_obj_iter_init(val, &iter);
            while ((obj_key = yyjson_obj_iter_next(&iter))) {
                obj_val = yyjson_obj_iter_get_val(obj_key);
                // py_key = yyjson_val_to_py_obj(obj_key);
                size_t str_len = yyjson_get_len(obj_key);
                const char *str = yyjson_get_str(obj_key);
                py_key = PyUnicode_FromStringAndSize(str, str_len);
                py_val = yyjson_val_to_py_obj(obj_val);

                if (!py_key) {
                    return NULL;
                }
                if (!py_val) {
                    Py_DecRef(py_key);  // is it necessary?
                    return NULL;
                }
                if(PyDict_SetItem(dict, py_key, py_val) == -1) {
                    return NULL;
                }
                Py_DecRef(py_key);
                Py_DecRef(py_val);
            }
            return dict;
        }
        case YYJSON_TYPE_RAW:
            return PyLong_FromString(yyjson_get_raw(val), NULL, 10);
        case YYJSON_TYPE_NONE:
        default:
            PyErr_SetString(PyExc_TypeError, "Unknown Json Type Encountered");
            return NULL;
    }
}


static inline yyjson_mut_val*
mut_primitive_to_element(yyjson_mut_doc *doc, PyObject *obj) {
    const PyTypeObject *ob_type = obj->ob_type;
    if (ob_type == &PyUnicode_Type) {
        Py_ssize_t str_len;
        const char *str = PyUnicode_AsUTF8AndSize(obj, &str_len);
        return yyjson_mut_strncpy(doc, str, str_len);
    } else if (ob_type == &PyLong_Type) {
        // ignore just integers larger than 64bits
        int overflow = 0;
        const int64_t num = PyLong_AsLongLongAndOverflow(obj, &overflow);
        if (!overflow){
            return yyjson_mut_sint(doc, num);
        } else {
            PyObject *str_repr = PyObject_Str(obj);
            Py_ssize_t str_len;
            const char *str = PyUnicode_AsUTF8AndSize(str_repr, &str_len);
            return yyjson_mut_rawncpy(doc, str, str_len);
        }
    } else if (ob_type == &PyList_Type) {
        yyjson_mut_val *val = yyjson_mut_arr(doc);
        for (Py_ssize_t i = 0; i < PyList_GET_SIZE(obj); i++) {
            yyjson_mut_arr_append(val, mut_primitive_to_element(doc, PyList_GET_ITEM(obj, i)));
        }
        return val;
    } else if (ob_type == &PyDict_Type) {
        yyjson_mut_val *val = yyjson_mut_obj(doc);
        Py_ssize_t i = 0;
        PyObject *k, *v;
        while (PyDict_Next(obj, &i, &k, &v)) {
            // key must be string in json representation force transform
            PyObject *str_repr = PyObject_Str(k);
            Py_ssize_t str_len;
            const char *str = PyUnicode_AsUTF8AndSize(str_repr, &str_len);
            yyjson_mut_val *new_key = yyjson_mut_strncpy(doc, str, str_len);
            yyjson_mut_obj_add(val, new_key, mut_primitive_to_element(doc, v));
        }
        return val;
    } else if (ob_type == &PyFloat_Type) {
        double dnum = PyFloat_AsDouble(obj);
        if (dnum == -1 && PyErr_Occurred()) return NULL;
        return yyjson_mut_real(doc, dnum);
    } else if (obj == Py_True) {
        return yyjson_mut_true(doc);
    } else if (obj == Py_False) {
        return yyjson_mut_false(doc);
    } else if (obj == Py_None) {
        return yyjson_mut_null(doc);
    } else {
        PyErr_SetString(PyExc_TypeError, "Tried to serialize an object, yet we don't know how");
        return NULL;
    }
}

static PyObject *
loads(PyObject *self, PyObject *args, PyObject *kwargs) {
    static char *kwlist[] = {"path", "flags", NULL};
    PyObject *content_py;
    yyjson_read_err err;
    yyjson_read_flag r_flag = 0;

    if(!PyArg_ParseTupleAndKeywords(
        args, kwargs,
        "U|I",
        kwlist,
        &content_py,
        &r_flag
    )) {
        PyErr_SetString(PyExc_TypeError, "Args Parse Error");
        return Py_None;
    }
    Py_ssize_t str_len;
    const char *content = PyUnicode_AsUTF8AndSize(content_py, &str_len);
    yyjson_doc *val = yyjson_read_opts(
          (char*)content,
          str_len,
          r_flag,
          &PyMem_Allocator,
          &err
        );
    if (!val) {
        PyErr_SetString(PyExc_ValueError, err.msg);
        return Py_None;
    }
    yyjson_val *root = yyjson_doc_get_root(val);
    PyObject *ret = yyjson_val_to_py_obj(root);
    return ret;
}

static PyObject *
load(PyObject *self, PyObject *args, PyObject *kwargs) {
    static char *kwlist[] = {"path", "flags", NULL};
    char *path;
    yyjson_read_err err;
    yyjson_read_flag r_flag = 0;

    if(!PyArg_ParseTupleAndKeywords(
        args, kwargs,
        "s|I",
        kwlist,
        &path,
        &r_flag
    )) {
        PyErr_SetString(PyExc_TypeError, "Args Parse Error");
        return Py_None;
    }
    yyjson_doc *val = yyjson_read_file(
          path,
          r_flag,
          &PyMem_Allocator,
          &err
        );
    if (!val) {
        PyErr_SetString(PyExc_ValueError, err.msg);
        return Py_None;
    }
    yyjson_val *root = yyjson_doc_get_root(val);
    PyObject *ret = yyjson_val_to_py_obj(root);
    return ret;
}

static PyObject *
dumps(PyObject *self, PyObject *args, PyObject *kwargs) {
    static char *kwlist[] = {"object", "flags", NULL};
    PyObject *obj;
    yyjson_read_flag w_flag = 0;

    if(!PyArg_ParseTupleAndKeywords(
        args, kwargs,
        "O|I",
        kwlist,
        &obj,
        &w_flag
    )) {
        PyErr_SetString(PyExc_TypeError, "Args Parse Error");
        return Py_None;
    }
    yyjson_mut_doc *new_doc = yyjson_mut_doc_new(&PyMem_Allocator);
    yyjson_mut_val *root = mut_primitive_to_element(new_doc, obj);
    yyjson_mut_doc_set_root(new_doc, root);
    char* result = NULL;
    size_t w_len;
    yyjson_write_err w_err;
    result = yyjson_mut_val_write_opts(root, w_flag, &PyMem_Allocator, &w_len, &w_err);

    PyObject *obj_ret = PyUnicode_FromStringAndSize(result, w_len);
    return obj_ret;
}
