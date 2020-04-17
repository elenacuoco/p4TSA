
.. _program_listing_file_include_tsaTypes.hpp:

Program Listing for File tsaTypes.hpp
=====================================

|exhale_lsh| :ref:`Return to documentation for file <file_include_tsaTypes.hpp>` (``include/tsaTypes.hpp``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: none

   #ifndef __NAPTYPES_HPP
   #define __NAPTYPES_HPP
   
   
   #include <fstream>
   
   #include <boost/numeric/ublas/matrix.hpp>
   #include <boost/numeric/ublas/matrix_proxy.hpp>
   #include <boost/numeric/ublas/io.hpp>
   #include <eternity.hpp>
   
   
   
   
   
   
   
   
   
   
   
   
   
   namespace tsa {
   
       typedef std::complex<double> Cdouble;
   
       // Arrays
       typedef boost::numeric::ublas::matrix<int> Imatrix;
       typedef boost::numeric::ublas::matrix<unsigned int> UImatrix;
       typedef boost::numeric::ublas::matrix<double> Dmatrix;
   
   
       typedef boost::numeric::ublas::matrix< std::complex<double> > Cmatrix;
   
       // Vectors
       typedef boost::numeric::ublas::vector<int> Ivector;
       typedef boost::numeric::ublas::vector<unsigned int> UIvector;
   
   
       typedef boost::numeric::ublas::vector< double > Dvector;
       typedef boost::numeric::ublas::vector< long double > LDvector;
   
   
   
   
       typedef boost::numeric::ublas::vector< std::complex<double> > Cvector;
   
       // Vectors of arrays
       typedef std::vector< Cmatrix > VCmatrix;
       typedef std::vector< Dmatrix > VDmatrix;
   
       // Matrix rows
       typedef boost::numeric::ublas::matrix_row<Dmatrix> DmatrixRow;
       typedef boost::numeric::ublas::matrix_column<Dmatrix> DmatrixCol;
   
       typedef boost::numeric::ublas::matrix_row<Cmatrix> CmatrixRow;
       typedef boost::numeric::ublas::matrix_column<Cmatrix> CmatrixCol;
   
   
   
   
   
   
   
   
   
   
   
   } // end namespace tsa
   
   #endif // __NAPTYPES_HPP
