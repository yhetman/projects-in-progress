from setuptools import setup
from Cython.Build import cythonize

setup(
    name='lab1',
    ext_modules=cythonize("lab1.pyx"),
    zip_safe=False,
)
