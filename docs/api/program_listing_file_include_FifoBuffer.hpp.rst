
.. _program_listing_file_include_FifoBuffer.hpp:

Program Listing for File FifoBuffer.hpp
=======================================

|exhale_lsh| :ref:`Return to documentation for file <file_include_FifoBuffer.hpp>` (``include/FifoBuffer.hpp``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: none

   
   
   #ifndef __FIFOBUFFER_HPP
   #define __FIFOBUFFER_HPP
   
   #include <queue>
   #include <deque>
   
   
   #include <eternity.hpp>
   #include <tsaTypes.hpp>
   #include <tsaSerialize.hpp>
   
   
   
   
   
   
   
   namespace tsa {
   
       class FifoBuffer {
       public:
   
           FifoBuffer(unsigned int channels);
   
   
           FifoBuffer(const FifoBuffer& from);
   
           ~FifoBuffer();
   
           FifoBuffer& operator=(const FifoBuffer& from);
   
   
   
   
   
   
   
   
   
   
           void AddPoints(Dmatrix& data, double scale, int n = 0, int offset = 0);
   
           void AddPoint(Dvector& data, double scale);
   
           void AddPoint();
   
           inline double& Back(unsigned int i) {
               return (*(mBuffer.back()))(i);
           }
   
   
           void DelPoints(int n);
   
           inline unsigned int Size() {
               return mBuffer.size();
           }
   
           inline double& operator()(int r, int c) {
               return (*mBuffer[c])(r);
           }
   
           void Load(const char *filename, const char *fmt = "txt") {
               eternity::xml_archive fa;
               fa.open(filename, eternity::archive::load);
               xml_serialize(fa, "");
               fa.close();
           }
   
           void Save(const char *filename, const char *fmt = "txt") {
               eternity::xml_archive fa;
               fa.open(filename, eternity::archive::store);
               xml_serialize(fa, "");
               fa.close();
           }
   
           void xml_serialize(eternity::xml_archive& xml, const char* prefix) {
               char buffer[1024];
   
               if (xml.is_loading()) {
                   unsigned int sz = 0;
                   snprintf(buffer, 1024, "%s.sz", prefix);
                   xml.read(buffer, sz, 0);
                   snprintf(buffer, 1024, "%s.mChannels", prefix);
                   xml.read(buffer, mChannels, 0);
                   DelPoints(sz);
                   for (unsigned int i = 0; i < sz; i++) {
                       snprintf(buffer, 1024, "%s.mBuffer.%d", prefix, i);
                       AddPoint();
                       DVECTOR_XML_SERIALIZE(*(mBuffer.back()), xml, buffer);
                   }
   
               } else {
                   unsigned int sz = mBuffer.size();
                   snprintf(buffer, 1024, "%s.sz", prefix);
                   xml.write(buffer, sz);
                   snprintf(buffer, 1024, "%s.mChannels", prefix);
                   xml.write(buffer, mChannels);
                   for (unsigned int i = 0; i < sz; i++) {
                       snprintf(buffer, 1024, "%s.mBuffer.%d", prefix, i);
                       DVECTOR_XML_SERIALIZE(*mBuffer[i], xml, buffer);
                   }
               }
           }
   
   
   
   
   
   
   
   
   
   
   
   
   
       protected:
   
   
       private:
   
   
   
   
           unsigned int mChannels; 
           std::queue<Dvector*> mRepository; 
           std::deque<Dvector*> mBuffer; 
       };
   
   
   
   
   
   
   
   
   
   
   } // end namespace tsa
   
   #endif // __FIFOBUFFER_HPP
