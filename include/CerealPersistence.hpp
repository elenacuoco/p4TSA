///
///   Copyright (C) 2026 by Elena Cuoco
///   elena.cuoco@unibo.it
///
///   This program is free software; you can redistribute it and/or modify
///   it under the terms of the GNU General Public License as published by
///   the Free Software Foundation; either version 2 of the License, or
///   (at your option) any later version.
///
/// @file   CerealPersistence.hpp
/// @author Elena Cuoco <elena.cuoco@unibo.it>
/// @date   2026
///
/// @brief  Replaces the vendored `eternity` XML persistence framework
///         (1999-2003, no longer compiled into p4TSA as of this file) with
///         Cereal (https://uscilab.github.io/cereal/), a small, modern,
///         actively-maintained, header-only C++11 serialization library --
///         no new link dependency, same footprint class as the Boost
///         headers already used for Dvector/Dmatrix.
///
///         `Dvector`/`Dmatrix` (boost::numeric::ublas::vector<double>/
///         matrix<double>, see tsaTypes.hpp) cannot be hooked up to cereal
///         directly: boost/numeric/ublas headers already give them their
///         own member `serialize(Archive&, unsigned int version)` for
///         Boost.Serialization (present regardless of whether
///         Boost.Serialization itself is ever used), and cereal's own
///         SFINAE dispatch finds that as a second candidate alongside any
///         free save/load pair added for the same type, refusing to pick
///         one (`cereal::specialize` -- the documented fix for exactly this
///         -- was tried first and did not resolve it here). `DvectorProxy`/
///         `DmatrixProxy` below sidestep the ambiguity entirely: they are
///         plain types this file owns outright, wrapping a reference to the
///         real Dvector/Dmatrix and converting through `std::vector<double>`
///         (which cereal already supports cleanly, no inherited-member
///         conflict) -- `ar(DvectorProxy(v))` in a class's own `serialize()`
///         reads/writes `v` in place with no ambiguity.
///
///         SaveBinary/LoadBinary give every persistable class's Save/Load a
///         single, consistent implementation: a class need only provide a
///         `template<class Archive> void serialize(Archive&)` member
///         listing its own fields (cereal's own idiom -- see e.g.
///         ArBurgEstimator.hpp for the resulting pattern), wrapping any
///         Dvector/Dmatrix member in a DvectorProxy/DmatrixProxy, not its
///         own hand-written file I/O.
///
///         Binary format (cereal::BinaryOutputArchive/BinaryInputArchive),
///         not XML/JSON: smaller and faster, and nothing here is meant to
///         be hand-edited -- if a human-readable dump is ever needed for
///         debugging, swap in cereal::JSONOutputArchive/JSONInputArchive,
///         the class-side `serialize()` methods do not change.
///
#ifndef __CEREALPERSISTENCE_HPP
#define __CEREALPERSISTENCE_HPP

#include <fstream>
#include <stdexcept>
#include <vector>

#include <cereal/archives/binary.hpp>
#include <cereal/types/vector.hpp>

#include <tsaTypes.hpp>

namespace tsa {

    struct DvectorProxy {
        Dvector& v;
        explicit DvectorProxy(Dvector& v_) : v(v_) {}

        template<class Archive>
        void save(Archive& ar) const {
            std::vector<double> tmp(v.begin(), v.end());
            ar(tmp);
        }

        template<class Archive>
        void load(Archive& ar) {
            std::vector<double> tmp;
            ar(tmp);
            v.resize(tmp.size());
            std::copy(tmp.begin(), tmp.end(), v.begin());
        }
    };

    struct DmatrixProxy {
        Dmatrix& m;
        explicit DmatrixProxy(Dmatrix& m_) : m(m_) {}

        template<class Archive>
        void save(Archive& ar) const {
            std::size_t s1 = m.size1(), s2 = m.size2();
            std::vector<double> tmp(s1 * s2);
            for (std::size_t i = 0; i < s1; ++i) {
                for (std::size_t j = 0; j < s2; ++j) {
                    tmp[i * s2 + j] = m(i, j);
                }
            }
            ar(s1, s2, tmp);
        }

        template<class Archive>
        void load(Archive& ar) {
            std::size_t s1 = 0, s2 = 0;
            std::vector<double> tmp;
            ar(s1, s2, tmp);
            m.resize(s1, s2);
            for (std::size_t i = 0; i < s1; ++i) {
                for (std::size_t j = 0; j < s2; ++j) {
                    m(i, j) = tmp[i * s2 + j];
                }
            }
        }
    };

    // Wraps VDmatrix (std::vector<Dmatrix>, see ARMAView's mAR/mMA): cereal's
    // own std::vector support would otherwise try to serialize each Dmatrix
    // element directly and hit the same ambiguity DmatrixProxy exists to
    // avoid.
    struct VDmatrixProxy {
        VDmatrix& vm;
        explicit VDmatrixProxy(VDmatrix& vm_) : vm(vm_) {}

        template<class Archive>
        void save(Archive& ar) const {
            std::size_t n = vm.size();
            ar(n);
            for (std::size_t k = 0; k < n; ++k) {
                DmatrixProxy(const_cast<Dmatrix&>(vm[k])).save(ar);
            }
        }

        template<class Archive>
        void load(Archive& ar) {
            std::size_t n = 0;
            ar(n);
            vm.resize(n);
            for (std::size_t k = 0; k < n; ++k) {
                DmatrixProxy(vm[k]).load(ar);
            }
        }
    };

    template<class T>
    void SaveBinary(const char* filename, const T& obj) {
        std::ofstream os(filename, std::ios::binary);
        if (!os) {
            throw std::runtime_error(std::string("SaveBinary: cannot open ") + filename);
        }
        cereal::BinaryOutputArchive archive(os);
        archive(obj);
    }

    template<class T>
    void LoadBinary(const char* filename, T& obj) {
        std::ifstream is(filename, std::ios::binary);
        if (!is) {
            throw std::runtime_error(std::string("LoadBinary: cannot open ") + filename);
        }
        cereal::BinaryInputArchive archive(is);
        archive(obj);
    }

} // namespace tsa

#endif // __CEREALPERSISTENCE_HPP
