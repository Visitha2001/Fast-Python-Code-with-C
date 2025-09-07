#define PY_SSIZE_T_CLEAN // py_ssize_t insted of int for sizes
#include <Python.h>

// unsigned long long in c is a data type in C used to store a non-negative integer. 
// It's the largest of the standard integer types and is guaranteed to be at least 64 bits wide, 
// which allows it to hold a very large range of values, from 0 to 18,446,744,073,709,551,615 (2^64-1)
static unsigned long long c_factorial(unsigned int n) {
    unsigned long long result = 1;
    for (unsigned int i = 1; i <= n; i++) {
        result *= i;
    }
    return result;
};

static PyObject * py_factorial_repeat_with_GIL(PyObject*self, PyObject*args){
    unsigned int n;
    unsigned int n_repetitions;
    if (!PyArg_ParseTuple(args, "IK", &n, &n_repetitions)) {
        return NULL;
    }
    unsigned long long last = 0;
    for (unsigned long long i = 0; i < n_repetitions; i++) {
        last = c_factorial(n);
    }
    return PyLong_FromUnsignedLongLong(last);
};

static PyObject * py_factorial_repeat_without_GIL(PyObject*self, PyObject*args){
    unsigned int n;
    unsigned int n_repetitions;
    if (!PyArg_ParseTuple(args, "IK", &n, &n_repetitions)) {
        return NULL;
    }
    unsigned long long last = 0;
    Py_BEGIN_ALLOW_THREADS // releases GIL
    for (unsigned long long i = 0; i < n_repetitions; i++) {
        last = c_factorial(n);
    }
    Py_END_ALLOW_THREADS // re-acquires GIL
    return PyLong_FromUnsignedLongLong(last);
};

static PyMethodDef FastFactorialMethods[] = {
    {"factorial_repeat_with_GIL", py_factorial_repeat_with_GIL, METH_VARARGS, "Computes the factorial of a number with GIL"},
    {"factorial_repeat_without_GIL", py_factorial_repeat_without_GIL, METH_VARARGS, "Computes the factorial of a number without GIL"},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef fast_factorial = {
    PyModuleDef_HEAD_INIT,
    "fast_factorial",
    NULL,
    -1,
    FastFactorialMethods
};

PyMODINIT_FUNC PyInit_fast_factorial(void) {
    return PyModule_Create(&fast_factorial);
};
