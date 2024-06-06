cmake_minimum_required(VERSION 3.6)
project(
    p4TSA
    LANGUAGES CXX
    VERSION 2.0.1
    DESCRIPTION "package for Time Series Analysis"
)

set(CMAKE_CXX_STANDARD 11)

find_package(GSL REQUIRED)
find_package(Boost REQUIRED)

#Find Framel
set(P4TSA_DEPENDENCIES "framel")
pkg_check_modules(P4TSADEPS REQUIRED IMPORTED_TARGET ${P4TSA_DEPENDENCIES})

add_subdirectory(src)
 
# Add the cmake folder so the FindSphinx module is found
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
if(BUILD_DOCS)
  add_subdirectory (docs)
endif(BUILD_DOCS)
