#include <WindowFactory.hpp>

namespace tsa {

    std::vector< std::string > GetWindowList() {
        std::vector< std::string > wl(8);

        wl[0] = "Bartlett";
        wl[1] = "Welch";
        wl[2] = "TukeyHann";
        wl[3] = "Cs2Hann";
        wl[4] = "Cs2Hamming";
        wl[5] = "Bisquare";
        wl[6] = "Tukey";
        wl[7] = "Kaiser";

        return wl;

    }

    BaseWindow* WindowFactory(const std::string& name, unsigned int size) {
        BaseWindow *w = 0;
        if (name == "Bartlett") {
            w = new BartlettWindow(size);
        } else if (name == "Welch") {
            w = new WelchWindow(size);
        } else if (name == "TukeyHann") {
            w = new TukeyHannWindow(size);
        } else if (name == "Cs2Hann") {
            w = new Cs2HannWindow(size);
        } else if (name == "Cs2Hamming") {
            w = new Cs2HammingWindow(size);
        } else if (name == "Bisquare") {
            w = new BisquareWindow(size);
        } else if (name == "Tukey") {
            w = new TukeyWindow(size);
        } else if (name == "Kaiser") {
            w = new KaiserWindow(size);
        }
        if (w != 0) {
            LogInfo("Created window %s", name.c_str());
        } else {
            LogWarning("Failed to create window %s", name.c_str());
        }
        return w;
    }

    BaseWindow* WindowFactory(const std::string& name, const std::string& parameters, unsigned int size) {
        BaseWindow *w = 0;
        if (name == "Bartlett") {
            w = new BartlettWindow(size, parameters);
        } else if (name == "Welch") {
            w = new WelchWindow(size, parameters);
        } else if (name == "TukeyHann") {
            w = new TukeyHannWindow(size, parameters);
        } else if (name == "Cs2Hann") {
            w = new Cs2HannWindow(size, parameters);
        } else if (name == "Cs2Hamming") {
            w = new Cs2HammingWindow(size, parameters);
        } else if (name == "Bisquare") {
            w = new BisquareWindow(size, parameters);
        } else if (name == "Tukey") {
            w = new TukeyWindow(size, parameters);
        } else if (name == "Kaiser") {
            w = new KaiserWindow(size, parameters);
        }
        if (w != 0) {
            LogInfo("Created window %s with parameters %s", name.c_str(), parameters.c_str());
        } else {
            LogWarning("Failed to create window %s with parameters %s", name.c_str(), parameters.c_str());
        }
        return w;
    }


};
