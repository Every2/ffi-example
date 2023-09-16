#include <Python.h>

extern int add(int a, int b);

static PyObject* py_add(PyObject* self, PyObject* args) {
	int a, b;
	if (!PyArg_ParseTuple(args, "ii", &a, &b)) {
		return NULL;
	}

	PyObject* result = PyLong_FromLongLong((PY_LONG_LONG)add(a, b));
	return result;
}

static PyMethodDef MyMethods[] = {
	{"add", py_add, METH_VARARGS, "Add two integers"},
	{NULL, NULL, 0, NULL}
};

static struct PyModuleDef addTwoIntegers = {
	PyModuleDef_HEAD_INIT,
	"addTwoIntegers",
	NULL,
	-1,
	MyMethods
};

PyMODINIT_FUNC PyInit_addTwoIntegers(void) {
	return PyModule_Create(&addTwoIntegers);
}