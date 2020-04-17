
.. _program_listing_file_include_AlgoBase.hpp:

Program Listing for File AlgoBase.hpp
=====================================

|exhale_lsh| :ref:`Return to documentation for file <file_include_AlgoBase.hpp>` (``include/AlgoBase.hpp``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: none

   #ifndef __ALGOBASE_HPP
   #define __ALGOBASE_HPP
   
   // -- System includes
   #include <stdexcept>
   #include <iostream>
   #include <fstream>
   // -- Project includes
   #include <boost/numeric/ublas/matrix.hpp>
   #include <boost/numeric/ublas/io.hpp>
   #include <string>
   
   
   
   // -- Local includes
   #include <tsaSerialize.hpp>
   #include <tsaTypes.hpp>
   #include <tsaLog.hpp>
   #include <BaseView.hpp>
   #include <SeqView.hpp>
   #include <AlgoExceptions.hpp>
   #include <tsaSerialize.hpp>
   // -- Forward references
   
   namespace tsa {
   
   
   
   
       class AlgoBase {
       public:
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
       protected:
   
   
       private:
   
   
       };
   
   
   
   
   
   
   
   
   
   
   
   } // end namespace tsa
   
   #endif // __ALGOBASE_HPP
