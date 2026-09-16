cmake_minimum_required(VERSION 3.28...3.31)
project(py4tsa LANGUAGES CXX)

# ---------------------------------------------------------------------------
# Packaging build for p4TSA / py4TSA
#
# Unlike the original build (which produced a separate libp4TSA.so and then
# dynamically linked the py4tsa extension against it), this build compiles all
# core C++ sources DIRECTLY into the py4tsa extension module. The result is a
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
# Frame I/O is not optional: FrameIStream and FrameIChannel are how the
# pipeline reads strain, and a build without them cannot search for triggers.
# A copy already on the system is preferred, which keeps the conda-forge build
# exactly as it was; when there is none -- a bare manylinux image, say -- the
# library is built from its own source instead, so that `pip install .` works
# somewhere conda does not reach.
find_path(FRAMEL_INCLUDE_DIR NAMES FrameL.h)
find_library(FRAMEL_LIB NAMES framel frame)

if(FRAMEL_INCLUDE_DIR AND FRAMEL_LIB)
  message(STATUS "FrameL: using ${FRAMEL_LIB}")
  set(FRAMEL_VENDORED FALSE)
else()
  message(STATUS "FrameL: not found on the system, building it from source")
  include(FetchContent)

  # FrameL's own CMakeLists builds Matlab and Python bindings, Debian and RPM
  # packaging, and its example programs, none of which belong in this wheel.
  # They are all guarded by cache variables, so setting them first is enough.
  set(ENABLE_C ON CACHE BOOL "" FORCE)
  set(ENABLE_MATLAB OFF CACHE BOOL "" FORCE)
  set(ENABLE_PYTHON OFF CACHE BOOL "" FORCE)
  set(ENABLE_PACKAGING OFF CACHE BOOL "" FORCE)
  set(BUILD_TESTING OFF CACHE BOOL "" FORCE)

  FetchContent_Declare(framel
    GIT_REPOSITORY https://git.ligo.org/virgo/virgoapp/Fr.git
    GIT_TAG        8.50.2
    GIT_SHALLOW    TRUE
    EXCLUDE_FROM_ALL              # its install() rules stay out of the wheel
  )
  FetchContent_MakeAvailable(framel)

  # framel declares its include directory PRIVATE, so linking the target does
  # not carry the header along: point at the source tree explicitly.
  set(FRAMEL_INCLUDE_DIR "${framel_SOURCE_DIR}/src")
  set(FRAMEL_LIB framel)
  set(FRAMEL_VENDORED TRUE)
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

# --- Cereal (HEADER-ONLY serialization, replaces the old vendored
# `eternity` XML persistence framework as of 2026-08-03 -- see
# CerealPersistence.hpp) -- same find_path pattern as Boost above.
# conda-forge: cereal.
find_path(CEREAL_INCLUDE_DIR NAMES cereal/cereal.hpp REQUIRED)
if(NOT CEREAL_INCLUDE_DIR)
  message(FATAL_ERROR "Cereal headers not found. Install cereal "
                      "(conda install -c conda-forge cereal) or system libcereal-dev.")
endif()

# --- core C++ sources ------------------------------------------------------
file(GLOB CORE_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

# --- the single extension module -------------------------------------------
pybind11_add_module(py4tsa
  ${CMAKE_CURRENT_SOURCE_DIR}/python-wrapper/py4tsa.cpp
  ${CORE_SOURCES}
)

target_include_directories(py4tsa PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${FRAMEL_INCLUDE_DIR}
  ${BOOST_INCLUDE_DIR}
  ${CEREAL_INCLUDE_DIR}
)

target_link_libraries(py4tsa PRIVATE
  GSL::gsl
  GSL::gslcblas
  ${FFTW3_LIB}
  ${FFTW3F_LIB}
  ${FRAMEL_LIB}
)
if(FFTW3L_LIB)
  target_link_libraries(py4tsa PRIVATE ${FFTW3L_LIB})
endif()

# scikit-build-core installs into the wheel root; conda into site-packages.
install(TARGETS py4tsa LIBRARY DESTINATION .)

if(FRAMEL_VENDORED)
  # A FrameL built here is on no loader path, so it ships beside the extension
  # and is found through a relative RPATH; auditwheel, finding it already in
  # the wheel, keeps that RPATH and leaves it be. Only the install RPATH is set:
  # in the build tree CMake already points at the framel target's own output
  # directory. The system case needs neither, its libframel being where the
  # loader looks already (or where conda's compiler wrappers say it is).
  set_target_properties(py4tsa PROPERTIES INSTALL_RPATH "$ORIGIN")
  # Only the file the loader asks for, under its SONAME. A wheel is a zip and
  # keeps no symlinks, so installing the target would ship three full copies.
  install(FILES $<TARGET_FILE:framel>
          DESTINATION .
          RENAME $<TARGET_SONAME_FILE_NAME:framel>)
endif()
