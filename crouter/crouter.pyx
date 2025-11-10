cdef extern from "crouter.h":
    void crouter()

cdef class CRouter:

    def __cinit__(self):
        pass

    def parse(self):
        crouter()
