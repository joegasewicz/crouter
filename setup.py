import os
# from pygments.lexers.sql import language_re
from setuptools import setup, Extension
from Cython.Build import cythonize

here = os.path.abspath(os.path.dirname(__file__))

ext = Extension(
    name="bindings.router",
    sources=[
        "bindings/crouter.pyx",
        "crouter.c"
    ],
    include_dirs=[os.path.join(here, "bindings")],
    extra_compile_args=[],
    extra_link_args=[],
    language="c",
)

setup(
    name="crouter",
    version="0.0.1",
    description="Python bindings for crouter C library",
    packages=["bindings"],
    package_data={"crouter": ["*.pxd", "*.pyx", "py.typed"]},
    ext_modules=cythonize([ext], language_level=3),
)
