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
// The long mothers (Coiflet 3-5, Symlet 10-20, and the centered Daubechies
// of 24, 32 and 40 taps that GSL stops short of) take their taps from
// ExtraWaveletLongTables.inc, written by tools/generate_long_wavelet_tables.py
// from PyWavelets; the Daubechies ones keep GSL's convention, `member` is the
// tap count. Every centered family here uses GSL's own centering, offset =
// nc / 2, as daubechies_centered_init does.
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

#include "ExtraWaveletLongTables.inc"

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
                case 3:
                    *h1 = h_coif3; *g1 = g_coif3; *h2 = h_coif3; *g2 = g_coif3;
                    *nc = 18; *offset = 9;
                    break;
                case 4:
                    *h1 = h_coif4; *g1 = g_coif4; *h2 = h_coif4; *g2 = g_coif4;
                    *nc = 24; *offset = 12;
                    break;
                case 5:
                    *h1 = h_coif5; *g1 = g_coif5; *h2 = h_coif5; *g2 = g_coif5;
                    *nc = 30; *offset = 15;
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
                case 10:
                    *h1 = h_sym10; *g1 = g_sym10; *h2 = h_sym10; *g2 = g_sym10;
                    *nc = 20; *offset = 10;
                    break;
                case 12:
                    *h1 = h_sym12; *g1 = g_sym12; *h2 = h_sym12; *g2 = g_sym12;
                    *nc = 24; *offset = 12;
                    break;
                case 16:
                    *h1 = h_sym16; *g1 = g_sym16; *h2 = h_sym16; *g2 = g_sym16;
                    *nc = 32; *offset = 16;
                    break;
                case 20:
                    *h1 = h_sym20; *g1 = g_sym20; *h2 = h_sym20; *g2 = g_sym20;
                    *nc = 40; *offset = 20;
                    break;
                default:
                    return GSL_FAILURE;
            }
            return GSL_SUCCESS;
        }

        // GSL's daubechies_centered_init stops at 20 taps (db10); this one
        // carries on with its convention, `member` the tap count.
        int daubechies_long_centered_init(const double **h1, const double **g1,
                                          const double **h2, const double **g2,
                                          size_t *nc, size_t *offset, size_t member) {
            switch (member) {
                case 24:
                    *h1 = h_daub24; *g1 = g_daub24; *h2 = h_daub24; *g2 = g_daub24;
                    break;
                case 32:
                    *h1 = h_daub32; *g1 = g_daub32; *h2 = h_daub32; *g2 = g_daub32;
                    break;
                case 40:
                    *h1 = h_daub40; *g1 = g_daub40; *h2 = h_daub40; *g2 = g_daub40;
                    break;
                default:
                    return GSL_FAILURE;
            }
            *nc = member;
            *offset = member >> 1;
            return GSL_SUCCESS;
        }

        static const gsl_wavelet_type coiflet_centered_type = {
            "coiflet-centered", &coiflet_centered_init
        };
        static const gsl_wavelet_type symlet_centered_type = {
            "symlet-centered", &symlet_centered_init
        };
        static const gsl_wavelet_type daubechies_long_centered_type = {
            "daubechies-long-centered", &daubechies_long_centered_init
        };

    } // anonymous namespace

    const gsl_wavelet_type *tsa_wavelet_coiflet_centered = &coiflet_centered_type;
    const gsl_wavelet_type *tsa_wavelet_symlet_centered = &symlet_centered_type;
    const gsl_wavelet_type *tsa_wavelet_daubechies_long_centered = &daubechies_long_centered_type;

} // namespace tsa
