cmake_minimum_required(VERSION 3.6)
project(pytsa)

set(CMAKE_CXX_STANDARD 11)

set(P4TSA_ROOT ../)

include_directories(${P4TSA_ROOT}/include ${P4TSA_ROOT}/include/eternity $ENV{ENV_ROOT}/include
        $ENV{ENV_ROOT}/include/boost $ENV{ENV_ROOT}/include/python3.9m pybind11/include $ENV{ENV_ROOT}/include/gsl)

link_directories(${P4TSA_ROOT} $ENV{ENV_ROOT}/lib)
      

link_libraries(p4TSA gsl frame fftw3 fftw3f fftw3l gslcblas)

pybind11_add_module(pytsa pytsa.cpp)
