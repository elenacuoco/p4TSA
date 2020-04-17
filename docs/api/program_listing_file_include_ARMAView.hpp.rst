
.. _program_listing_file_include_ARMAView.hpp:

Program Listing for File ARMAView.hpp
=====================================

|exhale_lsh| :ref:`Return to documentation for file <file_include_ARMAView.hpp>` (``include/ARMAView.hpp``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: none

   #ifndef __ARMAVIEW_HPP
   #define __ARMAVIEW_HPP
   
   
   
   #include <vector>
   
   
   
   #include <BaseView.hpp>
   
   
   
   
   
   
   
   
   
   
   namespace tsa {
   
   
       class ARMAView : public BaseView {
       public:
   
           ARMAView(unsigned int maxP, unsigned int maxQ, int channels = 1)
           :
           mAR(maxP + 1),
           mMA(maxQ + 1),
           mChannels(channels) {
               ResizeAR(maxP + 1);
               ResizeMA(maxQ + 1);
           };
   
   
           ARMAView(const ARMAView& from)
           :
           BaseView(from) {
               mChannels = from.mChannels;
               mAR = from.mAR;
               mMA = from.mMA;
           };
   
   
   
           ~ARMAView() {
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
   
                   snprintf(buffer, 1024, "%s.mChannels", prefix);
                   xml.read(buffer, mChannels, 0);
                   unsigned int sz;
   
                   snprintf(buffer, 1024, "%s.mARsize", prefix);
                   xml.read(buffer, sz, 0);
                   mAR.resize(sz);
                   for (unsigned int i = 0; i < sz; i++) {
                       unsigned int sz1, sz2;
   
                       snprintf(buffer, 1024, "%s.mAR.%d.sz1", prefix, i);
                       xml.read(buffer, sz1, 0);
                       snprintf(buffer, 1024, "%s.mAR.%d.sz2", prefix, i);
                       xml.read(buffer, sz2, 0);
                       mAR[i].resize(sz1, sz2);
                       for (unsigned j = 0; j < sz1; j++) {
                           for (unsigned k = 0; k < sz2; k++) {
                               snprintf(buffer, 1024, "%s.mAR.%d.%d.%d", prefix, i, j, k);
                               xml.read(buffer, mAR[i](j, k), 0);
                           }
                       }
                   }
   
                   snprintf(buffer, 1024, "%s.mMAsize", prefix);
                   xml.read(buffer, sz, 0);
                   mMA.resize(sz);
                   for (unsigned int i = 0; i < sz; i++) {
                       unsigned int sz1, sz2;
                       snprintf(buffer, 1024, "%s.mMA.%d.sz1", prefix, i);
                       xml.read(buffer, sz1, 0);
                       snprintf(buffer, 1024, "%s.mMA.%d.sz2", prefix, i);
                       xml.read(buffer, sz2, 0);
                       mMA[i].resize(sz1, sz2);
                       for (unsigned j = 0; j < sz1; j++) {
                           for (unsigned k = 0; k < sz2; k++) {
                               snprintf(buffer, 1024, "%s.mMA.%d.%d.%d", prefix, i, j, k);
                               xml.read(buffer, mMA[i](j, k), 0);
                           }
                       }
                   }
   
   
               } else {
   
                   snprintf(buffer, 1024, "%s.mChannels", prefix);
                   xml.write(buffer, mChannels);
                   snprintf(buffer, 1024, "%s.mARsize", prefix);
                   xml.write(buffer, mAR.size());
   
                   for (unsigned int i = 0; i < mAR.size(); i++) {
   
                       snprintf(buffer, 1024, "%s.mAR.%d.sz1", prefix, i);
                       xml.write(buffer, mAR[i].size1());
                       snprintf(buffer, 1024, "%s.mAR.%d.sz2", prefix, i);
                       xml.write(buffer, mAR[i].size2());
   
                       for (unsigned j = 0; j < mAR[i].size1(); j++) {
                           for (unsigned k = 0; k < mAR[i].size2(); k++) {
                               snprintf(buffer, 1024, "%s.mAR.%d.%d.%d", prefix, i, j, k);
                               xml.write(buffer, mAR[i](j, k));
                           }
                       }
                   }
   
                   snprintf(buffer, 1024, "%s.mMAsize", prefix);
                   xml.write(buffer, mMA.size());
   
                   for (unsigned int i = 0; i < mMA.size(); i++) {
   
                       snprintf(buffer, 1024, "%s.mMA.%d.sz1", prefix, i);
                       xml.write(buffer, mMA[i].size1());
                       snprintf(buffer, 1024, "%s.mMA.%d.sz2", prefix, i);
                       xml.write(buffer, mMA[i].size2());
   
                       for (unsigned j = 0; j < mMA[i].size1(); j++) {
                           for (unsigned k = 0; k < mMA[i].size2(); k++) {
                               snprintf(buffer, 1024, "%s.mMA.%d.%d.%d", prefix, i, j, k);
                               xml.write(buffer, mMA[i](j, k));
                           }
                       }
                   }
               }
           }
   
   
   
   
   
           const double& GetAR(int i, unsigned int channel = 0) const {
               return mAR[i](channel, channel);
           };
   
   
   
           const double& GetMA(int i, unsigned int channel = 0) const {
               return mMA[i](channel, channel);
           };
   
   
           const double& GetVAR(int i, unsigned int channel1, unsigned int channel2) const {
               return mAR[i](channel1, channel2);
           };
   
   
           const double& GetVMA(int i, unsigned int channel1, unsigned int channel2) const {
               return mMA[i](channel1, channel2);
           };
   
   
   
           unsigned int GetArOrder() const {
               return (mAR.size() - 1);
           };
   
   
           unsigned int GetMaOrder() const {
               return (mMA.size() - 1);
           };
   
   
           unsigned int GetChannels() const {
               return mMA[0].size1();
           };
   
   
   
   
   
   
           void SetAR(int i, double v, unsigned int channel = 0) {
               mAR[i](channel, channel) = v;
           };
   
   
           void SetMA(int i, double v, unsigned int channel = 0) {
               mMA[i](channel, channel) = v;
           };
   
   
   
           void SetVAR(int i, double v, unsigned int channel1, unsigned int channel2) {
               mAR[i](channel1, channel2) = v;
           }
   
   
   
           void SetVMA(int i, double v, unsigned int channel1, unsigned int channel2) {
               mMA[i](channel1, channel2) = v;
           };
   
   
   
           void SetOrder(unsigned int maxP, unsigned int maxQ) {
               if (maxP + 1 != mAR.size())
                   ResizeAR(maxP + 1);
               if (maxQ + 1 != mMA.size())
                   ResizeMA(maxQ + 1);
           };
   
   
   
           void SetChannels(unsigned int channels) {
               if (channels != mChannels) {
                   mChannels = channels;
                   ResizeAR(mAR.size());
                   ResizeMA(mMA.size());
               }
           };
   
   
   
       protected:
   
       private:
   
   
   
           void ResizeAR(unsigned int order) {
               if (order != mAR.size()) {
                   mAR.resize(order);
                   mAR.clear();
               }
   
               for (unsigned int i = 0; i < mAR.size(); i++) {
                   mAR[i].resize(mChannels, mChannels);
                   mAR[i].clear();
               }
           };
   
   
           void ResizeMA(unsigned int order) {
               if (order != mMA.size()) {
                   mMA.resize(order);
                   mMA.clear();
               }
               for (unsigned int i = 0; i < mMA.size(); i++) {
                   mMA[i].resize(mChannels, mChannels);
                   mMA[i].clear();
               }
           };
   
           VDmatrix mAR; 
           VDmatrix mMA; 
           unsigned int mChannels; 
   
       };
   
   
   
   
   
   
   
   
   } //end namespace
   
   #endif // ___ARMAVIEW_HPP
   
   
   
