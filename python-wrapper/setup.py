from setuptools import setup, Extension
from setuptools.command.build_ext import build_ext
import sys
import setuptools
import os

__version__ = '0.0.1'

ENV_INCLUDE=os.environ['ENV_ROOT']+'/include'
class get_pybind_include(object):
    """Helper class to determine the pybind11 include path

    The purpose of this class is to postpone importing pybind11
    until it is actually installed, so that the ``get_include()``
    method can be invoked. """

    def __init__(self, user=False):
        self.user = user

    def __str__(self):
        import pybind11
        return pybind11.get_include(self.user)


ext_modules = [
    Extension(
        'pytsa',
        ['pytsa.cpp'],
        include_dirs=['../include',ENV_INCLUDE,
            # Path to pybind11 headers
            get_pybind_include(),
            get_pybind_include(user=True)
        ],
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
