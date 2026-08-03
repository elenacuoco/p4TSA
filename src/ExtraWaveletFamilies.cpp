//
// ExtraWaveletFamilies.cpp
//
// Coiflet and Symlet gsl_wavelet_type definitions -- see
// ExtraWaveletFamilies.hpp for provenance/verification notes on every
// coefficient array below.
//
// `member` is the wavelet's usual *order* number (matches how these
// families are named in the literature/PyWavelets -- coif1, coif2, sym4,
// sym8), not its filter length (unlike GSL's own daubechies_init, where
// `member` is the length) -- documented here since it's a real, deliberate
// difference from GSL's own convention, not an oversight.
//

#include <ExtraWaveletFamilies.hpp>

namespace tsa {

    namespace {

        // ---- Coiflet order 1 (6 taps) ----
        static const double h_coif1[6] = { -0.07273261951252645,
          0.33789766245748182,
          0.85257202021160039,
          0.38486484686485778,
          -0.07273261951252645,
          -0.015655728135791993
        };
        static const double g_coif1[6] = { -0.015655728135791993,
          0.07273261951252645,
          0.38486484686485778,
          -0.85257202021160039,
          0.33789766245748182,
          0.07273261951252645
        };

        // ---- Coiflet order 2 (12 taps) ----
        static const double h_coif2[12] = { 0.016387336463203641,
          -0.041464936786871777,
          -0.067372554723725595,
          0.38611006682276289,
          0.81272363544941351,
          0.41700518442323908,
          -0.076488599078280761,
          -0.059434418646431092,
          0.02368017194684777,
          0.0056114348193688343,
          -0.0018232088709110323,
          -0.00072054944552034698
        };
        static const double g_coif2[12] = { -0.00072054944552034698,
          0.0018232088709110323,
          0.0056114348193688343,
          -0.02368017194684777,
          -0.059434418646431092,
          0.076488599078280761,
          0.41700518442323908,
          -0.81272363544941351,
          0.38611006682276289,
          0.067372554723725595,
          -0.041464936786871777,
          -0.016387336463203641
        };

        // ---- Symlet order 4 (8 taps) ----
        static const double h_sym4[8] = { 0.032223100604042702,
          -0.012603967262037833,
          -0.099219543576847216,
          0.29785779560527736,
          0.80373875180591614,
          0.49761866763201545,
          -0.02963552764599851,
          -0.075765714789273325
        };
        static const double g_sym4[8] = { -0.075765714789273325,
          0.02963552764599851,
          0.49761866763201545,
          -0.80373875180591614,
          0.29785779560527736,
          0.099219543576847216,
          -0.012603967262037833,
          -0.032223100604042702
        };

        // ---- Symlet order 8 (16 taps) ----
        static const double h_sym8[16] = { 0.0018899503327594609,
          -0.0003029205147213668,
          -0.014952258337048231,
          0.0038087520138906151,
          0.049137179673607506,
          -0.027219029917056003,
          -0.051945838107709037,
          0.3644418948353314,
          0.77718575170052351,
          0.48135965125837221,
          -0.061273359067658524,
          -0.14329423835080971,
          0.0076074873249176054,
          0.031695087811492981,
          -0.00054213233179114812,
          -0.0033824159510061256
        };
        static const double g_sym8[16] = { -0.0033824159510061256,
          0.00054213233179114812,
          0.031695087811492981,
          -0.0076074873249176054,
          -0.14329423835080971,
          0.061273359067658524,
          0.48135965125837221,
          -0.77718575170052351,
          0.3644418948353314,
          0.051945838107709037,
          -0.027219029917056003,
          -0.049137179673607506,
          0.0038087520138906151,
          0.014952258337048231,
          -0.0003029205147213668,
          -0.0018899503327594609
        };

        // Same pattern as GSL's own daubechies_centered_init (orthogonal
        // wavelet: analysis == synthesis filters; offset = member's own
        // "half length" for centering).
        int coiflet_centered_init(const double **h1, const double **g1,
                                   const double **h2, const double **g2,
                                   size_t *nc, size_t *offset, size_t member) {
            switch (member) {
                case 1:
                    *h1 = h_coif1; *g1 = g_coif1; *h2 = h_coif1; *g2 = g_coif1;
                    *nc = 6; *offset = 3;
                    break;
                case 2:
                    *h1 = h_coif2; *g1 = g_coif2; *h2 = h_coif2; *g2 = g_coif2;
                    *nc = 12; *offset = 6;
                    break;
                default:
                    return GSL_FAILURE;
            }
            return GSL_SUCCESS;
        }

        int symlet_centered_init(const double **h1, const double **g1,
                                  const double **h2, const double **g2,
                                  size_t *nc, size_t *offset, size_t member) {
            switch (member) {
                case 4:
                    *h1 = h_sym4; *g1 = g_sym4; *h2 = h_sym4; *g2 = g_sym4;
                    *nc = 8; *offset = 4;
                    break;
                case 8:
                    *h1 = h_sym8; *g1 = g_sym8; *h2 = h_sym8; *g2 = g_sym8;
                    *nc = 16; *offset = 8;
                    break;
                default:
                    return GSL_FAILURE;
            }
            return GSL_SUCCESS;
        }

        static const gsl_wavelet_type coiflet_centered_type = {
            "coiflet-centered", &coiflet_centered_init
        };
        static const gsl_wavelet_type symlet_centered_type = {
            "symlet-centered", &symlet_centered_init
        };

    } // anonymous namespace

    const gsl_wavelet_type *tsa_wavelet_coiflet_centered = &coiflet_centered_type;
    const gsl_wavelet_type *tsa_wavelet_symlet_centered = &symlet_centered_type;

} // namespace tsa
