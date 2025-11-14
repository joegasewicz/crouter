from cpython.ref cimport PyObject

cdef extern from "crouter.h":
    void crouter(PyObject *routes)

