#include <tsaTypes.hpp>
#include <tsaLog.hpp>
#include <fstream>




namespace tsa {

    std::string tsaVersion() {
        return std::string("NAP v3r1");
    }

    std::complex<double>CRATIO(std::complex<double> v1, std::complex<double> v2) {
        return v1 / v2;
    }

    void DmatrixPrint(const Dmatrix& m, const char *filename, bool transpose = false) {
        std::ofstream out(filename);

        for (unsigned int row = 0; row < m.size2(); row++) {

            out << row << " ";

            for (unsigned int col = 0; col < m.size1(); col++) {

                out << m(col, row) << " ";

            }

            out << "\n";

        }

    }



}
