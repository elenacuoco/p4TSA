set(SOURCE_FILES
    AR2.cpp
    AR2Parcor.cpp
    ArBurgEstimator.cpp
    ArDurbinEstimator.cpp
    Arma2Psd.cpp
    Arma2TF.cpp
    ARMAFilter.cpp
    ARMAfit.cpp
    BaseWindow.cpp
    BLInterpolation.cpp
    ButterworthFilter.cpp
    Cholesky.cpp
    ClusterizedEventFullFeatured.cpp
    ComplexFFT.cpp
    CreateDvector.cpp
    DCT.cpp
    DoubleWhitening.cpp
    DST.cpp
    eternity.cpp
    EventDescription.cpp
    EventFullFeatured.cpp
    fparser.cpp
    fpoptimizer.cpp
    FrameIStream.cpp
    FrameIChannel.cpp
    eternity.cpp
    FifoBuffer.cpp
    IDCT.cpp
    InverseRealFFT.cpp
    LatticeFilter.cpp
    LeastSquaresLattice.cpp
    LSLfilter.cpp
    LSLLearning.cpp
    MYWE.cpp
    tsaSerialize.cpp
    tsaLog.cpp
    tsaUtilityFunctions.cpp
    NotchWidrow.cpp
    Parcor2AR.cpp
    RealFFT.cpp
    RLSCanceler.cpp
    SelectionOrderCriteria.cpp
    VArma2TF.cpp
    ViewUtil.cpp
    WaveletThreshold.cpp
    WaveletTransform.cpp
    WavReconstruction.cpp
    WDF2Classify.cpp
    WDF2Reconstruct.cpp
    WindowFactory.cpp)


#Create the library
add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})

#Add all the include directories to the target
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include )

target_link_libraries(${PROJECT_NAME} PkgConfig::P4TSADEPS gsl fftw3  gslcblas)

install(TARGETS p4TSA)
install(FILES ${CMAKE_SOURCE_DIR}/include/tsa.hpp TYPE INCLUDE)