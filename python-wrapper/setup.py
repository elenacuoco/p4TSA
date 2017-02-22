from setuptools import setup, Extension
from setuptools.command.build_ext import build_ext
import sys
import setuptools
import os
import locations

__version__ = '0.0.1'

ENV_INCLUDE=os.environ['ENV_ROOT']+'/include'
PYBIND11_INCLUDE=os.path.dirname(locations.distutils_scheme('pybind11', *args, **kwargs)['headers'])
ext_modules = [
    Extension(
        'pytsa',
        ['pytsa.cpp'],
        include_dirs=['../include', ENV_INCLUDE, PYBIND11_INCLUDE],
        libraries=[ 'gsl', 'Frame', 'fftw3','fftw3f', 'fftw3l', 'gslcblas','p4TSA'],
        language='c++'
    ),
]

setup(
    name='pytsa',
    version=__version__,
    author='Elena Cuoco',
    author_email='info@elenacuoco.com',
    url='https://github.com/p4TSA',
    description='package for Time Series Analysis',
    long_description='',
    ext_modules=ext_modules,
    install_requires=['pybind11>=1.7'],
    setup_requires=['pytest-runner'],
    tests_require=['pytest'],
    zip_safe=False,
)
