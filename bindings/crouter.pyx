from cpython.ref cimport PyObject

cdef extern from "../crouter.h":
    void crouter(PyObject *routes)

cdef class CRouter:

    def __cinit__(self):
        pass

    def parse(self, routes):
        cdef PyObject *py_routes = <PyObject *>routes;
        crouter(py_routes)
