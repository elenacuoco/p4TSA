cmake_minimum_required(VERSION 3.15...3.29)
project(pytsa LANGUAGES CXX)

# ---------------------------------------------------------------------------
# Packaging build for p4TSA / pyTSA
#
# Unlike the original build (which produced a separate libp4TSA.so and then
# dynamically linked the pytsa extension against it), this build compiles all
# core C++ sources DIRECTLY into the pytsa extension module. The result is a
# single self-contained .so that only needs the *external* shared libraries
# (GSL, FFTW3, FrameL) at runtime -- no hunting for libp4TSA.so, no RPATH pain.
# ---------------------------------------------------------------------------

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "" FORCE)
endif()

# --- pybind11 (provided by scikit-build-core / conda) ----------------------
find_package(pybind11 CONFIG REQUIRED)

# --- GSL (standard CMake module: gives GSL::gsl and GSL::gslcblas) ----------
find_package(GSL REQUIRED)

# --- FFTW3: no reliable CMake config across distros -> find_library ---------
find_library(FFTW3_LIB  fftw3  REQUIRED)   # double precision
find_library(FFTW3F_LIB fftw3f REQUIRED)   # single precision
find_library(FFTW3L_LIB fftw3l)            # long double (optional)

# --- FrameL / libframel (conda-forge: framel / libframel) ------------------
find_path(FRAMEL_INCLUDE_DIR NAMES FrameL.h)
find_library(FRAMEL_LIB NAMES framel frame REQUIRED)
if(NOT FRAMEL_INCLUDE_DIR)
  message(FATAL_ERROR "FrameL.h not found. Install framel (conda install -c conda-forge framel).")
endif()

# --- Boost (HEADER-ONLY: only Boost.uBLAS + boost/config.hpp are used) ------
# We deliberately use find_path instead of find_package(Boost): the dependency
# is header-only, so there is nothing to link, and this avoids the FindBoost /
# CMP0167 policy churn in recent CMake. conda-forge: libboost-headers.
find_path(BOOST_INCLUDE_DIR NAMES boost/numeric/ublas/matrix.hpp REQUIRED)
if(NOT BOOST_INCLUDE_DIR)
  message(FATAL_ERROR "Boost headers not found. Install libboost-headers "
                      "(conda install -c conda-forge libboost-headers) or system libboost-dev.")
endif()

# --- core C++ sources ------------------------------------------------------
file(GLOB CORE_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

# --- the single extension module -------------------------------------------
pybind11_add_module(pytsa
  ${CMAKE_CURRENT_SOURCE_DIR}/python-wrapper/pytsa.cpp
  ${CORE_SOURCES}
)

target_include_directories(pytsa PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${CMAKE_CURRENT_SOURCE_DIR}/include/eternity
  ${FRAMEL_INCLUDE_DIR}
  ${BOOST_INCLUDE_DIR}
)

target_link_libraries(pytsa PRIVATE
  GSL::gsl
  GSL::gslcblas
  ${FFTW3_LIB}
  ${FFTW3F_LIB}
  ${FRAMEL_LIB}
)
if(FFTW3L_LIB)
  target_link_libraries(pytsa PRIVATE ${FFTW3L_LIB})
endif()

# scikit-build-core installs into the wheel root; conda into site-packages.
install(TARGETS pytsa LIBRARY DESTINATION .)
