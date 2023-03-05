cmake_minimum_required(VERSION 3.6)
project(p4TSA)
# The version number.

if(NOT p4TSA_VERSION)
  SET(p4TSA_VERSION_MAJOR 2)
  SET(p4TSA_VERSION_MINOR 0)
  SET(p4TSA_VERSION_PATCH 1)
  SET(p4TSA_VERSION 2.0.1)
endif(NOT p4TSA_VERSION)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        src/AR2.cpp
        src/AR2Parcor.cpp
        src/ArBurgEstimator.cpp
        src/ArDurbinEstimator.cpp
        src/Arma2Psd.cpp
        src/Arma2TF.cpp
        src/ARMAFilter.cpp
        src/ARMAfit.cpp
        src/BaseWindow.cpp
        src/BLInterpolation.cpp
        src/ButterworthFilter.cpp
        src/Cholesky.cpp
        src/ClusterizedEventFullFeatured.cpp
        src/ComplexFFT.cpp
        src/CreateDvector.cpp
        src/DCT.cpp
        src/DoubleWhitening.cpp
        src/DST.cpp
        src/eternity.cpp
        src/EventDescription.cpp
        src/EventFullFeatured.cpp
        src/fparser.cpp
        src/fpoptimizer.cpp
        src/FrameIStream.cpp
        src/FrameIChannel.cpp
        src/eternity.cpp
        src/FifoBuffer.cpp
        src/IDCT.cpp
        src/InverseRealFFT.cpp
        src/LatticeFilter.cpp
        src/LeastSquaresLattice.cpp
        src/LSLfilter.cpp
        src/LSLLearning.cpp
        src/MYWE.cpp
        src/tsaSerialize.cpp
        src/tsaLog.cpp
        src/tsaUtilityFunctions.cpp
        src/NotchWidrow.cpp
        src/Parcor2AR.cpp
        src/RealFFT.cpp
        src/RLSCanceler.cpp
        src/SelectionOrderCriteria.cpp
        src/VArma2TF.cpp
        src/ViewUtil.cpp
        src/WaveletThreshold.cpp
        src/WaveletTransform.cpp
        src/WavReconstruction.cpp
        src/WDF2Classify.cpp
        src/WDF2Reconstruct.cpp
        src/WindowFactory.cpp)
include_directories(include include/eternity $ENV{ENV_ROOT}/include $ENV{ENV_ROOT}/include/gsl) #$ENV{ENV_ROOT}/include/boost


link_directories($ENV{ENV_ROOT}/lib)
link_libraries(gsl fftw3  gslcblas framel)
add_library(p4TSA SHARED ${SOURCE_FILES})
install (TARGETS p4TSA DESTINATION $ENV{ENV_ROOT}/lib)
install (FILES include/tsa.hpp DESTINATION $ENV{ENV_ROOT}/include)
 
# Add the cmake folder so the FindSphinx module is found
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
if(DEFINED ENV{READTHEDOCS})
  add_subdirectory ("docs")
endif(DEFINED ENV{READTHEDOCS})
