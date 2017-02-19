cmake_minimum_required(VERSION 3.6)
project(pytsa)

set(CMAKE_CXX_STANDARD 11)

set(P4TSA_ROOT ../)

include_directories(${P4TSA_ROOT}/include ${P4TSA_ROOT}/include/eternity $ENV{ENV_ROOT}/include
        $ENV{ENV_ROOT}/include/boost $ENV{ENV_ROOT}/include/python3.6m pybind11/include $ENV{ENV_ROOT}/include/gsl
        /opt/rh/devtoolset-4/root/usr/include/c++/5.3.1 /opt/rh/devtoolset-4/root/usr/include/c++/5.3.1/x86_64-redhat-linux )

link_directories(${P4TSA_ROOT} $ENV{ENV_ROOT}/lib /opt/rh/devtoolset-4/root/usr/lib/gcc/x86_64-redhat-linux/5.3.1)

link_libraries(p4TSA gsl Frame fftw3 fftw3f fftw3l gslcblas)

pybind11_add_module(pytsa pytsa.cpp)
