#include "numpy/arrayobject.h"
#include "numpy/ndarrayobject.h"
#include "shared_memory.h"
#include <Python.h>
#include <iostream>

namespace {
using ::shared_memory::CreateSharedMsgQueue;
using ::shared_memory::GetNext;
} // namespace

static PyObject *create_shared_msg_queue(PyObject *self, PyObject *args) {
  PyObject *name = nullptr;
  PyObject *msg_queue_size = nullptr;

  // The input contains two objects.
  if (not PyArg_ParseTuple(args, "OO", &name, &msg_queue_size)) {
    PyErr_SetString(PyExc_TypeError, "input arguments are not pyobject");
  }
  PyObject *res = CreateSharedMsgQueue(name);
  return Py_BuildValue("O", res);
}

static PyObject *get_next(PyObject *self, PyObject *args) {
  PyObject *msg_queue = nullptr;

  // The input contains two objects.
  if (not PyArg_ParseTuple(args, "O", &msg_queue)) {
    PyErr_SetString(PyExc_TypeError, "input arguments are not pyobject");
  }
  PyObject *res = GetNext(msg_queue);
  return Py_BuildValue("O", res);
}

static PyMethodDef shmem_methods[] = {
    {"create_shared_msg_queue" /*method name*/,
     create_shared_msg_queue /*function pointer*/,
     METH_VARARGS /*variable argument functions*/},
    {"get_next" /*method name*/, get_next /*function pointer*/,
     METH_VARARGS /*variable argument functions*/},
    {NULL, NULL, 0, NULL} /* ending indicator */

};

static PyModuleDef shmem_utils_modules = {
    PyModuleDef_HEAD_INIT,
    "shmem_utils",
    "Example of shared memory between Python and C++, which supports passing "
    "numpy array.",
    -1,
    shmem_methods,
};

PyMODINIT_FUNC PyInit_shmem_utils(void) {
  import_array();

  return PyModule_Create(&shmem_utils_modules);
}