from cpython.ref cimport PyObject

cimport router

cdef class CRouter:

    def __cinit__(self):
        pass

    def parse(self, routes):
        cdef PyObject *py_routes = <PyObject *>routes;
        router.crouter(py_routes)
