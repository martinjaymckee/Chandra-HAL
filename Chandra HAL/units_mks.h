
#ifndef CHANDRA_MKS_UNITS_H
#define CHANDRA_MKS_UNITS_H

#include <ratio>

#include "dimensions.h"
#include "quantity.h"

namespace chandra
{
namespace units
{
namespace mks
{

//
// Unit "Eg"
//
    struct Eg
    {
        using factor_t = std::ratio<1000000000000000, 1>; // 1e+15
        using dimensions_t = dimensions::Mass;
        using offset_t = std::ratio<0, 1>;
        using relative_t = Eg;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "Eg";
        }
    };
    template<typename Value = long double>
    using Q_Eg = units::Quantity<Value, Eg>;
    namespace literals
    {
        static inline Q_Eg<long double> operator "" _Eg_ (long double _v) {
            return Q_Eg<long double>(_v); }
        static inline Q_Eg<long double> operator "" _Eg_ (unsigned long long int _v) {
            return Q_Eg<long double>(_v); }
    }



//
// Unit "Pg"
//
    struct Pg
    {
        using factor_t = std::ratio<1000000000000, 1>; // 1e+12
        using dimensions_t = dimensions::Mass;
        using offset_t = std::ratio<0, 1>;
        using relative_t = Pg;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "Pg";
        }
    };
    template<typename Value = long double>
    using Q_Pg = units::Quantity<Value, Pg>;
    namespace literals
    {
        static inline Q_Pg<long double> operator "" _Pg_ (long double _v) {
            return Q_Pg<long double>(_v); }
        static inline Q_Pg<long double> operator "" _Pg_ (unsigned long long int _v) {
            return Q_Pg<long double>(_v); }
    }



//
// Unit "Tg"
//
    struct Tg
    {
        using factor_t = std::ratio<1000000000, 1>; // 1e+09
        using dimensions_t = dimensions::Mass;
        using offset_t = std::ratio<0, 1>;
        using relative_t = Tg;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "Tg";
        }
    };
    template<typename Value = long double>
    using Q_Tg = units::Quantity<Value, Tg>;
    namespace literals
    {
        static inline Q_Tg<long double> operator "" _Tg_ (long double _v) {
            return Q_Tg<long double>(_v); }
        static inline Q_Tg<long double> operator "" _Tg_ (unsigned long long int _v) {
            return Q_Tg<long double>(_v); }
    }



//
// Unit "Gg"
//
    struct Gg
    {
        using factor_t = std::ratio<1000000, 1>; // 1e+06
        using dimensions_t = dimensions::Mass;
        using offset_t = std::ratio<0, 1>;
        using relative_t = Gg;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "Gg";
        }
    };
    template<typename Value = long double>
    using Q_Gg = units::Quantity<Value, Gg>;
    namespace literals
    {
        static inline Q_Gg<long double> operator "" _Gg_ (long double _v) {
            return Q_Gg<long double>(_v); }
        static inline Q_Gg<long double> operator "" _Gg_ (unsigned long long int _v) {
            return Q_Gg<long double>(_v); }
    }



//
// Unit "Mg"
//
    struct Mg
    {
        using factor_t = std::ratio<1000, 1>; // 1000
        using dimensions_t = dimensions::Mass;
        using offset_t = std::ratio<0, 1>;
        using relative_t = Mg;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "Mg";
        }
    };
    template<typename Value = long double>
    using Q_Mg = units::Quantity<Value, Mg>;
    namespace literals
    {
        static inline Q_Mg<long double> operator "" _Mg_ (long double _v) {
            return Q_Mg<long double>(_v); }
        static inline Q_Mg<long double> operator "" _Mg_ (unsigned long long int _v) {
            return Q_Mg<long double>(_v); }
    }



//
// Unit "kg"
//
    struct kg
    {
        using factor_t = std::ratio<1, 1>; // 1
        using dimensions_t = dimensions::Mass;
        using offset_t = std::ratio<0, 1>;
        using relative_t = kg;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "kg";
        }
    };
    template<typename Value = long double>
    using Q_kg = units::Quantity<Value, kg>;
    namespace literals
    {
        static inline Q_kg<long double> operator "" _kg_ (long double _v) {
            return Q_kg<long double>(_v); }
        static inline Q_kg<long double> operator "" _kg_ (unsigned long long int _v) {
            return Q_kg<long double>(_v); }
    }



//
// Unit "hg"
//
    struct hg
    {
        using factor_t = std::ratio<1, 10>; // 0.1
        using dimensions_t = dimensions::Mass;
        using offset_t = std::ratio<0, 1>;
        using relative_t = hg;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "hg";
        }
    };
    template<typename Value = long double>
    using Q_hg = units::Quantity<Value, hg>;
    namespace literals
    {
        static inline Q_hg<long double> operator "" _hg_ (long double _v) {
            return Q_hg<long double>(_v); }
        static inline Q_hg<long double> operator "" _hg_ (unsigned long long int _v) {
            return Q_hg<long double>(_v); }
    }



//
// Unit "dag"
//
    struct dag
    {
        using factor_t = std::ratio<1, 100>; // 0.01
        using dimensions_t = dimensions::Mass;
        using offset_t = std::ratio<0, 1>;
        using relative_t = dag;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "dag";
        }
    };
    template<typename Value = long double>
    using Q_dag = units::Quantity<Value, dag>;
    namespace literals
    {
        static inline Q_dag<long double> operator "" _dag_ (long double _v) {
            return Q_dag<long double>(_v); }
        static inline Q_dag<long double> operator "" _dag_ (unsigned long long int _v) {
            return Q_dag<long double>(_v); }
    }



//
// Unit "g"
//
    struct g
    {
        using factor_t = std::ratio<1, 1000>; // 0.001
        using dimensions_t = dimensions::Mass;
        using offset_t = std::ratio<0, 1>;
        using relative_t = g;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "g";
        }
    };
    template<typename Value = long double>
    using Q_g = units::Quantity<Value, g>;
    namespace literals
    {
        static inline Q_g<long double> operator "" _g_ (long double _v) {
            return Q_g<long double>(_v); }
        static inline Q_g<long double> operator "" _g_ (unsigned long long int _v) {
            return Q_g<long double>(_v); }
    }



//
// Unit "dg"
//
    struct dg
    {
        using factor_t = std::ratio<1, 10000>; // 0.0001
        using dimensions_t = dimensions::Mass;
        using offset_t = std::ratio<0, 1>;
        using relative_t = dg;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "dg";
        }
    };
    template<typename Value = long double>
    using Q_dg = units::Quantity<Value, dg>;
    namespace literals
    {
        static inline Q_dg<long double> operator "" _dg_ (long double _v) {
            return Q_dg<long double>(_v); }
        static inline Q_dg<long double> operator "" _dg_ (unsigned long long int _v) {
            return Q_dg<long double>(_v); }
    }



//
// Unit "cg"
//
    struct cg
    {
        using factor_t = std::ratio<1, 100000>; // 1e-05
        using dimensions_t = dimensions::Mass;
        using offset_t = std::ratio<0, 1>;
        using relative_t = cg;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "cg";
        }
    };
    template<typename Value = long double>
    using Q_cg = units::Quantity<Value, cg>;
    namespace literals
    {
        static inline Q_cg<long double> operator "" _cg_ (long double _v) {
            return Q_cg<long double>(_v); }
        static inline Q_cg<long double> operator "" _cg_ (unsigned long long int _v) {
            return Q_cg<long double>(_v); }
    }



//
// Unit "slug"
//
    struct slug
    {
        using factor_t = std::ratio<4283756, 625>; // 6854.01
        using dimensions_t = dimensions::Mass;
        using offset_t = std::ratio<0, 1>;
        using relative_t = slug;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "slug";
        }
    };
    template<typename Value = long double>
    using Q_slug = units::Quantity<Value, slug>;
    namespace literals
    {
        static inline Q_slug<long double> operator "" _slug_ (long double _v) {
            return Q_slug<long double>(_v); }
        static inline Q_slug<long double> operator "" _slug_ (unsigned long long int _v) {
            return Q_slug<long double>(_v); }
    }



//
// Unit "EN"
//
    struct EN
    {
        using factor_t = std::ratio<1000000000000000000, 1>; // 1e+18
        using dimensions_t = dimensions::Mass;
        using offset_t = std::ratio<0, 1>;
        using relative_t = EN;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "EN";
        }
    };
    template<typename Value = long double>
    using Q_EN = units::Quantity<Value, EN>;
    namespace literals
    {
        static inline Q_EN<long double> operator "" _EN_ (long double _v) {
            return Q_EN<long double>(_v); }
        static inline Q_EN<long double> operator "" _EN_ (unsigned long long int _v) {
            return Q_EN<long double>(_v); }
    }



//
// Unit "PN"
//
    struct PN
    {
        using factor_t = std::ratio<1000000000000000, 1>; // 1e+15
        using dimensions_t = dimensions::Mass;
        using offset_t = std::ratio<0, 1>;
        using relative_t = PN;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "PN";
        }
    };
    template<typename Value = long double>
    using Q_PN = units::Quantity<Value, PN>;
    namespace literals
    {
        static inline Q_PN<long double> operator "" _PN_ (long double _v) {
            return Q_PN<long double>(_v); }
        static inline Q_PN<long double> operator "" _PN_ (unsigned long long int _v) {
            return Q_PN<long double>(_v); }
    }



//
// Unit "TN"
//
    struct TN
    {
        using factor_t = std::ratio<1000000000000, 1>; // 1e+12
        using dimensions_t = dimensions::Mass;
        using offset_t = std::ratio<0, 1>;
        using relative_t = TN;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "TN";
        }
    };
    template<typename Value = long double>
    using Q_TN = units::Quantity<Value, TN>;
    namespace literals
    {
        static inline Q_TN<long double> operator "" _TN_ (long double _v) {
            return Q_TN<long double>(_v); }
        static inline Q_TN<long double> operator "" _TN_ (unsigned long long int _v) {
            return Q_TN<long double>(_v); }
    }



//
// Unit "GN"
//
    struct GN
    {
        using factor_t = std::ratio<1000000000, 1>; // 1e+09
        using dimensions_t = dimensions::Mass;
        using offset_t = std::ratio<0, 1>;
        using relative_t = GN;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "GN";
        }
    };
    template<typename Value = long double>
    using Q_GN = units::Quantity<Value, GN>;
    namespace literals
    {
        static inline Q_GN<long double> operator "" _GN_ (long double _v) {
            return Q_GN<long double>(_v); }
        static inline Q_GN<long double> operator "" _GN_ (unsigned long long int _v) {
            return Q_GN<long double>(_v); }
    }



//
// Unit "MN"
//
    struct MN
    {
        using factor_t = std::ratio<1000000, 1>; // 1e+06
        using dimensions_t = dimensions::Mass;
        using offset_t = std::ratio<0, 1>;
        using relative_t = MN;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "MN";
        }
    };
    template<typename Value = long double>
    using Q_MN = units::Quantity<Value, MN>;
    namespace literals
    {
        static inline Q_MN<long double> operator "" _MN_ (long double _v) {
            return Q_MN<long double>(_v); }
        static inline Q_MN<long double> operator "" _MN_ (unsigned long long int _v) {
            return Q_MN<long double>(_v); }
    }



//
// Unit "kN"
//
    struct kN
    {
        using factor_t = std::ratio<1000, 1>; // 1000
        using dimensions_t = dimensions::Mass;
        using offset_t = std::ratio<0, 1>;
        using relative_t = kN;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "kN";
        }
    };
    template<typename Value = long double>
    using Q_kN = units::Quantity<Value, kN>;
    namespace literals
    {
        static inline Q_kN<long double> operator "" _kN_ (long double _v) {
            return Q_kN<long double>(_v); }
        static inline Q_kN<long double> operator "" _kN_ (unsigned long long int _v) {
            return Q_kN<long double>(_v); }
    }



//
// Unit "hN"
//
    struct hN
    {
        using factor_t = std::ratio<100, 1>; // 100
        using dimensions_t = dimensions::Mass;
        using offset_t = std::ratio<0, 1>;
        using relative_t = hN;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "hN";
        }
    };
    template<typename Value = long double>
    using Q_hN = units::Quantity<Value, hN>;
    namespace literals
    {
        static inline Q_hN<long double> operator "" _hN_ (long double _v) {
            return Q_hN<long double>(_v); }
        static inline Q_hN<long double> operator "" _hN_ (unsigned long long int _v) {
            return Q_hN<long double>(_v); }
    }



//
// Unit "daN"
//
    struct daN
    {
        using factor_t = std::ratio<10, 1>; // 10
        using dimensions_t = dimensions::Mass;
        using offset_t = std::ratio<0, 1>;
        using relative_t = daN;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "daN";
        }
    };
    template<typename Value = long double>
    using Q_daN = units::Quantity<Value, daN>;
    namespace literals
    {
        static inline Q_daN<long double> operator "" _daN_ (long double _v) {
            return Q_daN<long double>(_v); }
        static inline Q_daN<long double> operator "" _daN_ (unsigned long long int _v) {
            return Q_daN<long double>(_v); }
    }



//
// Unit "N"
//
    struct N
    {
        using factor_t = std::ratio<1, 1>; // 1
        using dimensions_t = dimensions::Mass;
        using offset_t = std::ratio<0, 1>;
        using relative_t = N;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "N";
        }
    };
    template<typename Value = long double>
    using Q_N = units::Quantity<Value, N>;
    namespace literals
    {
        static inline Q_N<long double> operator "" _N_ (long double _v) {
            return Q_N<long double>(_v); }
        static inline Q_N<long double> operator "" _N_ (unsigned long long int _v) {
            return Q_N<long double>(_v); }
    }



//
// Unit "dN"
//
    struct dN
    {
        using factor_t = std::ratio<1, 10>; // 0.1
        using dimensions_t = dimensions::Mass;
        using offset_t = std::ratio<0, 1>;
        using relative_t = dN;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "dN";
        }
    };
    template<typename Value = long double>
    using Q_dN = units::Quantity<Value, dN>;
    namespace literals
    {
        static inline Q_dN<long double> operator "" _dN_ (long double _v) {
            return Q_dN<long double>(_v); }
        static inline Q_dN<long double> operator "" _dN_ (unsigned long long int _v) {
            return Q_dN<long double>(_v); }
    }



//
// Unit "cN"
//
    struct cN
    {
        using factor_t = std::ratio<1, 100>; // 0.01
        using dimensions_t = dimensions::Mass;
        using offset_t = std::ratio<0, 1>;
        using relative_t = cN;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "cN";
        }
    };
    template<typename Value = long double>
    using Q_cN = units::Quantity<Value, cN>;
    namespace literals
    {
        static inline Q_cN<long double> operator "" _cN_ (long double _v) {
            return Q_cN<long double>(_v); }
        static inline Q_cN<long double> operator "" _cN_ (unsigned long long int _v) {
            return Q_cN<long double>(_v); }
    }



//
// Unit "mN"
//
    struct mN
    {
        using factor_t = std::ratio<1, 1000>; // 0.001
        using dimensions_t = dimensions::Mass;
        using offset_t = std::ratio<0, 1>;
        using relative_t = mN;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "mN";
        }
    };
    template<typename Value = long double>
    using Q_mN = units::Quantity<Value, mN>;
    namespace literals
    {
        static inline Q_mN<long double> operator "" _mN_ (long double _v) {
            return Q_mN<long double>(_v); }
        static inline Q_mN<long double> operator "" _mN_ (unsigned long long int _v) {
            return Q_mN<long double>(_v); }
    }



//
// Unit "Egf"
//
    struct Egf
    {
        using factor_t = std::ratio<9806650000000000, 1>; // 9.80665e+15
        using dimensions_t = dimensions::Mass;
        using offset_t = std::ratio<0, 1>;
        using relative_t = Egf;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "Egf";
        }
    };
    template<typename Value = long double>
    using Q_Egf = units::Quantity<Value, Egf>;
    namespace literals
    {
        static inline Q_Egf<long double> operator "" _Egf_ (long double _v) {
            return Q_Egf<long double>(_v); }
        static inline Q_Egf<long double> operator "" _Egf_ (unsigned long long int _v) {
            return Q_Egf<long double>(_v); }
    }



//
// Unit "Pgf"
//
    struct Pgf
    {
        using factor_t = std::ratio<9806650000000, 1>; // 9.80665e+12
        using dimensions_t = dimensions::Mass;
        using offset_t = std::ratio<0, 1>;
        using relative_t = Pgf;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "Pgf";
        }
    };
    template<typename Value = long double>
    using Q_Pgf = units::Quantity<Value, Pgf>;
    namespace literals
    {
        static inline Q_Pgf<long double> operator "" _Pgf_ (long double _v) {
            return Q_Pgf<long double>(_v); }
        static inline Q_Pgf<long double> operator "" _Pgf_ (unsigned long long int _v) {
            return Q_Pgf<long double>(_v); }
    }



//
// Unit "Tgf"
//
    struct Tgf
    {
        using factor_t = std::ratio<9806650000, 1>; // 9.80665e+09
        using dimensions_t = dimensions::Mass;
        using offset_t = std::ratio<0, 1>;
        using relative_t = Tgf;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "Tgf";
        }
    };
    template<typename Value = long double>
    using Q_Tgf = units::Quantity<Value, Tgf>;
    namespace literals
    {
        static inline Q_Tgf<long double> operator "" _Tgf_ (long double _v) {
            return Q_Tgf<long double>(_v); }
        static inline Q_Tgf<long double> operator "" _Tgf_ (unsigned long long int _v) {
            return Q_Tgf<long double>(_v); }
    }



//
// Unit "Ggf"
//
    struct Ggf
    {
        using factor_t = std::ratio<9806650, 1>; // 9.80665e+06
        using dimensions_t = dimensions::Mass;
        using offset_t = std::ratio<0, 1>;
        using relative_t = Ggf;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "Ggf";
        }
    };
    template<typename Value = long double>
    using Q_Ggf = units::Quantity<Value, Ggf>;
    namespace literals
    {
        static inline Q_Ggf<long double> operator "" _Ggf_ (long double _v) {
            return Q_Ggf<long double>(_v); }
        static inline Q_Ggf<long double> operator "" _Ggf_ (unsigned long long int _v) {
            return Q_Ggf<long double>(_v); }
    }



//
// Unit "Mgf"
//
    struct Mgf
    {
        using factor_t = std::ratio<196133, 20>; // 9806.65
        using dimensions_t = dimensions::Mass;
        using offset_t = std::ratio<0, 1>;
        using relative_t = Mgf;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "Mgf";
        }
    };
    template<typename Value = long double>
    using Q_Mgf = units::Quantity<Value, Mgf>;
    namespace literals
    {
        static inline Q_Mgf<long double> operator "" _Mgf_ (long double _v) {
            return Q_Mgf<long double>(_v); }
        static inline Q_Mgf<long double> operator "" _Mgf_ (unsigned long long int _v) {
            return Q_Mgf<long double>(_v); }
    }



//
// Unit "kgf"
//
    struct kgf
    {
        using factor_t = std::ratio<51024, 5203>; // 9.80665
        using dimensions_t = dimensions::Mass;
        using offset_t = std::ratio<0, 1>;
        using relative_t = kgf;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "kgf";
        }
    };
    template<typename Value = long double>
    using Q_kgf = units::Quantity<Value, kgf>;
    namespace literals
    {
        static inline Q_kgf<long double> operator "" _kgf_ (long double _v) {
            return Q_kgf<long double>(_v); }
        static inline Q_kgf<long double> operator "" _kgf_ (unsigned long long int _v) {
            return Q_kgf<long double>(_v); }
    }



//
// Unit "hgf"
//
    struct hgf
    {
        using factor_t = std::ratio<6695, 6827>; // 0.980665
        using dimensions_t = dimensions::Mass;
        using offset_t = std::ratio<0, 1>;
        using relative_t = hgf;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "hgf";
        }
    };
    template<typename Value = long double>
    using Q_hgf = units::Quantity<Value, hgf>;
    namespace literals
    {
        static inline Q_hgf<long double> operator "" _hgf_ (long double _v) {
            return Q_hgf<long double>(_v); }
        static inline Q_hgf<long double> operator "" _hgf_ (unsigned long long int _v) {
            return Q_hgf<long double>(_v); }
    }



//
// Unit "dagf"
//
    struct dagf
    {
        using factor_t = std::ratio<705, 7189>; // 0.0980665
        using dimensions_t = dimensions::Mass;
        using offset_t = std::ratio<0, 1>;
        using relative_t = dagf;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "dagf";
        }
    };
    template<typename Value = long double>
    using Q_dagf = units::Quantity<Value, dagf>;
    namespace literals
    {
        static inline Q_dagf<long double> operator "" _dagf_ (long double _v) {
            return Q_dagf<long double>(_v); }
        static inline Q_dagf<long double> operator "" _dagf_ (unsigned long long int _v) {
            return Q_dagf<long double>(_v); }
    }



//
// Unit "gf"
//
    struct gf
    {
        using factor_t = std::ratio<35, 3569>; // 0.00980665
        using dimensions_t = dimensions::Mass;
        using offset_t = std::ratio<0, 1>;
        using relative_t = gf;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "gf";
        }
    };
    template<typename Value = long double>
    using Q_gf = units::Quantity<Value, gf>;
    namespace literals
    {
        static inline Q_gf<long double> operator "" _gf_ (long double _v) {
            return Q_gf<long double>(_v); }
        static inline Q_gf<long double> operator "" _gf_ (unsigned long long int _v) {
            return Q_gf<long double>(_v); }
    }



//
// Unit "dgf"
//
    struct dgf
    {
        using factor_t = std::ratio<7, 7138>; // 0.000980665
        using dimensions_t = dimensions::Mass;
        using offset_t = std::ratio<0, 1>;
        using relative_t = dgf;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "dgf";
        }
    };
    template<typename Value = long double>
    using Q_dgf = units::Quantity<Value, dgf>;
    namespace literals
    {
        static inline Q_dgf<long double> operator "" _dgf_ (long double _v) {
            return Q_dgf<long double>(_v); }
        static inline Q_dgf<long double> operator "" _dgf_ (unsigned long long int _v) {
            return Q_dgf<long double>(_v); }
    }



//
// Unit "cgf"
//
    struct cgf
    {
        using factor_t = std::ratio<6, 61183>; // 9.80665e-05
        using dimensions_t = dimensions::Mass;
        using offset_t = std::ratio<0, 1>;
        using relative_t = cgf;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "cgf";
        }
    };
    template<typename Value = long double>
    using Q_cgf = units::Quantity<Value, cgf>;
    namespace literals
    {
        static inline Q_cgf<long double> operator "" _cgf_ (long double _v) {
            return Q_cgf<long double>(_v); }
        static inline Q_cgf<long double> operator "" _cgf_ (unsigned long long int _v) {
            return Q_cgf<long double>(_v); }
    }



//
// Unit "mgf"
//
    struct mgf
    {
        using factor_t = std::ratio<8, 815773>; // 9.80665e-06
        using dimensions_t = dimensions::Mass;
        using offset_t = std::ratio<0, 1>;
        using relative_t = mgf;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "mgf";
        }
    };
    template<typename Value = long double>
    using Q_mgf = units::Quantity<Value, mgf>;
    namespace literals
    {
        static inline Q_mgf<long double> operator "" _mgf_ (long double _v) {
            return Q_mgf<long double>(_v); }
        static inline Q_mgf<long double> operator "" _mgf_ (unsigned long long int _v) {
            return Q_mgf<long double>(_v); }
    }



//
// Unit "lb"
//
    struct lb
    {
        using factor_t = std::ratio<125, 556>; // 0.22482
        using dimensions_t = dimensions::Mass;
        using offset_t = std::ratio<0, 1>;
        using relative_t = lb;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "lb";
        }
    };
    template<typename Value = long double>
    using Q_lb = units::Quantity<Value, lb>;
    namespace literals
    {
        static inline Q_lb<long double> operator "" _lb_ (long double _v) {
            return Q_lb<long double>(_v); }
        static inline Q_lb<long double> operator "" _lb_ (unsigned long long int _v) {
            return Q_lb<long double>(_v); }
    }



//
// Unit "pdl"
//
    struct pdl
    {
        using factor_t = std::ratio<5047, 698>; // 7.23066
        using dimensions_t = dimensions::Mass;
        using offset_t = std::ratio<0, 1>;
        using relative_t = pdl;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "pdl";
        }
    };
    template<typename Value = long double>
    using Q_pdl = units::Quantity<Value, pdl>;
    namespace literals
    {
        static inline Q_pdl<long double> operator "" _pdl_ (long double _v) {
            return Q_pdl<long double>(_v); }
        static inline Q_pdl<long double> operator "" _pdl_ (unsigned long long int _v) {
            return Q_pdl<long double>(_v); }
    }



//
// Unit "Em"
//
    struct Em
    {
        using factor_t = std::ratio<1000000000000000000, 1>; // 1e+18
        using dimensions_t = dimensions::Length;
        using offset_t = std::ratio<0, 1>;
        using relative_t = Em;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "Em";
        }
    };
    template<typename Value = long double>
    using Q_Em = units::Quantity<Value, Em>;
    namespace literals
    {
        static inline Q_Em<long double> operator "" _Em_ (long double _v) {
            return Q_Em<long double>(_v); }
        static inline Q_Em<long double> operator "" _Em_ (unsigned long long int _v) {
            return Q_Em<long double>(_v); }
    }



//
// Unit "Pm"
//
    struct Pm
    {
        using factor_t = std::ratio<1000000000000000, 1>; // 1e+15
        using dimensions_t = dimensions::Length;
        using offset_t = std::ratio<0, 1>;
        using relative_t = Pm;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "Pm";
        }
    };
    template<typename Value = long double>
    using Q_Pm = units::Quantity<Value, Pm>;
    namespace literals
    {
        static inline Q_Pm<long double> operator "" _Pm_ (long double _v) {
            return Q_Pm<long double>(_v); }
        static inline Q_Pm<long double> operator "" _Pm_ (unsigned long long int _v) {
            return Q_Pm<long double>(_v); }
    }



//
// Unit "Tm"
//
    struct Tm
    {
        using factor_t = std::ratio<1000000000000, 1>; // 1e+12
        using dimensions_t = dimensions::Length;
        using offset_t = std::ratio<0, 1>;
        using relative_t = Tm;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "Tm";
        }
    };
    template<typename Value = long double>
    using Q_Tm = units::Quantity<Value, Tm>;
    namespace literals
    {
        static inline Q_Tm<long double> operator "" _Tm_ (long double _v) {
            return Q_Tm<long double>(_v); }
        static inline Q_Tm<long double> operator "" _Tm_ (unsigned long long int _v) {
            return Q_Tm<long double>(_v); }
    }



//
// Unit "Gm"
//
    struct Gm
    {
        using factor_t = std::ratio<1000000000, 1>; // 1e+09
        using dimensions_t = dimensions::Length;
        using offset_t = std::ratio<0, 1>;
        using relative_t = Gm;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "Gm";
        }
    };
    template<typename Value = long double>
    using Q_Gm = units::Quantity<Value, Gm>;
    namespace literals
    {
        static inline Q_Gm<long double> operator "" _Gm_ (long double _v) {
            return Q_Gm<long double>(_v); }
        static inline Q_Gm<long double> operator "" _Gm_ (unsigned long long int _v) {
            return Q_Gm<long double>(_v); }
    }



//
// Unit "Mm"
//
    struct Mm
    {
        using factor_t = std::ratio<1000000, 1>; // 1e+06
        using dimensions_t = dimensions::Length;
        using offset_t = std::ratio<0, 1>;
        using relative_t = Mm;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "Mm";
        }
    };
    template<typename Value = long double>
    using Q_Mm = units::Quantity<Value, Mm>;
    namespace literals
    {
        static inline Q_Mm<long double> operator "" _Mm_ (long double _v) {
            return Q_Mm<long double>(_v); }
        static inline Q_Mm<long double> operator "" _Mm_ (unsigned long long int _v) {
            return Q_Mm<long double>(_v); }
    }



//
// Unit "km"
//
    struct km
    {
        using factor_t = std::ratio<1000, 1>; // 1000
        using dimensions_t = dimensions::Length;
        using offset_t = std::ratio<0, 1>;
        using relative_t = km;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "km";
        }
    };
    template<typename Value = long double>
    using Q_km = units::Quantity<Value, km>;
    namespace literals
    {
        static inline Q_km<long double> operator "" _km_ (long double _v) {
            return Q_km<long double>(_v); }
        static inline Q_km<long double> operator "" _km_ (unsigned long long int _v) {
            return Q_km<long double>(_v); }
    }



//
// Unit "hm"
//
    struct hm
    {
        using factor_t = std::ratio<100, 1>; // 100
        using dimensions_t = dimensions::Length;
        using offset_t = std::ratio<0, 1>;
        using relative_t = hm;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "hm";
        }
    };
    template<typename Value = long double>
    using Q_hm = units::Quantity<Value, hm>;
    namespace literals
    {
        static inline Q_hm<long double> operator "" _hm_ (long double _v) {
            return Q_hm<long double>(_v); }
        static inline Q_hm<long double> operator "" _hm_ (unsigned long long int _v) {
            return Q_hm<long double>(_v); }
    }



//
// Unit "dam"
//
    struct dam
    {
        using factor_t = std::ratio<10, 1>; // 10
        using dimensions_t = dimensions::Length;
        using offset_t = std::ratio<0, 1>;
        using relative_t = dam;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "dam";
        }
    };
    template<typename Value = long double>
    using Q_dam = units::Quantity<Value, dam>;
    namespace literals
    {
        static inline Q_dam<long double> operator "" _dam_ (long double _v) {
            return Q_dam<long double>(_v); }
        static inline Q_dam<long double> operator "" _dam_ (unsigned long long int _v) {
            return Q_dam<long double>(_v); }
    }



//
// Unit "m"
//
    struct m
    {
        using factor_t = std::ratio<1, 1>; // 1
        using dimensions_t = dimensions::Length;
        using offset_t = std::ratio<0, 1>;
        using relative_t = m;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "m";
        }
    };
    template<typename Value = long double>
    using Q_m = units::Quantity<Value, m>;
    namespace literals
    {
        static inline Q_m<long double> operator "" _m_ (long double _v) {
            return Q_m<long double>(_v); }
        static inline Q_m<long double> operator "" _m_ (unsigned long long int _v) {
            return Q_m<long double>(_v); }
    }



//
// Unit "dm"
//
    struct dm
    {
        using factor_t = std::ratio<1, 10>; // 0.1
        using dimensions_t = dimensions::Length;
        using offset_t = std::ratio<0, 1>;
        using relative_t = dm;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "dm";
        }
    };
    template<typename Value = long double>
    using Q_dm = units::Quantity<Value, dm>;
    namespace literals
    {
        static inline Q_dm<long double> operator "" _dm_ (long double _v) {
            return Q_dm<long double>(_v); }
        static inline Q_dm<long double> operator "" _dm_ (unsigned long long int _v) {
            return Q_dm<long double>(_v); }
    }



//
// Unit "cm"
//
    struct cm
    {
        using factor_t = std::ratio<1, 100>; // 0.01
        using dimensions_t = dimensions::Length;
        using offset_t = std::ratio<0, 1>;
        using relative_t = cm;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "cm";
        }
    };
    template<typename Value = long double>
    using Q_cm = units::Quantity<Value, cm>;
    namespace literals
    {
        static inline Q_cm<long double> operator "" _cm_ (long double _v) {
            return Q_cm<long double>(_v); }
        static inline Q_cm<long double> operator "" _cm_ (unsigned long long int _v) {
            return Q_cm<long double>(_v); }
    }



//
// Unit "mm"
//
    struct mm
    {
        using factor_t = std::ratio<1, 1000>; // 0.001
        using dimensions_t = dimensions::Length;
        using offset_t = std::ratio<0, 1>;
        using relative_t = mm;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "mm";
        }
    };
    template<typename Value = long double>
    using Q_mm = units::Quantity<Value, mm>;
    namespace literals
    {
        static inline Q_mm<long double> operator "" _mm_ (long double _v) {
            return Q_mm<long double>(_v); }
        static inline Q_mm<long double> operator "" _mm_ (unsigned long long int _v) {
            return Q_mm<long double>(_v); }
    }



//
// Unit "mi"
//
    struct mi
    {
        using factor_t = std::ratio<80467, 50>; // 1609.34
        using dimensions_t = dimensions::Length;
        using offset_t = std::ratio<0, 1>;
        using relative_t = mi;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "mi";
        }
    };
    template<typename Value = long double>
    using Q_mi = units::Quantity<Value, mi>;
    namespace literals
    {
        static inline Q_mi<long double> operator "" _mi_ (long double _v) {
            return Q_mi<long double>(_v); }
        static inline Q_mi<long double> operator "" _mi_ (unsigned long long int _v) {
            return Q_mi<long double>(_v); }
    }



//
// Unit "yd"
//
    struct yd
    {
        using factor_t = std::ratio<4557, 5000>; // 0.9114
        using dimensions_t = dimensions::Length;
        using offset_t = std::ratio<0, 1>;
        using relative_t = yd;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "yd";
        }
    };
    template<typename Value = long double>
    using Q_yd = units::Quantity<Value, yd>;
    namespace literals
    {
        static inline Q_yd<long double> operator "" _yd_ (long double _v) {
            return Q_yd<long double>(_v); }
        static inline Q_yd<long double> operator "" _yd_ (unsigned long long int _v) {
            return Q_yd<long double>(_v); }
    }



//
// Unit "ft"
//
    struct ft
    {
        using factor_t = std::ratio<381, 1250>; // 0.3048
        using dimensions_t = dimensions::Length;
        using offset_t = std::ratio<0, 1>;
        using relative_t = ft;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "ft";
        }
    };
    template<typename Value = long double>
    using Q_ft = units::Quantity<Value, ft>;
    namespace literals
    {
        static inline Q_ft<long double> operator "" _ft_ (long double _v) {
            return Q_ft<long double>(_v); }
        static inline Q_ft<long double> operator "" _ft_ (unsigned long long int _v) {
            return Q_ft<long double>(_v); }
    }



//
// Unit "in"
//
    struct in
    {
        using factor_t = std::ratio<127, 5000>; // 0.0254
        using dimensions_t = dimensions::Length;
        using offset_t = std::ratio<0, 1>;
        using relative_t = in;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "in";
        }
    };
    template<typename Value = long double>
    using Q_in = units::Quantity<Value, in>;
    namespace literals
    {
        static inline Q_in<long double> operator "" _in_ (long double _v) {
            return Q_in<long double>(_v); }
        static inline Q_in<long double> operator "" _in_ (unsigned long long int _v) {
            return Q_in<long double>(_v); }
    }



//
// Unit "Gm2"
//
    struct Gm2
    {
        using factor_t = std::ratio<1000000000000000000, 1>; // 1e+18
        using dimensions_t = dimensions::Area;
        using offset_t = std::ratio<0, 1>;
        using relative_t = Gm2;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "Gm2";
        }
    };
    template<typename Value = long double>
    using Q_Gm2 = units::Quantity<Value, Gm2>;
    namespace literals
    {
        static inline Q_Gm2<long double> operator "" _Gm2_ (long double _v) {
            return Q_Gm2<long double>(_v); }
        static inline Q_Gm2<long double> operator "" _Gm2_ (unsigned long long int _v) {
            return Q_Gm2<long double>(_v); }
    }



//
// Unit "Mm2"
//
    struct Mm2
    {
        using factor_t = std::ratio<1000000000000, 1>; // 1e+12
        using dimensions_t = dimensions::Area;
        using offset_t = std::ratio<0, 1>;
        using relative_t = Mm2;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "Mm2";
        }
    };
    template<typename Value = long double>
    using Q_Mm2 = units::Quantity<Value, Mm2>;
    namespace literals
    {
        static inline Q_Mm2<long double> operator "" _Mm2_ (long double _v) {
            return Q_Mm2<long double>(_v); }
        static inline Q_Mm2<long double> operator "" _Mm2_ (unsigned long long int _v) {
            return Q_Mm2<long double>(_v); }
    }



//
// Unit "km2"
//
    struct km2
    {
        using factor_t = std::ratio<1000000, 1>; // 1e+06
        using dimensions_t = dimensions::Area;
        using offset_t = std::ratio<0, 1>;
        using relative_t = km2;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "km2";
        }
    };
    template<typename Value = long double>
    using Q_km2 = units::Quantity<Value, km2>;
    namespace literals
    {
        static inline Q_km2<long double> operator "" _km2_ (long double _v) {
            return Q_km2<long double>(_v); }
        static inline Q_km2<long double> operator "" _km2_ (unsigned long long int _v) {
            return Q_km2<long double>(_v); }
    }



//
// Unit "hm2"
//
    struct hm2
    {
        using factor_t = std::ratio<10000, 1>; // 10000
        using dimensions_t = dimensions::Area;
        using offset_t = std::ratio<0, 1>;
        using relative_t = hm2;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "hm2";
        }
    };
    template<typename Value = long double>
    using Q_hm2 = units::Quantity<Value, hm2>;
    namespace literals
    {
        static inline Q_hm2<long double> operator "" _hm2_ (long double _v) {
            return Q_hm2<long double>(_v); }
        static inline Q_hm2<long double> operator "" _hm2_ (unsigned long long int _v) {
            return Q_hm2<long double>(_v); }
    }



//
// Unit "dam2"
//
    struct dam2
    {
        using factor_t = std::ratio<100, 1>; // 100
        using dimensions_t = dimensions::Area;
        using offset_t = std::ratio<0, 1>;
        using relative_t = dam2;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "dam2";
        }
    };
    template<typename Value = long double>
    using Q_dam2 = units::Quantity<Value, dam2>;
    namespace literals
    {
        static inline Q_dam2<long double> operator "" _dam2_ (long double _v) {
            return Q_dam2<long double>(_v); }
        static inline Q_dam2<long double> operator "" _dam2_ (unsigned long long int _v) {
            return Q_dam2<long double>(_v); }
    }



//
// Unit "m2"
//
    struct m2
    {
        using factor_t = std::ratio<1, 1>; // 1
        using dimensions_t = dimensions::Area;
        using offset_t = std::ratio<0, 1>;
        using relative_t = m2;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "m2";
        }
    };
    template<typename Value = long double>
    using Q_m2 = units::Quantity<Value, m2>;
    namespace literals
    {
        static inline Q_m2<long double> operator "" _m2_ (long double _v) {
            return Q_m2<long double>(_v); }
        static inline Q_m2<long double> operator "" _m2_ (unsigned long long int _v) {
            return Q_m2<long double>(_v); }
    }



//
// Unit "dm2"
//
    struct dm2
    {
        using factor_t = std::ratio<1, 100>; // 0.01
        using dimensions_t = dimensions::Area;
        using offset_t = std::ratio<0, 1>;
        using relative_t = dm2;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "dm2";
        }
    };
    template<typename Value = long double>
    using Q_dm2 = units::Quantity<Value, dm2>;
    namespace literals
    {
        static inline Q_dm2<long double> operator "" _dm2_ (long double _v) {
            return Q_dm2<long double>(_v); }
        static inline Q_dm2<long double> operator "" _dm2_ (unsigned long long int _v) {
            return Q_dm2<long double>(_v); }
    }



//
// Unit "cm2"
//
    struct cm2
    {
        using factor_t = std::ratio<1, 10000>; // 0.0001
        using dimensions_t = dimensions::Area;
        using offset_t = std::ratio<0, 1>;
        using relative_t = cm2;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "cm2";
        }
    };
    template<typename Value = long double>
    using Q_cm2 = units::Quantity<Value, cm2>;
    namespace literals
    {
        static inline Q_cm2<long double> operator "" _cm2_ (long double _v) {
            return Q_cm2<long double>(_v); }
        static inline Q_cm2<long double> operator "" _cm2_ (unsigned long long int _v) {
            return Q_cm2<long double>(_v); }
    }



//
// Unit "mi2"
//
    struct mi2
    {
        using factor_t = std::ratio<6474938089, 2500>; // 2.58998e+06
        using dimensions_t = dimensions::Area;
        using offset_t = std::ratio<0, 1>;
        using relative_t = mi2;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "mi2";
        }
    };
    template<typename Value = long double>
    using Q_mi2 = units::Quantity<Value, mi2>;
    namespace literals
    {
        static inline Q_mi2<long double> operator "" _mi2_ (long double _v) {
            return Q_mi2<long double>(_v); }
        static inline Q_mi2<long double> operator "" _mi2_ (unsigned long long int _v) {
            return Q_mi2<long double>(_v); }
    }



//
// Unit "yd2"
//
    struct yd2
    {
        using factor_t = std::ratio<1393, 1677>; // 0.83065
        using dimensions_t = dimensions::Area;
        using offset_t = std::ratio<0, 1>;
        using relative_t = yd2;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "yd2";
        }
    };
    template<typename Value = long double>
    using Q_yd2 = units::Quantity<Value, yd2>;
    namespace literals
    {
        static inline Q_yd2<long double> operator "" _yd2_ (long double _v) {
            return Q_yd2<long double>(_v); }
        static inline Q_yd2<long double> operator "" _yd2_ (unsigned long long int _v) {
            return Q_yd2<long double>(_v); }
    }



//
// Unit "ft2"
//
    struct ft2
    {
        using factor_t = std::ratio<72, 775>; // 0.092903
        using dimensions_t = dimensions::Area;
        using offset_t = std::ratio<0, 1>;
        using relative_t = ft2;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "ft2";
        }
    };
    template<typename Value = long double>
    using Q_ft2 = units::Quantity<Value, ft2>;
    namespace literals
    {
        static inline Q_ft2<long double> operator "" _ft2_ (long double _v) {
            return Q_ft2<long double>(_v); }
        static inline Q_ft2<long double> operator "" _ft2_ (unsigned long long int _v) {
            return Q_ft2<long double>(_v); }
    }



//
// Unit "in2"
//
    struct in2
    {
        using factor_t = std::ratio<1, 1550>; // 0.00064516
        using dimensions_t = dimensions::Area;
        using offset_t = std::ratio<0, 1>;
        using relative_t = in2;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "in2";
        }
    };
    template<typename Value = long double>
    using Q_in2 = units::Quantity<Value, in2>;
    namespace literals
    {
        static inline Q_in2<long double> operator "" _in2_ (long double _v) {
            return Q_in2<long double>(_v); }
        static inline Q_in2<long double> operator "" _in2_ (unsigned long long int _v) {
            return Q_in2<long double>(_v); }
    }



//
// Unit "Mm3"
//
    struct Mm3
    {
        using factor_t = std::ratio<1000000000000000000, 1>; // 1e+18
        using dimensions_t = dimensions::Area;
        using offset_t = std::ratio<0, 1>;
        using relative_t = Mm3;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "Mm3";
        }
    };
    template<typename Value = long double>
    using Q_Mm3 = units::Quantity<Value, Mm3>;
    namespace literals
    {
        static inline Q_Mm3<long double> operator "" _Mm3_ (long double _v) {
            return Q_Mm3<long double>(_v); }
        static inline Q_Mm3<long double> operator "" _Mm3_ (unsigned long long int _v) {
            return Q_Mm3<long double>(_v); }
    }



//
// Unit "km3"
//
    struct km3
    {
        using factor_t = std::ratio<1000000000, 1>; // 1e+09
        using dimensions_t = dimensions::Area;
        using offset_t = std::ratio<0, 1>;
        using relative_t = km3;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "km3";
        }
    };
    template<typename Value = long double>
    using Q_km3 = units::Quantity<Value, km3>;
    namespace literals
    {
        static inline Q_km3<long double> operator "" _km3_ (long double _v) {
            return Q_km3<long double>(_v); }
        static inline Q_km3<long double> operator "" _km3_ (unsigned long long int _v) {
            return Q_km3<long double>(_v); }
    }



//
// Unit "hm3"
//
    struct hm3
    {
        using factor_t = std::ratio<1000000, 1>; // 1e+06
        using dimensions_t = dimensions::Area;
        using offset_t = std::ratio<0, 1>;
        using relative_t = hm3;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "hm3";
        }
    };
    template<typename Value = long double>
    using Q_hm3 = units::Quantity<Value, hm3>;
    namespace literals
    {
        static inline Q_hm3<long double> operator "" _hm3_ (long double _v) {
            return Q_hm3<long double>(_v); }
        static inline Q_hm3<long double> operator "" _hm3_ (unsigned long long int _v) {
            return Q_hm3<long double>(_v); }
    }



//
// Unit "dam3"
//
    struct dam3
    {
        using factor_t = std::ratio<1000, 1>; // 1000
        using dimensions_t = dimensions::Area;
        using offset_t = std::ratio<0, 1>;
        using relative_t = dam3;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "dam3";
        }
    };
    template<typename Value = long double>
    using Q_dam3 = units::Quantity<Value, dam3>;
    namespace literals
    {
        static inline Q_dam3<long double> operator "" _dam3_ (long double _v) {
            return Q_dam3<long double>(_v); }
        static inline Q_dam3<long double> operator "" _dam3_ (unsigned long long int _v) {
            return Q_dam3<long double>(_v); }
    }



//
// Unit "m3"
//
    struct m3
    {
        using factor_t = std::ratio<1, 1>; // 1
        using dimensions_t = dimensions::Area;
        using offset_t = std::ratio<0, 1>;
        using relative_t = m3;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "m3";
        }
    };
    template<typename Value = long double>
    using Q_m3 = units::Quantity<Value, m3>;
    namespace literals
    {
        static inline Q_m3<long double> operator "" _m3_ (long double _v) {
            return Q_m3<long double>(_v); }
        static inline Q_m3<long double> operator "" _m3_ (unsigned long long int _v) {
            return Q_m3<long double>(_v); }
    }



//
// Unit "dm3"
//
    struct dm3
    {
        using factor_t = std::ratio<1, 1000>; // 0.001
        using dimensions_t = dimensions::Area;
        using offset_t = std::ratio<0, 1>;
        using relative_t = dm3;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "dm3";
        }
    };
    template<typename Value = long double>
    using Q_dm3 = units::Quantity<Value, dm3>;
    namespace literals
    {
        static inline Q_dm3<long double> operator "" _dm3_ (long double _v) {
            return Q_dm3<long double>(_v); }
        static inline Q_dm3<long double> operator "" _dm3_ (unsigned long long int _v) {
            return Q_dm3<long double>(_v); }
    }



//
// Unit "cm3"
//
    struct cm3
    {
        using factor_t = std::ratio<1, 1000000>; // 1e-06
        using dimensions_t = dimensions::Area;
        using offset_t = std::ratio<0, 1>;
        using relative_t = cm3;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "cm3";
        }
    };
    template<typename Value = long double>
    using Q_cm3 = units::Quantity<Value, cm3>;
    namespace literals
    {
        static inline Q_cm3<long double> operator "" _cm3_ (long double _v) {
            return Q_cm3<long double>(_v); }
        static inline Q_cm3<long double> operator "" _cm3_ (unsigned long long int _v) {
            return Q_cm3<long double>(_v); }
    }



//
// Unit "mi3"
//
    struct mi3
    {
        using factor_t = std::ratio<2480049693668, 595>; // 4.16815e+09
        using dimensions_t = dimensions::Area;
        using offset_t = std::ratio<0, 1>;
        using relative_t = mi3;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "mi3";
        }
    };
    template<typename Value = long double>
    using Q_mi3 = units::Quantity<Value, mi3>;
    namespace literals
    {
        static inline Q_mi3<long double> operator "" _mi3_ (long double _v) {
            return Q_mi3<long double>(_v); }
        static inline Q_mi3<long double> operator "" _mi3_ (unsigned long long int _v) {
            return Q_mi3<long double>(_v); }
    }



//
// Unit "yd3"
//
    struct yd3
    {
        using factor_t = std::ratio<617, 815>; // 0.757054
        using dimensions_t = dimensions::Area;
        using offset_t = std::ratio<0, 1>;
        using relative_t = yd3;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "yd3";
        }
    };
    template<typename Value = long double>
    using Q_yd3 = units::Quantity<Value, yd3>;
    namespace literals
    {
        static inline Q_yd3<long double> operator "" _yd3_ (long double _v) {
            return Q_yd3<long double>(_v); }
        static inline Q_yd3<long double> operator "" _yd3_ (unsigned long long int _v) {
            return Q_yd3<long double>(_v); }
    }



//
// Unit "ft3"
//
    struct ft3
    {
        using factor_t = std::ratio<19, 671>; // 0.0283168
        using dimensions_t = dimensions::Area;
        using offset_t = std::ratio<0, 1>;
        using relative_t = ft3;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "ft3";
        }
    };
    template<typename Value = long double>
    using Q_ft3 = units::Quantity<Value, ft3>;
    namespace literals
    {
        static inline Q_ft3<long double> operator "" _ft3_ (long double _v) {
            return Q_ft3<long double>(_v); }
        static inline Q_ft3<long double> operator "" _ft3_ (unsigned long long int _v) {
            return Q_ft3<long double>(_v); }
    }



//
// Unit "in3"
//
    struct in3
    {
        using factor_t = std::ratio<1, 61024>; // 1.63871e-05
        using dimensions_t = dimensions::Area;
        using offset_t = std::ratio<0, 1>;
        using relative_t = in3;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "in3";
        }
    };
    template<typename Value = long double>
    using Q_in3 = units::Quantity<Value, in3>;
    namespace literals
    {
        static inline Q_in3<long double> operator "" _in3_ (long double _v) {
            return Q_in3<long double>(_v); }
        static inline Q_in3<long double> operator "" _in3_ (unsigned long long int _v) {
            return Q_in3<long double>(_v); }
    }



//
// Unit "Es"
//
    struct Es
    {
        using factor_t = std::ratio<1000000000000000000, 1>; // 1e+18
        using dimensions_t = dimensions::Time;
        using offset_t = std::ratio<0, 1>;
        using relative_t = Es;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "Es";
        }
    };
    template<typename Value = long double>
    using Q_Es = units::Quantity<Value, Es>;
    namespace literals
    {
        static inline Q_Es<long double> operator "" _Es_ (long double _v) {
            return Q_Es<long double>(_v); }
        static inline Q_Es<long double> operator "" _Es_ (unsigned long long int _v) {
            return Q_Es<long double>(_v); }
    }



//
// Unit "Ps"
//
    struct Ps
    {
        using factor_t = std::ratio<1000000000000000, 1>; // 1e+15
        using dimensions_t = dimensions::Time;
        using offset_t = std::ratio<0, 1>;
        using relative_t = Ps;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "Ps";
        }
    };
    template<typename Value = long double>
    using Q_Ps = units::Quantity<Value, Ps>;
    namespace literals
    {
        static inline Q_Ps<long double> operator "" _Ps_ (long double _v) {
            return Q_Ps<long double>(_v); }
        static inline Q_Ps<long double> operator "" _Ps_ (unsigned long long int _v) {
            return Q_Ps<long double>(_v); }
    }



//
// Unit "Ts"
//
    struct Ts
    {
        using factor_t = std::ratio<1000000000000, 1>; // 1e+12
        using dimensions_t = dimensions::Time;
        using offset_t = std::ratio<0, 1>;
        using relative_t = Ts;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "Ts";
        }
    };
    template<typename Value = long double>
    using Q_Ts = units::Quantity<Value, Ts>;
    namespace literals
    {
        static inline Q_Ts<long double> operator "" _Ts_ (long double _v) {
            return Q_Ts<long double>(_v); }
        static inline Q_Ts<long double> operator "" _Ts_ (unsigned long long int _v) {
            return Q_Ts<long double>(_v); }
    }



//
// Unit "Gs"
//
    struct Gs
    {
        using factor_t = std::ratio<1000000000, 1>; // 1e+09
        using dimensions_t = dimensions::Time;
        using offset_t = std::ratio<0, 1>;
        using relative_t = Gs;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "Gs";
        }
    };
    template<typename Value = long double>
    using Q_Gs = units::Quantity<Value, Gs>;
    namespace literals
    {
        static inline Q_Gs<long double> operator "" _Gs_ (long double _v) {
            return Q_Gs<long double>(_v); }
        static inline Q_Gs<long double> operator "" _Gs_ (unsigned long long int _v) {
            return Q_Gs<long double>(_v); }
    }



//
// Unit "Ms"
//
    struct Ms
    {
        using factor_t = std::ratio<1000000, 1>; // 1e+06
        using dimensions_t = dimensions::Time;
        using offset_t = std::ratio<0, 1>;
        using relative_t = Ms;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "Ms";
        }
    };
    template<typename Value = long double>
    using Q_Ms = units::Quantity<Value, Ms>;
    namespace literals
    {
        static inline Q_Ms<long double> operator "" _Ms_ (long double _v) {
            return Q_Ms<long double>(_v); }
        static inline Q_Ms<long double> operator "" _Ms_ (unsigned long long int _v) {
            return Q_Ms<long double>(_v); }
    }



//
// Unit "ks"
//
    struct ks
    {
        using factor_t = std::ratio<1000, 1>; // 1000
        using dimensions_t = dimensions::Time;
        using offset_t = std::ratio<0, 1>;
        using relative_t = ks;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "ks";
        }
    };
    template<typename Value = long double>
    using Q_ks = units::Quantity<Value, ks>;
    namespace literals
    {
        static inline Q_ks<long double> operator "" _ks_ (long double _v) {
            return Q_ks<long double>(_v); }
        static inline Q_ks<long double> operator "" _ks_ (unsigned long long int _v) {
            return Q_ks<long double>(_v); }
    }



//
// Unit "hs"
//
    struct hs
    {
        using factor_t = std::ratio<100, 1>; // 100
        using dimensions_t = dimensions::Time;
        using offset_t = std::ratio<0, 1>;
        using relative_t = hs;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "hs";
        }
    };
    template<typename Value = long double>
    using Q_hs = units::Quantity<Value, hs>;
    namespace literals
    {
        static inline Q_hs<long double> operator "" _hs_ (long double _v) {
            return Q_hs<long double>(_v); }
        static inline Q_hs<long double> operator "" _hs_ (unsigned long long int _v) {
            return Q_hs<long double>(_v); }
    }



//
// Unit "das"
//
    struct das
    {
        using factor_t = std::ratio<10, 1>; // 10
        using dimensions_t = dimensions::Time;
        using offset_t = std::ratio<0, 1>;
        using relative_t = das;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "das";
        }
    };
    template<typename Value = long double>
    using Q_das = units::Quantity<Value, das>;
    namespace literals
    {
        static inline Q_das<long double> operator "" _das_ (long double _v) {
            return Q_das<long double>(_v); }
        static inline Q_das<long double> operator "" _das_ (unsigned long long int _v) {
            return Q_das<long double>(_v); }
    }



//
// Unit "s"
//
    struct s
    {
        using factor_t = std::ratio<1, 1>; // 1
        using dimensions_t = dimensions::Time;
        using offset_t = std::ratio<0, 1>;
        using relative_t = s;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "s";
        }
    };
    template<typename Value = long double>
    using Q_s = units::Quantity<Value, s>;
    namespace literals
    {
        static inline Q_s<long double> operator "" _s_ (long double _v) {
            return Q_s<long double>(_v); }
        static inline Q_s<long double> operator "" _s_ (unsigned long long int _v) {
            return Q_s<long double>(_v); }
    }



//
// Unit "ds"
//
    struct ds
    {
        using factor_t = std::ratio<1, 10>; // 0.1
        using dimensions_t = dimensions::Time;
        using offset_t = std::ratio<0, 1>;
        using relative_t = ds;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "ds";
        }
    };
    template<typename Value = long double>
    using Q_ds = units::Quantity<Value, ds>;
    namespace literals
    {
        static inline Q_ds<long double> operator "" _ds_ (long double _v) {
            return Q_ds<long double>(_v); }
        static inline Q_ds<long double> operator "" _ds_ (unsigned long long int _v) {
            return Q_ds<long double>(_v); }
    }



//
// Unit "cs"
//
    struct cs
    {
        using factor_t = std::ratio<1, 100>; // 0.01
        using dimensions_t = dimensions::Time;
        using offset_t = std::ratio<0, 1>;
        using relative_t = cs;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "cs";
        }
    };
    template<typename Value = long double>
    using Q_cs = units::Quantity<Value, cs>;
    namespace literals
    {
        static inline Q_cs<long double> operator "" _cs_ (long double _v) {
            return Q_cs<long double>(_v); }
        static inline Q_cs<long double> operator "" _cs_ (unsigned long long int _v) {
            return Q_cs<long double>(_v); }
    }



//
// Unit "ms"
//
    struct ms
    {
        using factor_t = std::ratio<1, 1000>; // 0.001
        using dimensions_t = dimensions::Time;
        using offset_t = std::ratio<0, 1>;
        using relative_t = ms;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "ms";
        }
    };
    template<typename Value = long double>
    using Q_ms = units::Quantity<Value, ms>;
    namespace literals
    {
        static inline Q_ms<long double> operator "" _ms_ (long double _v) {
            return Q_ms<long double>(_v); }
        static inline Q_ms<long double> operator "" _ms_ (unsigned long long int _v) {
            return Q_ms<long double>(_v); }
    }



//
// Unit "min"
//
    struct min
    {
        using factor_t = std::ratio<60, 1>; // 60
        using dimensions_t = dimensions::Time;
        using offset_t = std::ratio<0, 1>;
        using relative_t = min;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "min";
        }
    };
    template<typename Value = long double>
    using Q_min = units::Quantity<Value, min>;
    namespace literals
    {
        static inline Q_min<long double> operator "" _min_ (long double _v) {
            return Q_min<long double>(_v); }
        static inline Q_min<long double> operator "" _min_ (unsigned long long int _v) {
            return Q_min<long double>(_v); }
    }



//
// Unit "hr"
//
    struct hr
    {
        using factor_t = std::ratio<3600, 1>; // 3600
        using dimensions_t = dimensions::Time;
        using offset_t = std::ratio<0, 1>;
        using relative_t = hr;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "hr";
        }
    };
    template<typename Value = long double>
    using Q_hr = units::Quantity<Value, hr>;
    namespace literals
    {
        static inline Q_hr<long double> operator "" _hr_ (long double _v) {
            return Q_hr<long double>(_v); }
        static inline Q_hr<long double> operator "" _hr_ (unsigned long long int _v) {
            return Q_hr<long double>(_v); }
    }



//
// Unit "day"
//
    struct day
    {
        using factor_t = std::ratio<86400, 1>; // 86400
        using dimensions_t = dimensions::Time;
        using offset_t = std::ratio<0, 1>;
        using relative_t = day;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "day";
        }
    };
    template<typename Value = long double>
    using Q_day = units::Quantity<Value, day>;
    namespace literals
    {
        static inline Q_day<long double> operator "" _day_ (long double _v) {
            return Q_day<long double>(_v); }
        static inline Q_day<long double> operator "" _day_ (unsigned long long int _v) {
            return Q_day<long double>(_v); }
    }



//
// Unit "EHz"
//
    struct EHz
    {
        using factor_t = std::ratio<1000000000000000000, 1>; // 1e+18
        using dimensions_t = dimensions::Frequency;
        using offset_t = std::ratio<0, 1>;
        using relative_t = EHz;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "EHz";
        }
    };
    template<typename Value = long double>
    using Q_EHz = units::Quantity<Value, EHz>;
    namespace literals
    {
        static inline Q_EHz<long double> operator "" _EHz_ (long double _v) {
            return Q_EHz<long double>(_v); }
        static inline Q_EHz<long double> operator "" _EHz_ (unsigned long long int _v) {
            return Q_EHz<long double>(_v); }
    }



//
// Unit "PHz"
//
    struct PHz
    {
        using factor_t = std::ratio<1000000000000000, 1>; // 1e+15
        using dimensions_t = dimensions::Frequency;
        using offset_t = std::ratio<0, 1>;
        using relative_t = PHz;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "PHz";
        }
    };
    template<typename Value = long double>
    using Q_PHz = units::Quantity<Value, PHz>;
    namespace literals
    {
        static inline Q_PHz<long double> operator "" _PHz_ (long double _v) {
            return Q_PHz<long double>(_v); }
        static inline Q_PHz<long double> operator "" _PHz_ (unsigned long long int _v) {
            return Q_PHz<long double>(_v); }
    }



//
// Unit "THz"
//
    struct THz
    {
        using factor_t = std::ratio<1000000000000, 1>; // 1e+12
        using dimensions_t = dimensions::Frequency;
        using offset_t = std::ratio<0, 1>;
        using relative_t = THz;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "THz";
        }
    };
    template<typename Value = long double>
    using Q_THz = units::Quantity<Value, THz>;
    namespace literals
    {
        static inline Q_THz<long double> operator "" _THz_ (long double _v) {
            return Q_THz<long double>(_v); }
        static inline Q_THz<long double> operator "" _THz_ (unsigned long long int _v) {
            return Q_THz<long double>(_v); }
    }



//
// Unit "GHz"
//
    struct GHz
    {
        using factor_t = std::ratio<1000000000, 1>; // 1e+09
        using dimensions_t = dimensions::Frequency;
        using offset_t = std::ratio<0, 1>;
        using relative_t = GHz;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "GHz";
        }
    };
    template<typename Value = long double>
    using Q_GHz = units::Quantity<Value, GHz>;
    namespace literals
    {
        static inline Q_GHz<long double> operator "" _GHz_ (long double _v) {
            return Q_GHz<long double>(_v); }
        static inline Q_GHz<long double> operator "" _GHz_ (unsigned long long int _v) {
            return Q_GHz<long double>(_v); }
    }



//
// Unit "MHz"
//
    struct MHz
    {
        using factor_t = std::ratio<1000000, 1>; // 1e+06
        using dimensions_t = dimensions::Frequency;
        using offset_t = std::ratio<0, 1>;
        using relative_t = MHz;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "MHz";
        }
    };
    template<typename Value = long double>
    using Q_MHz = units::Quantity<Value, MHz>;
    namespace literals
    {
        static inline Q_MHz<long double> operator "" _MHz_ (long double _v) {
            return Q_MHz<long double>(_v); }
        static inline Q_MHz<long double> operator "" _MHz_ (unsigned long long int _v) {
            return Q_MHz<long double>(_v); }
    }



//
// Unit "kHz"
//
    struct kHz
    {
        using factor_t = std::ratio<1000, 1>; // 1000
        using dimensions_t = dimensions::Frequency;
        using offset_t = std::ratio<0, 1>;
        using relative_t = kHz;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "kHz";
        }
    };
    template<typename Value = long double>
    using Q_kHz = units::Quantity<Value, kHz>;
    namespace literals
    {
        static inline Q_kHz<long double> operator "" _kHz_ (long double _v) {
            return Q_kHz<long double>(_v); }
        static inline Q_kHz<long double> operator "" _kHz_ (unsigned long long int _v) {
            return Q_kHz<long double>(_v); }
    }



//
// Unit "hHz"
//
    struct hHz
    {
        using factor_t = std::ratio<100, 1>; // 100
        using dimensions_t = dimensions::Frequency;
        using offset_t = std::ratio<0, 1>;
        using relative_t = hHz;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "hHz";
        }
    };
    template<typename Value = long double>
    using Q_hHz = units::Quantity<Value, hHz>;
    namespace literals
    {
        static inline Q_hHz<long double> operator "" _hHz_ (long double _v) {
            return Q_hHz<long double>(_v); }
        static inline Q_hHz<long double> operator "" _hHz_ (unsigned long long int _v) {
            return Q_hHz<long double>(_v); }
    }



//
// Unit "daHz"
//
    struct daHz
    {
        using factor_t = std::ratio<10, 1>; // 10
        using dimensions_t = dimensions::Frequency;
        using offset_t = std::ratio<0, 1>;
        using relative_t = daHz;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "daHz";
        }
    };
    template<typename Value = long double>
    using Q_daHz = units::Quantity<Value, daHz>;
    namespace literals
    {
        static inline Q_daHz<long double> operator "" _daHz_ (long double _v) {
            return Q_daHz<long double>(_v); }
        static inline Q_daHz<long double> operator "" _daHz_ (unsigned long long int _v) {
            return Q_daHz<long double>(_v); }
    }



//
// Unit "Hz"
//
    struct Hz
    {
        using factor_t = std::ratio<1, 1>; // 1
        using dimensions_t = dimensions::Frequency;
        using offset_t = std::ratio<0, 1>;
        using relative_t = Hz;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "Hz";
        }
    };
    template<typename Value = long double>
    using Q_Hz = units::Quantity<Value, Hz>;
    namespace literals
    {
        static inline Q_Hz<long double> operator "" _Hz_ (long double _v) {
            return Q_Hz<long double>(_v); }
        static inline Q_Hz<long double> operator "" _Hz_ (unsigned long long int _v) {
            return Q_Hz<long double>(_v); }
    }



//
// Unit "dHz"
//
    struct dHz
    {
        using factor_t = std::ratio<1, 10>; // 0.1
        using dimensions_t = dimensions::Frequency;
        using offset_t = std::ratio<0, 1>;
        using relative_t = dHz;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "dHz";
        }
    };
    template<typename Value = long double>
    using Q_dHz = units::Quantity<Value, dHz>;
    namespace literals
    {
        static inline Q_dHz<long double> operator "" _dHz_ (long double _v) {
            return Q_dHz<long double>(_v); }
        static inline Q_dHz<long double> operator "" _dHz_ (unsigned long long int _v) {
            return Q_dHz<long double>(_v); }
    }



//
// Unit "cHz"
//
    struct cHz
    {
        using factor_t = std::ratio<1, 100>; // 0.01
        using dimensions_t = dimensions::Frequency;
        using offset_t = std::ratio<0, 1>;
        using relative_t = cHz;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "cHz";
        }
    };
    template<typename Value = long double>
    using Q_cHz = units::Quantity<Value, cHz>;
    namespace literals
    {
        static inline Q_cHz<long double> operator "" _cHz_ (long double _v) {
            return Q_cHz<long double>(_v); }
        static inline Q_cHz<long double> operator "" _cHz_ (unsigned long long int _v) {
            return Q_cHz<long double>(_v); }
    }



//
// Unit "mHz"
//
    struct mHz
    {
        using factor_t = std::ratio<1, 1000>; // 0.001
        using dimensions_t = dimensions::Frequency;
        using offset_t = std::ratio<0, 1>;
        using relative_t = mHz;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "mHz";
        }
    };
    template<typename Value = long double>
    using Q_mHz = units::Quantity<Value, mHz>;
    namespace literals
    {
        static inline Q_mHz<long double> operator "" _mHz_ (long double _v) {
            return Q_mHz<long double>(_v); }
        static inline Q_mHz<long double> operator "" _mHz_ (unsigned long long int _v) {
            return Q_mHz<long double>(_v); }
    }



//
// Unit "Em_per_s"
//
    struct Em_per_s
    {
        using factor_t = std::ratio<1000000000000000000, 1>; // 1e+18
        using dimensions_t = dimensions::Velocity;
        using offset_t = std::ratio<0, 1>;
        using relative_t = Em_per_s;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "Em_per_s";
        }
    };
    template<typename Value = long double>
    using Q_Em_per_s = units::Quantity<Value, Em_per_s>;
    namespace literals
    {
        static inline Q_Em_per_s<long double> operator "" _Em_per_s_ (long double _v) {
            return Q_Em_per_s<long double>(_v); }
        static inline Q_Em_per_s<long double> operator "" _Em_per_s_ (unsigned long long int _v) {
            return Q_Em_per_s<long double>(_v); }
    }



//
// Unit "Pm_per_s"
//
    struct Pm_per_s
    {
        using factor_t = std::ratio<1000000000000000, 1>; // 1e+15
        using dimensions_t = dimensions::Velocity;
        using offset_t = std::ratio<0, 1>;
        using relative_t = Pm_per_s;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "Pm_per_s";
        }
    };
    template<typename Value = long double>
    using Q_Pm_per_s = units::Quantity<Value, Pm_per_s>;
    namespace literals
    {
        static inline Q_Pm_per_s<long double> operator "" _Pm_per_s_ (long double _v) {
            return Q_Pm_per_s<long double>(_v); }
        static inline Q_Pm_per_s<long double> operator "" _Pm_per_s_ (unsigned long long int _v) {
            return Q_Pm_per_s<long double>(_v); }
    }



//
// Unit "Tm_per_s"
//
    struct Tm_per_s
    {
        using factor_t = std::ratio<1000000000000, 1>; // 1e+12
        using dimensions_t = dimensions::Velocity;
        using offset_t = std::ratio<0, 1>;
        using relative_t = Tm_per_s;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "Tm_per_s";
        }
    };
    template<typename Value = long double>
    using Q_Tm_per_s = units::Quantity<Value, Tm_per_s>;
    namespace literals
    {
        static inline Q_Tm_per_s<long double> operator "" _Tm_per_s_ (long double _v) {
            return Q_Tm_per_s<long double>(_v); }
        static inline Q_Tm_per_s<long double> operator "" _Tm_per_s_ (unsigned long long int _v) {
            return Q_Tm_per_s<long double>(_v); }
    }



//
// Unit "Gm_per_s"
//
    struct Gm_per_s
    {
        using factor_t = std::ratio<1000000000, 1>; // 1e+09
        using dimensions_t = dimensions::Velocity;
        using offset_t = std::ratio<0, 1>;
        using relative_t = Gm_per_s;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "Gm_per_s";
        }
    };
    template<typename Value = long double>
    using Q_Gm_per_s = units::Quantity<Value, Gm_per_s>;
    namespace literals
    {
        static inline Q_Gm_per_s<long double> operator "" _Gm_per_s_ (long double _v) {
            return Q_Gm_per_s<long double>(_v); }
        static inline Q_Gm_per_s<long double> operator "" _Gm_per_s_ (unsigned long long int _v) {
            return Q_Gm_per_s<long double>(_v); }
    }



//
// Unit "Mm_per_s"
//
    struct Mm_per_s
    {
        using factor_t = std::ratio<1000000, 1>; // 1e+06
        using dimensions_t = dimensions::Velocity;
        using offset_t = std::ratio<0, 1>;
        using relative_t = Mm_per_s;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "Mm_per_s";
        }
    };
    template<typename Value = long double>
    using Q_Mm_per_s = units::Quantity<Value, Mm_per_s>;
    namespace literals
    {
        static inline Q_Mm_per_s<long double> operator "" _Mm_per_s_ (long double _v) {
            return Q_Mm_per_s<long double>(_v); }
        static inline Q_Mm_per_s<long double> operator "" _Mm_per_s_ (unsigned long long int _v) {
            return Q_Mm_per_s<long double>(_v); }
    }



//
// Unit "km_per_s"
//
    struct km_per_s
    {
        using factor_t = std::ratio<1000, 1>; // 1000
        using dimensions_t = dimensions::Velocity;
        using offset_t = std::ratio<0, 1>;
        using relative_t = km_per_s;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "km_per_s";
        }
    };
    template<typename Value = long double>
    using Q_km_per_s = units::Quantity<Value, km_per_s>;
    namespace literals
    {
        static inline Q_km_per_s<long double> operator "" _km_per_s_ (long double _v) {
            return Q_km_per_s<long double>(_v); }
        static inline Q_km_per_s<long double> operator "" _km_per_s_ (unsigned long long int _v) {
            return Q_km_per_s<long double>(_v); }
    }



//
// Unit "hm_per_s"
//
    struct hm_per_s
    {
        using factor_t = std::ratio<100, 1>; // 100
        using dimensions_t = dimensions::Velocity;
        using offset_t = std::ratio<0, 1>;
        using relative_t = hm_per_s;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "hm_per_s";
        }
    };
    template<typename Value = long double>
    using Q_hm_per_s = units::Quantity<Value, hm_per_s>;
    namespace literals
    {
        static inline Q_hm_per_s<long double> operator "" _hm_per_s_ (long double _v) {
            return Q_hm_per_s<long double>(_v); }
        static inline Q_hm_per_s<long double> operator "" _hm_per_s_ (unsigned long long int _v) {
            return Q_hm_per_s<long double>(_v); }
    }



//
// Unit "dam_per_s"
//
    struct dam_per_s
    {
        using factor_t = std::ratio<10, 1>; // 10
        using dimensions_t = dimensions::Velocity;
        using offset_t = std::ratio<0, 1>;
        using relative_t = dam_per_s;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "dam_per_s";
        }
    };
    template<typename Value = long double>
    using Q_dam_per_s = units::Quantity<Value, dam_per_s>;
    namespace literals
    {
        static inline Q_dam_per_s<long double> operator "" _dam_per_s_ (long double _v) {
            return Q_dam_per_s<long double>(_v); }
        static inline Q_dam_per_s<long double> operator "" _dam_per_s_ (unsigned long long int _v) {
            return Q_dam_per_s<long double>(_v); }
    }



//
// Unit "m_per_s"
//
    struct m_per_s
    {
        using factor_t = std::ratio<1, 1>; // 1
        using dimensions_t = dimensions::Velocity;
        using offset_t = std::ratio<0, 1>;
        using relative_t = m_per_s;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "m_per_s";
        }
    };
    template<typename Value = long double>
    using Q_m_per_s = units::Quantity<Value, m_per_s>;
    namespace literals
    {
        static inline Q_m_per_s<long double> operator "" _m_per_s_ (long double _v) {
            return Q_m_per_s<long double>(_v); }
        static inline Q_m_per_s<long double> operator "" _m_per_s_ (unsigned long long int _v) {
            return Q_m_per_s<long double>(_v); }
    }



//
// Unit "dm_per_s"
//
    struct dm_per_s
    {
        using factor_t = std::ratio<1, 10>; // 0.1
        using dimensions_t = dimensions::Velocity;
        using offset_t = std::ratio<0, 1>;
        using relative_t = dm_per_s;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "dm_per_s";
        }
    };
    template<typename Value = long double>
    using Q_dm_per_s = units::Quantity<Value, dm_per_s>;
    namespace literals
    {
        static inline Q_dm_per_s<long double> operator "" _dm_per_s_ (long double _v) {
            return Q_dm_per_s<long double>(_v); }
        static inline Q_dm_per_s<long double> operator "" _dm_per_s_ (unsigned long long int _v) {
            return Q_dm_per_s<long double>(_v); }
    }



//
// Unit "cm_per_s"
//
    struct cm_per_s
    {
        using factor_t = std::ratio<1, 100>; // 0.01
        using dimensions_t = dimensions::Velocity;
        using offset_t = std::ratio<0, 1>;
        using relative_t = cm_per_s;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "cm_per_s";
        }
    };
    template<typename Value = long double>
    using Q_cm_per_s = units::Quantity<Value, cm_per_s>;
    namespace literals
    {
        static inline Q_cm_per_s<long double> operator "" _cm_per_s_ (long double _v) {
            return Q_cm_per_s<long double>(_v); }
        static inline Q_cm_per_s<long double> operator "" _cm_per_s_ (unsigned long long int _v) {
            return Q_cm_per_s<long double>(_v); }
    }



//
// Unit "mm_per_s"
//
    struct mm_per_s
    {
        using factor_t = std::ratio<1, 1000>; // 0.001
        using dimensions_t = dimensions::Velocity;
        using offset_t = std::ratio<0, 1>;
        using relative_t = mm_per_s;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "mm_per_s";
        }
    };
    template<typename Value = long double>
    using Q_mm_per_s = units::Quantity<Value, mm_per_s>;
    namespace literals
    {
        static inline Q_mm_per_s<long double> operator "" _mm_per_s_ (long double _v) {
            return Q_mm_per_s<long double>(_v); }
        static inline Q_mm_per_s<long double> operator "" _mm_per_s_ (unsigned long long int _v) {
            return Q_mm_per_s<long double>(_v); }
    }



//
// Unit "kmph"
//
    struct kmph
    {
        using factor_t = std::ratio<9, 25>; // 0.36
        using dimensions_t = dimensions::Velocity;
        using offset_t = std::ratio<0, 1>;
        using relative_t = kmph;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "kmph";
        }
    };
    template<typename Value = long double>
    using Q_kmph = units::Quantity<Value, kmph>;
    namespace literals
    {
        static inline Q_kmph<long double> operator "" _kmph_ (long double _v) {
            return Q_kmph<long double>(_v); }
        static inline Q_kmph<long double> operator "" _kmph_ (unsigned long long int _v) {
            return Q_kmph<long double>(_v); }
    }



//
// Unit "mph"
//
    struct mph
    {
        using factor_t = std::ratio<1321, 2955>; // 0.447039
        using dimensions_t = dimensions::Velocity;
        using offset_t = std::ratio<0, 1>;
        using relative_t = mph;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "mph";
        }
    };
    template<typename Value = long double>
    using Q_mph = units::Quantity<Value, mph>;
    namespace literals
    {
        static inline Q_mph<long double> operator "" _mph_ (long double _v) {
            return Q_mph<long double>(_v); }
        static inline Q_mph<long double> operator "" _mph_ (unsigned long long int _v) {
            return Q_mph<long double>(_v); }
    }



//
// Unit "kt"
//
    struct kt
    {
        using factor_t = std::ratio<643, 1250>; // 0.5144
        using dimensions_t = dimensions::Velocity;
        using offset_t = std::ratio<0, 1>;
        using relative_t = kt;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "kt";
        }
    };
    template<typename Value = long double>
    using Q_kt = units::Quantity<Value, kt>;
    namespace literals
    {
        static inline Q_kt<long double> operator "" _kt_ (long double _v) {
            return Q_kt<long double>(_v); }
        static inline Q_kt<long double> operator "" _kt_ (unsigned long long int _v) {
            return Q_kt<long double>(_v); }
    }



//
// Unit "mi_per_s"
//
    struct mi_per_s
    {
        using factor_t = std::ratio<80467, 50>; // 1609.34
        using dimensions_t = dimensions::Velocity;
        using offset_t = std::ratio<0, 1>;
        using relative_t = mi_per_s;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "mi_per_s";
        }
    };
    template<typename Value = long double>
    using Q_mi_per_s = units::Quantity<Value, mi_per_s>;
    namespace literals
    {
        static inline Q_mi_per_s<long double> operator "" _mi_per_s_ (long double _v) {
            return Q_mi_per_s<long double>(_v); }
        static inline Q_mi_per_s<long double> operator "" _mi_per_s_ (unsigned long long int _v) {
            return Q_mi_per_s<long double>(_v); }
    }



//
// Unit "yd_per_s"
//
    struct yd_per_s
    {
        using factor_t = std::ratio<4557, 5000>; // 0.9114
        using dimensions_t = dimensions::Velocity;
        using offset_t = std::ratio<0, 1>;
        using relative_t = yd_per_s;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "yd_per_s";
        }
    };
    template<typename Value = long double>
    using Q_yd_per_s = units::Quantity<Value, yd_per_s>;
    namespace literals
    {
        static inline Q_yd_per_s<long double> operator "" _yd_per_s_ (long double _v) {
            return Q_yd_per_s<long double>(_v); }
        static inline Q_yd_per_s<long double> operator "" _yd_per_s_ (unsigned long long int _v) {
            return Q_yd_per_s<long double>(_v); }
    }



//
// Unit "fps"
//
    struct fps
    {
        using factor_t = std::ratio<381, 1250>; // 0.3048
        using dimensions_t = dimensions::Velocity;
        using offset_t = std::ratio<0, 1>;
        using relative_t = fps;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "fps";
        }
    };
    template<typename Value = long double>
    using Q_fps = units::Quantity<Value, fps>;
    namespace literals
    {
        static inline Q_fps<long double> operator "" _fps_ (long double _v) {
            return Q_fps<long double>(_v); }
        static inline Q_fps<long double> operator "" _fps_ (unsigned long long int _v) {
            return Q_fps<long double>(_v); }
    }



//
// Unit "in_per_s"
//
    struct in_per_s
    {
        using factor_t = std::ratio<127, 5000>; // 0.0254
        using dimensions_t = dimensions::Velocity;
        using offset_t = std::ratio<0, 1>;
        using relative_t = in_per_s;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "in_per_s";
        }
    };
    template<typename Value = long double>
    using Q_in_per_s = units::Quantity<Value, in_per_s>;
    namespace literals
    {
        static inline Q_in_per_s<long double> operator "" _in_per_s_ (long double _v) {
            return Q_in_per_s<long double>(_v); }
        static inline Q_in_per_s<long double> operator "" _in_per_s_ (unsigned long long int _v) {
            return Q_in_per_s<long double>(_v); }
    }



//
// Unit "Em_per_s2"
//
    struct Em_per_s2
    {
        using factor_t = std::ratio<1000000000000000000, 1>; // 1e+18
        using dimensions_t = dimensions::Acceleration;
        using offset_t = std::ratio<0, 1>;
        using relative_t = Em_per_s2;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "Em_per_s2";
        }
    };
    template<typename Value = long double>
    using Q_Em_per_s2 = units::Quantity<Value, Em_per_s2>;
    namespace literals
    {
        static inline Q_Em_per_s2<long double> operator "" _Em_per_s2_ (long double _v) {
            return Q_Em_per_s2<long double>(_v); }
        static inline Q_Em_per_s2<long double> operator "" _Em_per_s2_ (unsigned long long int _v) {
            return Q_Em_per_s2<long double>(_v); }
    }



//
// Unit "Pm_per_s2"
//
    struct Pm_per_s2
    {
        using factor_t = std::ratio<1000000000000000, 1>; // 1e+15
        using dimensions_t = dimensions::Acceleration;
        using offset_t = std::ratio<0, 1>;
        using relative_t = Pm_per_s2;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "Pm_per_s2";
        }
    };
    template<typename Value = long double>
    using Q_Pm_per_s2 = units::Quantity<Value, Pm_per_s2>;
    namespace literals
    {
        static inline Q_Pm_per_s2<long double> operator "" _Pm_per_s2_ (long double _v) {
            return Q_Pm_per_s2<long double>(_v); }
        static inline Q_Pm_per_s2<long double> operator "" _Pm_per_s2_ (unsigned long long int _v) {
            return Q_Pm_per_s2<long double>(_v); }
    }



//
// Unit "Tm_per_s2"
//
    struct Tm_per_s2
    {
        using factor_t = std::ratio<1000000000000, 1>; // 1e+12
        using dimensions_t = dimensions::Acceleration;
        using offset_t = std::ratio<0, 1>;
        using relative_t = Tm_per_s2;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "Tm_per_s2";
        }
    };
    template<typename Value = long double>
    using Q_Tm_per_s2 = units::Quantity<Value, Tm_per_s2>;
    namespace literals
    {
        static inline Q_Tm_per_s2<long double> operator "" _Tm_per_s2_ (long double _v) {
            return Q_Tm_per_s2<long double>(_v); }
        static inline Q_Tm_per_s2<long double> operator "" _Tm_per_s2_ (unsigned long long int _v) {
            return Q_Tm_per_s2<long double>(_v); }
    }



//
// Unit "Gm_per_s2"
//
    struct Gm_per_s2
    {
        using factor_t = std::ratio<1000000000, 1>; // 1e+09
        using dimensions_t = dimensions::Acceleration;
        using offset_t = std::ratio<0, 1>;
        using relative_t = Gm_per_s2;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "Gm_per_s2";
        }
    };
    template<typename Value = long double>
    using Q_Gm_per_s2 = units::Quantity<Value, Gm_per_s2>;
    namespace literals
    {
        static inline Q_Gm_per_s2<long double> operator "" _Gm_per_s2_ (long double _v) {
            return Q_Gm_per_s2<long double>(_v); }
        static inline Q_Gm_per_s2<long double> operator "" _Gm_per_s2_ (unsigned long long int _v) {
            return Q_Gm_per_s2<long double>(_v); }
    }



//
// Unit "Mm_per_s2"
//
    struct Mm_per_s2
    {
        using factor_t = std::ratio<1000000, 1>; // 1e+06
        using dimensions_t = dimensions::Acceleration;
        using offset_t = std::ratio<0, 1>;
        using relative_t = Mm_per_s2;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "Mm_per_s2";
        }
    };
    template<typename Value = long double>
    using Q_Mm_per_s2 = units::Quantity<Value, Mm_per_s2>;
    namespace literals
    {
        static inline Q_Mm_per_s2<long double> operator "" _Mm_per_s2_ (long double _v) {
            return Q_Mm_per_s2<long double>(_v); }
        static inline Q_Mm_per_s2<long double> operator "" _Mm_per_s2_ (unsigned long long int _v) {
            return Q_Mm_per_s2<long double>(_v); }
    }



//
// Unit "km_per_s2"
//
    struct km_per_s2
    {
        using factor_t = std::ratio<1000, 1>; // 1000
        using dimensions_t = dimensions::Acceleration;
        using offset_t = std::ratio<0, 1>;
        using relative_t = km_per_s2;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "km_per_s2";
        }
    };
    template<typename Value = long double>
    using Q_km_per_s2 = units::Quantity<Value, km_per_s2>;
    namespace literals
    {
        static inline Q_km_per_s2<long double> operator "" _km_per_s2_ (long double _v) {
            return Q_km_per_s2<long double>(_v); }
        static inline Q_km_per_s2<long double> operator "" _km_per_s2_ (unsigned long long int _v) {
            return Q_km_per_s2<long double>(_v); }
    }



//
// Unit "hm_per_s2"
//
    struct hm_per_s2
    {
        using factor_t = std::ratio<100, 1>; // 100
        using dimensions_t = dimensions::Acceleration;
        using offset_t = std::ratio<0, 1>;
        using relative_t = hm_per_s2;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "hm_per_s2";
        }
    };
    template<typename Value = long double>
    using Q_hm_per_s2 = units::Quantity<Value, hm_per_s2>;
    namespace literals
    {
        static inline Q_hm_per_s2<long double> operator "" _hm_per_s2_ (long double _v) {
            return Q_hm_per_s2<long double>(_v); }
        static inline Q_hm_per_s2<long double> operator "" _hm_per_s2_ (unsigned long long int _v) {
            return Q_hm_per_s2<long double>(_v); }
    }



//
// Unit "dam_per_s2"
//
    struct dam_per_s2
    {
        using factor_t = std::ratio<10, 1>; // 10
        using dimensions_t = dimensions::Acceleration;
        using offset_t = std::ratio<0, 1>;
        using relative_t = dam_per_s2;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "dam_per_s2";
        }
    };
    template<typename Value = long double>
    using Q_dam_per_s2 = units::Quantity<Value, dam_per_s2>;
    namespace literals
    {
        static inline Q_dam_per_s2<long double> operator "" _dam_per_s2_ (long double _v) {
            return Q_dam_per_s2<long double>(_v); }
        static inline Q_dam_per_s2<long double> operator "" _dam_per_s2_ (unsigned long long int _v) {
            return Q_dam_per_s2<long double>(_v); }
    }



//
// Unit "m_per_s2"
//
    struct m_per_s2
    {
        using factor_t = std::ratio<1, 1>; // 1
        using dimensions_t = dimensions::Acceleration;
        using offset_t = std::ratio<0, 1>;
        using relative_t = m_per_s2;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "m_per_s2";
        }
    };
    template<typename Value = long double>
    using Q_m_per_s2 = units::Quantity<Value, m_per_s2>;
    namespace literals
    {
        static inline Q_m_per_s2<long double> operator "" _m_per_s2_ (long double _v) {
            return Q_m_per_s2<long double>(_v); }
        static inline Q_m_per_s2<long double> operator "" _m_per_s2_ (unsigned long long int _v) {
            return Q_m_per_s2<long double>(_v); }
    }



//
// Unit "dm_per_s2"
//
    struct dm_per_s2
    {
        using factor_t = std::ratio<1, 10>; // 0.1
        using dimensions_t = dimensions::Acceleration;
        using offset_t = std::ratio<0, 1>;
        using relative_t = dm_per_s2;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "dm_per_s2";
        }
    };
    template<typename Value = long double>
    using Q_dm_per_s2 = units::Quantity<Value, dm_per_s2>;
    namespace literals
    {
        static inline Q_dm_per_s2<long double> operator "" _dm_per_s2_ (long double _v) {
            return Q_dm_per_s2<long double>(_v); }
        static inline Q_dm_per_s2<long double> operator "" _dm_per_s2_ (unsigned long long int _v) {
            return Q_dm_per_s2<long double>(_v); }
    }



//
// Unit "cm_per_s2"
//
    struct cm_per_s2
    {
        using factor_t = std::ratio<1, 100>; // 0.01
        using dimensions_t = dimensions::Acceleration;
        using offset_t = std::ratio<0, 1>;
        using relative_t = cm_per_s2;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "cm_per_s2";
        }
    };
    template<typename Value = long double>
    using Q_cm_per_s2 = units::Quantity<Value, cm_per_s2>;
    namespace literals
    {
        static inline Q_cm_per_s2<long double> operator "" _cm_per_s2_ (long double _v) {
            return Q_cm_per_s2<long double>(_v); }
        static inline Q_cm_per_s2<long double> operator "" _cm_per_s2_ (unsigned long long int _v) {
            return Q_cm_per_s2<long double>(_v); }
    }



//
// Unit "mm_per_s2"
//
    struct mm_per_s2
    {
        using factor_t = std::ratio<1, 1000>; // 0.001
        using dimensions_t = dimensions::Acceleration;
        using offset_t = std::ratio<0, 1>;
        using relative_t = mm_per_s2;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "mm_per_s2";
        }
    };
    template<typename Value = long double>
    using Q_mm_per_s2 = units::Quantity<Value, mm_per_s2>;
    namespace literals
    {
        static inline Q_mm_per_s2<long double> operator "" _mm_per_s2_ (long double _v) {
            return Q_mm_per_s2<long double>(_v); }
        static inline Q_mm_per_s2<long double> operator "" _mm_per_s2_ (unsigned long long int _v) {
            return Q_mm_per_s2<long double>(_v); }
    }



//
// Unit "mi_per_s2"
//
    struct mi_per_s2
    {
        using factor_t = std::ratio<80467, 50>; // 1609.34
        using dimensions_t = dimensions::Acceleration;
        using offset_t = std::ratio<0, 1>;
        using relative_t = mi_per_s2;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "mi_per_s2";
        }
    };
    template<typename Value = long double>
    using Q_mi_per_s2 = units::Quantity<Value, mi_per_s2>;
    namespace literals
    {
        static inline Q_mi_per_s2<long double> operator "" _mi_per_s2_ (long double _v) {
            return Q_mi_per_s2<long double>(_v); }
        static inline Q_mi_per_s2<long double> operator "" _mi_per_s2_ (unsigned long long int _v) {
            return Q_mi_per_s2<long double>(_v); }
    }



//
// Unit "yd_per_s2"
//
    struct yd_per_s2
    {
        using factor_t = std::ratio<4557, 5000>; // 0.9114
        using dimensions_t = dimensions::Acceleration;
        using offset_t = std::ratio<0, 1>;
        using relative_t = yd_per_s2;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "yd_per_s2";
        }
    };
    template<typename Value = long double>
    using Q_yd_per_s2 = units::Quantity<Value, yd_per_s2>;
    namespace literals
    {
        static inline Q_yd_per_s2<long double> operator "" _yd_per_s2_ (long double _v) {
            return Q_yd_per_s2<long double>(_v); }
        static inline Q_yd_per_s2<long double> operator "" _yd_per_s2_ (unsigned long long int _v) {
            return Q_yd_per_s2<long double>(_v); }
    }



//
// Unit "ft_per_s2"
//
    struct ft_per_s2
    {
        using factor_t = std::ratio<381, 1250>; // 0.3048
        using dimensions_t = dimensions::Acceleration;
        using offset_t = std::ratio<0, 1>;
        using relative_t = ft_per_s2;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "ft_per_s2";
        }
    };
    template<typename Value = long double>
    using Q_ft_per_s2 = units::Quantity<Value, ft_per_s2>;
    namespace literals
    {
        static inline Q_ft_per_s2<long double> operator "" _ft_per_s2_ (long double _v) {
            return Q_ft_per_s2<long double>(_v); }
        static inline Q_ft_per_s2<long double> operator "" _ft_per_s2_ (unsigned long long int _v) {
            return Q_ft_per_s2<long double>(_v); }
    }



//
// Unit "in_per_s2"
//
    struct in_per_s2
    {
        using factor_t = std::ratio<127, 5000>; // 0.0254
        using dimensions_t = dimensions::Acceleration;
        using offset_t = std::ratio<0, 1>;
        using relative_t = in_per_s2;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "in_per_s2";
        }
    };
    template<typename Value = long double>
    using Q_in_per_s2 = units::Quantity<Value, in_per_s2>;
    namespace literals
    {
        static inline Q_in_per_s2<long double> operator "" _in_per_s2_ (long double _v) {
            return Q_in_per_s2<long double>(_v); }
        static inline Q_in_per_s2<long double> operator "" _in_per_s2_ (unsigned long long int _v) {
            return Q_in_per_s2<long double>(_v); }
    }



//
// Unit "Pgees"
//
    struct Pgees
    {
        using factor_t = std::ratio<9806650000000000, 1>; // 9.80665e+15
        using dimensions_t = dimensions::Acceleration;
        using offset_t = std::ratio<0, 1>;
        using relative_t = Pgees;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "Pgees";
        }
    };
    template<typename Value = long double>
    using Q_Pgees = units::Quantity<Value, Pgees>;
    namespace literals
    {
        static inline Q_Pgees<long double> operator "" _Pgees_ (long double _v) {
            return Q_Pgees<long double>(_v); }
        static inline Q_Pgees<long double> operator "" _Pgees_ (unsigned long long int _v) {
            return Q_Pgees<long double>(_v); }
    }



//
// Unit "Tgees"
//
    struct Tgees
    {
        using factor_t = std::ratio<9806650000000, 1>; // 9.80665e+12
        using dimensions_t = dimensions::Acceleration;
        using offset_t = std::ratio<0, 1>;
        using relative_t = Tgees;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "Tgees";
        }
    };
    template<typename Value = long double>
    using Q_Tgees = units::Quantity<Value, Tgees>;
    namespace literals
    {
        static inline Q_Tgees<long double> operator "" _Tgees_ (long double _v) {
            return Q_Tgees<long double>(_v); }
        static inline Q_Tgees<long double> operator "" _Tgees_ (unsigned long long int _v) {
            return Q_Tgees<long double>(_v); }
    }



//
// Unit "Ggees"
//
    struct Ggees
    {
        using factor_t = std::ratio<9806650000, 1>; // 9.80665e+09
        using dimensions_t = dimensions::Acceleration;
        using offset_t = std::ratio<0, 1>;
        using relative_t = Ggees;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "Ggees";
        }
    };
    template<typename Value = long double>
    using Q_Ggees = units::Quantity<Value, Ggees>;
    namespace literals
    {
        static inline Q_Ggees<long double> operator "" _Ggees_ (long double _v) {
            return Q_Ggees<long double>(_v); }
        static inline Q_Ggees<long double> operator "" _Ggees_ (unsigned long long int _v) {
            return Q_Ggees<long double>(_v); }
    }



//
// Unit "Mgees"
//
    struct Mgees
    {
        using factor_t = std::ratio<9806650, 1>; // 9.80665e+06
        using dimensions_t = dimensions::Acceleration;
        using offset_t = std::ratio<0, 1>;
        using relative_t = Mgees;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "Mgees";
        }
    };
    template<typename Value = long double>
    using Q_Mgees = units::Quantity<Value, Mgees>;
    namespace literals
    {
        static inline Q_Mgees<long double> operator "" _Mgees_ (long double _v) {
            return Q_Mgees<long double>(_v); }
        static inline Q_Mgees<long double> operator "" _Mgees_ (unsigned long long int _v) {
            return Q_Mgees<long double>(_v); }
    }



//
// Unit "kgees"
//
    struct kgees
    {
        using factor_t = std::ratio<196133, 20>; // 9806.65
        using dimensions_t = dimensions::Acceleration;
        using offset_t = std::ratio<0, 1>;
        using relative_t = kgees;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "kgees";
        }
    };
    template<typename Value = long double>
    using Q_kgees = units::Quantity<Value, kgees>;
    namespace literals
    {
        static inline Q_kgees<long double> operator "" _kgees_ (long double _v) {
            return Q_kgees<long double>(_v); }
        static inline Q_kgees<long double> operator "" _kgees_ (unsigned long long int _v) {
            return Q_kgees<long double>(_v); }
    }



//
// Unit "hgees"
//
    struct hgees
    {
        using factor_t = std::ratio<196133, 200>; // 980.665
        using dimensions_t = dimensions::Acceleration;
        using offset_t = std::ratio<0, 1>;
        using relative_t = hgees;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "hgees";
        }
    };
    template<typename Value = long double>
    using Q_hgees = units::Quantity<Value, hgees>;
    namespace literals
    {
        static inline Q_hgees<long double> operator "" _hgees_ (long double _v) {
            return Q_hgees<long double>(_v); }
        static inline Q_hgees<long double> operator "" _hgees_ (unsigned long long int _v) {
            return Q_hgees<long double>(_v); }
    }



//
// Unit "dagees"
//
    struct dagees
    {
        using factor_t = std::ratio<78159, 797>; // 98.0665
        using dimensions_t = dimensions::Acceleration;
        using offset_t = std::ratio<0, 1>;
        using relative_t = dagees;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "dagees";
        }
    };
    template<typename Value = long double>
    using Q_dagees = units::Quantity<Value, dagees>;
    namespace literals
    {
        static inline Q_dagees<long double> operator "" _dagees_ (long double _v) {
            return Q_dagees<long double>(_v); }
        static inline Q_dagees<long double> operator "" _dagees_ (unsigned long long int _v) {
            return Q_dagees<long double>(_v); }
    }



//
// Unit "gees"
//
    struct gees
    {
        using factor_t = std::ratio<7963, 812>; // 9.80665
        using dimensions_t = dimensions::Acceleration;
        using offset_t = std::ratio<0, 1>;
        using relative_t = gees;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "gees";
        }
    };
    template<typename Value = long double>
    using Q_gees = units::Quantity<Value, gees>;
    namespace literals
    {
        static inline Q_gees<long double> operator "" _gees_ (long double _v) {
            return Q_gees<long double>(_v); }
        static inline Q_gees<long double> operator "" _gees_ (unsigned long long int _v) {
            return Q_gees<long double>(_v); }
    }



//
// Unit "dgees"
//
    struct dgees
    {
        using factor_t = std::ratio<913, 931>; // 0.980665
        using dimensions_t = dimensions::Acceleration;
        using offset_t = std::ratio<0, 1>;
        using relative_t = dgees;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "dgees";
        }
    };
    template<typename Value = long double>
    using Q_dgees = units::Quantity<Value, dgees>;
    namespace literals
    {
        static inline Q_dgees<long double> operator "" _dgees_ (long double _v) {
            return Q_dgees<long double>(_v); }
        static inline Q_dgees<long double> operator "" _dgees_ (unsigned long long int _v) {
            return Q_dgees<long double>(_v); }
    }



//
// Unit "cgees"
//
    struct cgees
    {
        using factor_t = std::ratio<71, 724>; // 0.0980665
        using dimensions_t = dimensions::Acceleration;
        using offset_t = std::ratio<0, 1>;
        using relative_t = cgees;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "cgees";
        }
    };
    template<typename Value = long double>
    using Q_cgees = units::Quantity<Value, cgees>;
    namespace literals
    {
        static inline Q_cgees<long double> operator "" _cgees_ (long double _v) {
            return Q_cgees<long double>(_v); }
        static inline Q_cgees<long double> operator "" _cgees_ (unsigned long long int _v) {
            return Q_cgees<long double>(_v); }
    }



//
// Unit "mgees"
//
    struct mgees
    {
        using factor_t = std::ratio<35, 3569>; // 0.00980665
        using dimensions_t = dimensions::Acceleration;
        using offset_t = std::ratio<0, 1>;
        using relative_t = mgees;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "mgees";
        }
    };
    template<typename Value = long double>
    using Q_mgees = units::Quantity<Value, mgees>;
    namespace literals
    {
        static inline Q_mgees<long double> operator "" _mgees_ (long double _v) {
            return Q_mgees<long double>(_v); }
        static inline Q_mgees<long double> operator "" _mgees_ (unsigned long long int _v) {
            return Q_mgees<long double>(_v); }
    }



//
// Unit "ugees"
//
    struct ugees
    {
        using factor_t = std::ratio<1, 100000>; // 9.80665e-06
        using dimensions_t = dimensions::Acceleration;
        using offset_t = std::ratio<0, 1>;
        using relative_t = ugees;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "ugees";
        }
    };
    template<typename Value = long double>
    using Q_ugees = units::Quantity<Value, ugees>;
    namespace literals
    {
        static inline Q_ugees<long double> operator "" _ugees_ (long double _v) {
            return Q_ugees<long double>(_v); }
        static inline Q_ugees<long double> operator "" _ugees_ (unsigned long long int _v) {
            return Q_ugees<long double>(_v); }
    }



//
// Unit "Em_per_s3"
//
    struct Em_per_s3
    {
        using factor_t = std::ratio<1000000000000000000, 1>; // 1e+18
        using dimensions_t = dimensions::Jerk;
        using offset_t = std::ratio<0, 1>;
        using relative_t = Em_per_s3;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "Em_per_s3";
        }
    };
    template<typename Value = long double>
    using Q_Em_per_s3 = units::Quantity<Value, Em_per_s3>;
    namespace literals
    {
        static inline Q_Em_per_s3<long double> operator "" _Em_per_s3_ (long double _v) {
            return Q_Em_per_s3<long double>(_v); }
        static inline Q_Em_per_s3<long double> operator "" _Em_per_s3_ (unsigned long long int _v) {
            return Q_Em_per_s3<long double>(_v); }
    }



//
// Unit "Pm_per_s3"
//
    struct Pm_per_s3
    {
        using factor_t = std::ratio<1000000000000000, 1>; // 1e+15
        using dimensions_t = dimensions::Jerk;
        using offset_t = std::ratio<0, 1>;
        using relative_t = Pm_per_s3;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "Pm_per_s3";
        }
    };
    template<typename Value = long double>
    using Q_Pm_per_s3 = units::Quantity<Value, Pm_per_s3>;
    namespace literals
    {
        static inline Q_Pm_per_s3<long double> operator "" _Pm_per_s3_ (long double _v) {
            return Q_Pm_per_s3<long double>(_v); }
        static inline Q_Pm_per_s3<long double> operator "" _Pm_per_s3_ (unsigned long long int _v) {
            return Q_Pm_per_s3<long double>(_v); }
    }



//
// Unit "Tm_per_s3"
//
    struct Tm_per_s3
    {
        using factor_t = std::ratio<1000000000000, 1>; // 1e+12
        using dimensions_t = dimensions::Jerk;
        using offset_t = std::ratio<0, 1>;
        using relative_t = Tm_per_s3;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "Tm_per_s3";
        }
    };
    template<typename Value = long double>
    using Q_Tm_per_s3 = units::Quantity<Value, Tm_per_s3>;
    namespace literals
    {
        static inline Q_Tm_per_s3<long double> operator "" _Tm_per_s3_ (long double _v) {
            return Q_Tm_per_s3<long double>(_v); }
        static inline Q_Tm_per_s3<long double> operator "" _Tm_per_s3_ (unsigned long long int _v) {
            return Q_Tm_per_s3<long double>(_v); }
    }



//
// Unit "Gm_per_s3"
//
    struct Gm_per_s3
    {
        using factor_t = std::ratio<1000000000, 1>; // 1e+09
        using dimensions_t = dimensions::Jerk;
        using offset_t = std::ratio<0, 1>;
        using relative_t = Gm_per_s3;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "Gm_per_s3";
        }
    };
    template<typename Value = long double>
    using Q_Gm_per_s3 = units::Quantity<Value, Gm_per_s3>;
    namespace literals
    {
        static inline Q_Gm_per_s3<long double> operator "" _Gm_per_s3_ (long double _v) {
            return Q_Gm_per_s3<long double>(_v); }
        static inline Q_Gm_per_s3<long double> operator "" _Gm_per_s3_ (unsigned long long int _v) {
            return Q_Gm_per_s3<long double>(_v); }
    }



//
// Unit "Mm_per_s3"
//
    struct Mm_per_s3
    {
        using factor_t = std::ratio<1000000, 1>; // 1e+06
        using dimensions_t = dimensions::Jerk;
        using offset_t = std::ratio<0, 1>;
        using relative_t = Mm_per_s3;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "Mm_per_s3";
        }
    };
    template<typename Value = long double>
    using Q_Mm_per_s3 = units::Quantity<Value, Mm_per_s3>;
    namespace literals
    {
        static inline Q_Mm_per_s3<long double> operator "" _Mm_per_s3_ (long double _v) {
            return Q_Mm_per_s3<long double>(_v); }
        static inline Q_Mm_per_s3<long double> operator "" _Mm_per_s3_ (unsigned long long int _v) {
            return Q_Mm_per_s3<long double>(_v); }
    }



//
// Unit "km_per_s3"
//
    struct km_per_s3
    {
        using factor_t = std::ratio<1000, 1>; // 1000
        using dimensions_t = dimensions::Jerk;
        using offset_t = std::ratio<0, 1>;
        using relative_t = km_per_s3;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "km_per_s3";
        }
    };
    template<typename Value = long double>
    using Q_km_per_s3 = units::Quantity<Value, km_per_s3>;
    namespace literals
    {
        static inline Q_km_per_s3<long double> operator "" _km_per_s3_ (long double _v) {
            return Q_km_per_s3<long double>(_v); }
        static inline Q_km_per_s3<long double> operator "" _km_per_s3_ (unsigned long long int _v) {
            return Q_km_per_s3<long double>(_v); }
    }



//
// Unit "hm_per_s3"
//
    struct hm_per_s3
    {
        using factor_t = std::ratio<100, 1>; // 100
        using dimensions_t = dimensions::Jerk;
        using offset_t = std::ratio<0, 1>;
        using relative_t = hm_per_s3;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "hm_per_s3";
        }
    };
    template<typename Value = long double>
    using Q_hm_per_s3 = units::Quantity<Value, hm_per_s3>;
    namespace literals
    {
        static inline Q_hm_per_s3<long double> operator "" _hm_per_s3_ (long double _v) {
            return Q_hm_per_s3<long double>(_v); }
        static inline Q_hm_per_s3<long double> operator "" _hm_per_s3_ (unsigned long long int _v) {
            return Q_hm_per_s3<long double>(_v); }
    }



//
// Unit "dam_per_s3"
//
    struct dam_per_s3
    {
        using factor_t = std::ratio<10, 1>; // 10
        using dimensions_t = dimensions::Jerk;
        using offset_t = std::ratio<0, 1>;
        using relative_t = dam_per_s3;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "dam_per_s3";
        }
    };
    template<typename Value = long double>
    using Q_dam_per_s3 = units::Quantity<Value, dam_per_s3>;
    namespace literals
    {
        static inline Q_dam_per_s3<long double> operator "" _dam_per_s3_ (long double _v) {
            return Q_dam_per_s3<long double>(_v); }
        static inline Q_dam_per_s3<long double> operator "" _dam_per_s3_ (unsigned long long int _v) {
            return Q_dam_per_s3<long double>(_v); }
    }



//
// Unit "m_per_s3"
//
    struct m_per_s3
    {
        using factor_t = std::ratio<1, 1>; // 1
        using dimensions_t = dimensions::Jerk;
        using offset_t = std::ratio<0, 1>;
        using relative_t = m_per_s3;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "m_per_s3";
        }
    };
    template<typename Value = long double>
    using Q_m_per_s3 = units::Quantity<Value, m_per_s3>;
    namespace literals
    {
        static inline Q_m_per_s3<long double> operator "" _m_per_s3_ (long double _v) {
            return Q_m_per_s3<long double>(_v); }
        static inline Q_m_per_s3<long double> operator "" _m_per_s3_ (unsigned long long int _v) {
            return Q_m_per_s3<long double>(_v); }
    }



//
// Unit "dm_per_s3"
//
    struct dm_per_s3
    {
        using factor_t = std::ratio<1, 10>; // 0.1
        using dimensions_t = dimensions::Jerk;
        using offset_t = std::ratio<0, 1>;
        using relative_t = dm_per_s3;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "dm_per_s3";
        }
    };
    template<typename Value = long double>
    using Q_dm_per_s3 = units::Quantity<Value, dm_per_s3>;
    namespace literals
    {
        static inline Q_dm_per_s3<long double> operator "" _dm_per_s3_ (long double _v) {
            return Q_dm_per_s3<long double>(_v); }
        static inline Q_dm_per_s3<long double> operator "" _dm_per_s3_ (unsigned long long int _v) {
            return Q_dm_per_s3<long double>(_v); }
    }



//
// Unit "cm_per_s3"
//
    struct cm_per_s3
    {
        using factor_t = std::ratio<1, 100>; // 0.01
        using dimensions_t = dimensions::Jerk;
        using offset_t = std::ratio<0, 1>;
        using relative_t = cm_per_s3;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "cm_per_s3";
        }
    };
    template<typename Value = long double>
    using Q_cm_per_s3 = units::Quantity<Value, cm_per_s3>;
    namespace literals
    {
        static inline Q_cm_per_s3<long double> operator "" _cm_per_s3_ (long double _v) {
            return Q_cm_per_s3<long double>(_v); }
        static inline Q_cm_per_s3<long double> operator "" _cm_per_s3_ (unsigned long long int _v) {
            return Q_cm_per_s3<long double>(_v); }
    }



//
// Unit "mm_per_s3"
//
    struct mm_per_s3
    {
        using factor_t = std::ratio<1, 1000>; // 0.001
        using dimensions_t = dimensions::Jerk;
        using offset_t = std::ratio<0, 1>;
        using relative_t = mm_per_s3;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "mm_per_s3";
        }
    };
    template<typename Value = long double>
    using Q_mm_per_s3 = units::Quantity<Value, mm_per_s3>;
    namespace literals
    {
        static inline Q_mm_per_s3<long double> operator "" _mm_per_s3_ (long double _v) {
            return Q_mm_per_s3<long double>(_v); }
        static inline Q_mm_per_s3<long double> operator "" _mm_per_s3_ (unsigned long long int _v) {
            return Q_mm_per_s3<long double>(_v); }
    }



//
// Unit "mi_per_s3"
//
    struct mi_per_s3
    {
        using factor_t = std::ratio<80467, 50>; // 1609.34
        using dimensions_t = dimensions::Jerk;
        using offset_t = std::ratio<0, 1>;
        using relative_t = mi_per_s3;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "mi_per_s3";
        }
    };
    template<typename Value = long double>
    using Q_mi_per_s3 = units::Quantity<Value, mi_per_s3>;
    namespace literals
    {
        static inline Q_mi_per_s3<long double> operator "" _mi_per_s3_ (long double _v) {
            return Q_mi_per_s3<long double>(_v); }
        static inline Q_mi_per_s3<long double> operator "" _mi_per_s3_ (unsigned long long int _v) {
            return Q_mi_per_s3<long double>(_v); }
    }



//
// Unit "yd_per_s3"
//
    struct yd_per_s3
    {
        using factor_t = std::ratio<4557, 5000>; // 0.9114
        using dimensions_t = dimensions::Jerk;
        using offset_t = std::ratio<0, 1>;
        using relative_t = yd_per_s3;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "yd_per_s3";
        }
    };
    template<typename Value = long double>
    using Q_yd_per_s3 = units::Quantity<Value, yd_per_s3>;
    namespace literals
    {
        static inline Q_yd_per_s3<long double> operator "" _yd_per_s3_ (long double _v) {
            return Q_yd_per_s3<long double>(_v); }
        static inline Q_yd_per_s3<long double> operator "" _yd_per_s3_ (unsigned long long int _v) {
            return Q_yd_per_s3<long double>(_v); }
    }



//
// Unit "ft_per_s3"
//
    struct ft_per_s3
    {
        using factor_t = std::ratio<381, 1250>; // 0.3048
        using dimensions_t = dimensions::Jerk;
        using offset_t = std::ratio<0, 1>;
        using relative_t = ft_per_s3;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "ft_per_s3";
        }
    };
    template<typename Value = long double>
    using Q_ft_per_s3 = units::Quantity<Value, ft_per_s3>;
    namespace literals
    {
        static inline Q_ft_per_s3<long double> operator "" _ft_per_s3_ (long double _v) {
            return Q_ft_per_s3<long double>(_v); }
        static inline Q_ft_per_s3<long double> operator "" _ft_per_s3_ (unsigned long long int _v) {
            return Q_ft_per_s3<long double>(_v); }
    }



//
// Unit "in_per_s3"
//
    struct in_per_s3
    {
        using factor_t = std::ratio<127, 5000>; // 0.0254
        using dimensions_t = dimensions::Jerk;
        using offset_t = std::ratio<0, 1>;
        using relative_t = in_per_s3;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "in_per_s3";
        }
    };
    template<typename Value = long double>
    using Q_in_per_s3 = units::Quantity<Value, in_per_s3>;
    namespace literals
    {
        static inline Q_in_per_s3<long double> operator "" _in_per_s3_ (long double _v) {
            return Q_in_per_s3<long double>(_v); }
        static inline Q_in_per_s3<long double> operator "" _in_per_s3_ (unsigned long long int _v) {
            return Q_in_per_s3<long double>(_v); }
    }



//
// Unit "Pgees_per_s"
//
    struct Pgees_per_s
    {
        using factor_t = std::ratio<9806650000000000, 1>; // 9.80665e+15
        using dimensions_t = dimensions::Jerk;
        using offset_t = std::ratio<0, 1>;
        using relative_t = Pgees_per_s;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "Pgees_per_s";
        }
    };
    template<typename Value = long double>
    using Q_Pgees_per_s = units::Quantity<Value, Pgees_per_s>;
    namespace literals
    {
        static inline Q_Pgees_per_s<long double> operator "" _Pgees_per_s_ (long double _v) {
            return Q_Pgees_per_s<long double>(_v); }
        static inline Q_Pgees_per_s<long double> operator "" _Pgees_per_s_ (unsigned long long int _v) {
            return Q_Pgees_per_s<long double>(_v); }
    }



//
// Unit "Tgees_per_s"
//
    struct Tgees_per_s
    {
        using factor_t = std::ratio<9806650000000, 1>; // 9.80665e+12
        using dimensions_t = dimensions::Jerk;
        using offset_t = std::ratio<0, 1>;
        using relative_t = Tgees_per_s;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "Tgees_per_s";
        }
    };
    template<typename Value = long double>
    using Q_Tgees_per_s = units::Quantity<Value, Tgees_per_s>;
    namespace literals
    {
        static inline Q_Tgees_per_s<long double> operator "" _Tgees_per_s_ (long double _v) {
            return Q_Tgees_per_s<long double>(_v); }
        static inline Q_Tgees_per_s<long double> operator "" _Tgees_per_s_ (unsigned long long int _v) {
            return Q_Tgees_per_s<long double>(_v); }
    }



//
// Unit "Ggees_per_s"
//
    struct Ggees_per_s
    {
        using factor_t = std::ratio<9806650000, 1>; // 9.80665e+09
        using dimensions_t = dimensions::Jerk;
        using offset_t = std::ratio<0, 1>;
        using relative_t = Ggees_per_s;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "Ggees_per_s";
        }
    };
    template<typename Value = long double>
    using Q_Ggees_per_s = units::Quantity<Value, Ggees_per_s>;
    namespace literals
    {
        static inline Q_Ggees_per_s<long double> operator "" _Ggees_per_s_ (long double _v) {
            return Q_Ggees_per_s<long double>(_v); }
        static inline Q_Ggees_per_s<long double> operator "" _Ggees_per_s_ (unsigned long long int _v) {
            return Q_Ggees_per_s<long double>(_v); }
    }



//
// Unit "Mgees_per_s"
//
    struct Mgees_per_s
    {
        using factor_t = std::ratio<9806650, 1>; // 9.80665e+06
        using dimensions_t = dimensions::Jerk;
        using offset_t = std::ratio<0, 1>;
        using relative_t = Mgees_per_s;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "Mgees_per_s";
        }
    };
    template<typename Value = long double>
    using Q_Mgees_per_s = units::Quantity<Value, Mgees_per_s>;
    namespace literals
    {
        static inline Q_Mgees_per_s<long double> operator "" _Mgees_per_s_ (long double _v) {
            return Q_Mgees_per_s<long double>(_v); }
        static inline Q_Mgees_per_s<long double> operator "" _Mgees_per_s_ (unsigned long long int _v) {
            return Q_Mgees_per_s<long double>(_v); }
    }



//
// Unit "kgees_per_s"
//
    struct kgees_per_s
    {
        using factor_t = std::ratio<196133, 20>; // 9806.65
        using dimensions_t = dimensions::Jerk;
        using offset_t = std::ratio<0, 1>;
        using relative_t = kgees_per_s;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "kgees_per_s";
        }
    };
    template<typename Value = long double>
    using Q_kgees_per_s = units::Quantity<Value, kgees_per_s>;
    namespace literals
    {
        static inline Q_kgees_per_s<long double> operator "" _kgees_per_s_ (long double _v) {
            return Q_kgees_per_s<long double>(_v); }
        static inline Q_kgees_per_s<long double> operator "" _kgees_per_s_ (unsigned long long int _v) {
            return Q_kgees_per_s<long double>(_v); }
    }



//
// Unit "hgees_per_s"
//
    struct hgees_per_s
    {
        using factor_t = std::ratio<196133, 200>; // 980.665
        using dimensions_t = dimensions::Jerk;
        using offset_t = std::ratio<0, 1>;
        using relative_t = hgees_per_s;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "hgees_per_s";
        }
    };
    template<typename Value = long double>
    using Q_hgees_per_s = units::Quantity<Value, hgees_per_s>;
    namespace literals
    {
        static inline Q_hgees_per_s<long double> operator "" _hgees_per_s_ (long double _v) {
            return Q_hgees_per_s<long double>(_v); }
        static inline Q_hgees_per_s<long double> operator "" _hgees_per_s_ (unsigned long long int _v) {
            return Q_hgees_per_s<long double>(_v); }
    }



//
// Unit "dagees_per_s"
//
    struct dagees_per_s
    {
        using factor_t = std::ratio<78159, 797>; // 98.0665
        using dimensions_t = dimensions::Jerk;
        using offset_t = std::ratio<0, 1>;
        using relative_t = dagees_per_s;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "dagees_per_s";
        }
    };
    template<typename Value = long double>
    using Q_dagees_per_s = units::Quantity<Value, dagees_per_s>;
    namespace literals
    {
        static inline Q_dagees_per_s<long double> operator "" _dagees_per_s_ (long double _v) {
            return Q_dagees_per_s<long double>(_v); }
        static inline Q_dagees_per_s<long double> operator "" _dagees_per_s_ (unsigned long long int _v) {
            return Q_dagees_per_s<long double>(_v); }
    }



//
// Unit "gees_per_s"
//
    struct gees_per_s
    {
        using factor_t = std::ratio<7963, 812>; // 9.80665
        using dimensions_t = dimensions::Jerk;
        using offset_t = std::ratio<0, 1>;
        using relative_t = gees_per_s;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "gees_per_s";
        }
    };
    template<typename Value = long double>
    using Q_gees_per_s = units::Quantity<Value, gees_per_s>;
    namespace literals
    {
        static inline Q_gees_per_s<long double> operator "" _gees_per_s_ (long double _v) {
            return Q_gees_per_s<long double>(_v); }
        static inline Q_gees_per_s<long double> operator "" _gees_per_s_ (unsigned long long int _v) {
            return Q_gees_per_s<long double>(_v); }
    }



//
// Unit "dgees_per_s"
//
    struct dgees_per_s
    {
        using factor_t = std::ratio<913, 931>; // 0.980665
        using dimensions_t = dimensions::Jerk;
        using offset_t = std::ratio<0, 1>;
        using relative_t = dgees_per_s;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "dgees_per_s";
        }
    };
    template<typename Value = long double>
    using Q_dgees_per_s = units::Quantity<Value, dgees_per_s>;
    namespace literals
    {
        static inline Q_dgees_per_s<long double> operator "" _dgees_per_s_ (long double _v) {
            return Q_dgees_per_s<long double>(_v); }
        static inline Q_dgees_per_s<long double> operator "" _dgees_per_s_ (unsigned long long int _v) {
            return Q_dgees_per_s<long double>(_v); }
    }



//
// Unit "cgees_per_s"
//
    struct cgees_per_s
    {
        using factor_t = std::ratio<71, 724>; // 0.0980665
        using dimensions_t = dimensions::Jerk;
        using offset_t = std::ratio<0, 1>;
        using relative_t = cgees_per_s;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "cgees_per_s";
        }
    };
    template<typename Value = long double>
    using Q_cgees_per_s = units::Quantity<Value, cgees_per_s>;
    namespace literals
    {
        static inline Q_cgees_per_s<long double> operator "" _cgees_per_s_ (long double _v) {
            return Q_cgees_per_s<long double>(_v); }
        static inline Q_cgees_per_s<long double> operator "" _cgees_per_s_ (unsigned long long int _v) {
            return Q_cgees_per_s<long double>(_v); }
    }



//
// Unit "mgees_per_s"
//
    struct mgees_per_s
    {
        using factor_t = std::ratio<35, 3569>; // 0.00980665
        using dimensions_t = dimensions::Jerk;
        using offset_t = std::ratio<0, 1>;
        using relative_t = mgees_per_s;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "mgees_per_s";
        }
    };
    template<typename Value = long double>
    using Q_mgees_per_s = units::Quantity<Value, mgees_per_s>;
    namespace literals
    {
        static inline Q_mgees_per_s<long double> operator "" _mgees_per_s_ (long double _v) {
            return Q_mgees_per_s<long double>(_v); }
        static inline Q_mgees_per_s<long double> operator "" _mgees_per_s_ (unsigned long long int _v) {
            return Q_mgees_per_s<long double>(_v); }
    }



//
// Unit "ugees_per_s"
//
    struct ugees_per_s
    {
        using factor_t = std::ratio<1, 100000>; // 9.80665e-06
        using dimensions_t = dimensions::Jerk;
        using offset_t = std::ratio<0, 1>;
        using relative_t = ugees_per_s;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "ugees_per_s";
        }
    };
    template<typename Value = long double>
    using Q_ugees_per_s = units::Quantity<Value, ugees_per_s>;
    namespace literals
    {
        static inline Q_ugees_per_s<long double> operator "" _ugees_per_s_ (long double _v) {
            return Q_ugees_per_s<long double>(_v); }
        static inline Q_ugees_per_s<long double> operator "" _ugees_per_s_ (unsigned long long int _v) {
            return Q_ugees_per_s<long double>(_v); }
    }



//
// Unit "rad"
//
    struct rad
    {
        using factor_t = std::ratio<1, 1>; // 1
        using dimensions_t = dimensions::PlaneAngle;
        using offset_t = std::ratio<0, 1>;
        using relative_t = rad;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "rad";
        }
    };
    template<typename Value = long double>
    using Q_rad = units::Quantity<Value, rad>;
    namespace literals
    {
        static inline Q_rad<long double> operator "" _rad_ (long double _v) {
            return Q_rad<long double>(_v); }
        static inline Q_rad<long double> operator "" _rad_ (unsigned long long int _v) {
            return Q_rad<long double>(_v); }
    }



//
// Unit "rev"
//
    struct rev
    {
        using factor_t = std::ratio<113, 355>; // 0.31831
        using dimensions_t = dimensions::PlaneAngle;
        using offset_t = std::ratio<0, 1>;
        using relative_t = rev;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "rev";
        }
    };
    template<typename Value = long double>
    using Q_rev = units::Quantity<Value, rev>;
    namespace literals
    {
        static inline Q_rev<long double> operator "" _rev_ (long double _v) {
            return Q_rev<long double>(_v); }
        static inline Q_rev<long double> operator "" _rev_ (unsigned long long int _v) {
            return Q_rev<long double>(_v); }
    }



//
// Unit "deg"
//
    struct deg
    {
        using factor_t = std::ratio<71, 4068>; // 0.0174533
        using dimensions_t = dimensions::PlaneAngle;
        using offset_t = std::ratio<0, 1>;
        using relative_t = deg;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "deg";
        }
    };
    template<typename Value = long double>
    using Q_deg = units::Quantity<Value, deg>;
    namespace literals
    {
        static inline Q_deg<long double> operator "" _deg_ (long double _v) {
            return Q_deg<long double>(_v); }
        static inline Q_deg<long double> operator "" _deg_ (unsigned long long int _v) {
            return Q_deg<long double>(_v); }
    }



//
// Unit "grad"
//
    struct grad
    {
        using factor_t = std::ratio<71, 4520>; // 0.015708
        using dimensions_t = dimensions::PlaneAngle;
        using offset_t = std::ratio<0, 1>;
        using relative_t = grad;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "grad";
        }
    };
    template<typename Value = long double>
    using Q_grad = units::Quantity<Value, grad>;
    namespace literals
    {
        static inline Q_grad<long double> operator "" _grad_ (long double _v) {
            return Q_grad<long double>(_v); }
        static inline Q_grad<long double> operator "" _grad_ (unsigned long long int _v) {
            return Q_grad<long double>(_v); }
    }



//
// Unit "rad_per_s"
//
    struct rad_per_s
    {
        using factor_t = std::ratio<1, 1>; // 1
        using dimensions_t = dimensions::AngularVelocity;
        using offset_t = std::ratio<0, 1>;
        using relative_t = rad_per_s;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "rad_per_s";
        }
    };
    template<typename Value = long double>
    using Q_rad_per_s = units::Quantity<Value, rad_per_s>;
    namespace literals
    {
        static inline Q_rad_per_s<long double> operator "" _rad_per_s_ (long double _v) {
            return Q_rad_per_s<long double>(_v); }
        static inline Q_rad_per_s<long double> operator "" _rad_per_s_ (unsigned long long int _v) {
            return Q_rad_per_s<long double>(_v); }
    }



//
// Unit "rev_per_s"
//
    struct rev_per_s
    {
        using factor_t = std::ratio<113, 355>; // 0.31831
        using dimensions_t = dimensions::AngularVelocity;
        using offset_t = std::ratio<0, 1>;
        using relative_t = rev_per_s;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "rev_per_s";
        }
    };
    template<typename Value = long double>
    using Q_rev_per_s = units::Quantity<Value, rev_per_s>;
    namespace literals
    {
        static inline Q_rev_per_s<long double> operator "" _rev_per_s_ (long double _v) {
            return Q_rev_per_s<long double>(_v); }
        static inline Q_rev_per_s<long double> operator "" _rev_per_s_ (unsigned long long int _v) {
            return Q_rev_per_s<long double>(_v); }
    }



//
// Unit "deg_per_s"
//
    struct deg_per_s
    {
        using factor_t = std::ratio<71, 4068>; // 0.0174533
        using dimensions_t = dimensions::AngularVelocity;
        using offset_t = std::ratio<0, 1>;
        using relative_t = deg_per_s;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "deg_per_s";
        }
    };
    template<typename Value = long double>
    using Q_deg_per_s = units::Quantity<Value, deg_per_s>;
    namespace literals
    {
        static inline Q_deg_per_s<long double> operator "" _deg_per_s_ (long double _v) {
            return Q_deg_per_s<long double>(_v); }
        static inline Q_deg_per_s<long double> operator "" _deg_per_s_ (unsigned long long int _v) {
            return Q_deg_per_s<long double>(_v); }
    }



//
// Unit "grad_per_s"
//
    struct grad_per_s
    {
        using factor_t = std::ratio<71, 4520>; // 0.015708
        using dimensions_t = dimensions::AngularVelocity;
        using offset_t = std::ratio<0, 1>;
        using relative_t = grad_per_s;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "grad_per_s";
        }
    };
    template<typename Value = long double>
    using Q_grad_per_s = units::Quantity<Value, grad_per_s>;
    namespace literals
    {
        static inline Q_grad_per_s<long double> operator "" _grad_per_s_ (long double _v) {
            return Q_grad_per_s<long double>(_v); }
        static inline Q_grad_per_s<long double> operator "" _grad_per_s_ (unsigned long long int _v) {
            return Q_grad_per_s<long double>(_v); }
    }



//
// Unit "rpm"
//
    struct rpm
    {
        using factor_t = std::ratio<442, 83315>; // 0.00530517
        using dimensions_t = dimensions::AngularVelocity;
        using offset_t = std::ratio<0, 1>;
        using relative_t = rpm;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "rpm";
        }
    };
    template<typename Value = long double>
    using Q_rpm = units::Quantity<Value, rpm>;
    namespace literals
    {
        static inline Q_rpm<long double> operator "" _rpm_ (long double _v) {
            return Q_rpm<long double>(_v); }
        static inline Q_rpm<long double> operator "" _rpm_ (unsigned long long int _v) {
            return Q_rpm<long double>(_v); }
    }



//
// Unit "rad_per_s2"
//
    struct rad_per_s2
    {
        using factor_t = std::ratio<1, 1>; // 1
        using dimensions_t = dimensions::AngularAcceleration;
        using offset_t = std::ratio<0, 1>;
        using relative_t = rad_per_s2;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "rad_per_s2";
        }
    };
    template<typename Value = long double>
    using Q_rad_per_s2 = units::Quantity<Value, rad_per_s2>;
    namespace literals
    {
        static inline Q_rad_per_s2<long double> operator "" _rad_per_s2_ (long double _v) {
            return Q_rad_per_s2<long double>(_v); }
        static inline Q_rad_per_s2<long double> operator "" _rad_per_s2_ (unsigned long long int _v) {
            return Q_rad_per_s2<long double>(_v); }
    }



//
// Unit "rev_per_s2"
//
    struct rev_per_s2
    {
        using factor_t = std::ratio<113, 355>; // 0.31831
        using dimensions_t = dimensions::AngularAcceleration;
        using offset_t = std::ratio<0, 1>;
        using relative_t = rev_per_s2;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "rev_per_s2";
        }
    };
    template<typename Value = long double>
    using Q_rev_per_s2 = units::Quantity<Value, rev_per_s2>;
    namespace literals
    {
        static inline Q_rev_per_s2<long double> operator "" _rev_per_s2_ (long double _v) {
            return Q_rev_per_s2<long double>(_v); }
        static inline Q_rev_per_s2<long double> operator "" _rev_per_s2_ (unsigned long long int _v) {
            return Q_rev_per_s2<long double>(_v); }
    }



//
// Unit "deg_per_s2"
//
    struct deg_per_s2
    {
        using factor_t = std::ratio<71, 4068>; // 0.0174533
        using dimensions_t = dimensions::AngularAcceleration;
        using offset_t = std::ratio<0, 1>;
        using relative_t = deg_per_s2;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "deg_per_s2";
        }
    };
    template<typename Value = long double>
    using Q_deg_per_s2 = units::Quantity<Value, deg_per_s2>;
    namespace literals
    {
        static inline Q_deg_per_s2<long double> operator "" _deg_per_s2_ (long double _v) {
            return Q_deg_per_s2<long double>(_v); }
        static inline Q_deg_per_s2<long double> operator "" _deg_per_s2_ (unsigned long long int _v) {
            return Q_deg_per_s2<long double>(_v); }
    }



//
// Unit "grad_per_s2"
//
    struct grad_per_s2
    {
        using factor_t = std::ratio<71, 4520>; // 0.015708
        using dimensions_t = dimensions::AngularAcceleration;
        using offset_t = std::ratio<0, 1>;
        using relative_t = grad_per_s2;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "grad_per_s2";
        }
    };
    template<typename Value = long double>
    using Q_grad_per_s2 = units::Quantity<Value, grad_per_s2>;
    namespace literals
    {
        static inline Q_grad_per_s2<long double> operator "" _grad_per_s2_ (long double _v) {
            return Q_grad_per_s2<long double>(_v); }
        static inline Q_grad_per_s2<long double> operator "" _grad_per_s2_ (unsigned long long int _v) {
            return Q_grad_per_s2<long double>(_v); }
    }



//
// Unit "EC"
//
    struct EC
    {
        using factor_t = std::ratio<1000000000000000000, 1>; // 1e+18
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = EC;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "EC";
        }
    };
    template<typename Value = long double>
    using Q_EC = units::Quantity<Value, EC>;
    namespace literals
    {
        static inline Q_EC<long double> operator "" _EC_ (long double _v) {
            return Q_EC<long double>(_v); }
        static inline Q_EC<long double> operator "" _EC_ (unsigned long long int _v) {
            return Q_EC<long double>(_v); }
    }



//
// Unit "EC_abs"
//
    struct EC_abs
    {
        using factor_t = std::ratio<1000000000000000000, 1>; // 1e+18
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = EC;
        static constexpr bool absolute = true;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "EC_abs";
        }
    };
    template<typename Value = long double>
    using Q_EC_abs = units::Quantity<Value, EC_abs>;
    namespace literals
    {
        static inline Q_EC_abs<long double> operator "" _EC_abs_ (long double _v) {
            return Q_EC_abs<long double>(_v); }
        static inline Q_EC_abs<long double> operator "" _EC_abs_ (unsigned long long int _v) {
            return Q_EC_abs<long double>(_v); }
    }



//
// Unit "PC"
//
    struct PC
    {
        using factor_t = std::ratio<1000000000000000, 1>; // 1e+15
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = PC;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "PC";
        }
    };
    template<typename Value = long double>
    using Q_PC = units::Quantity<Value, PC>;
    namespace literals
    {
        static inline Q_PC<long double> operator "" _PC_ (long double _v) {
            return Q_PC<long double>(_v); }
        static inline Q_PC<long double> operator "" _PC_ (unsigned long long int _v) {
            return Q_PC<long double>(_v); }
    }



//
// Unit "PC_abs"
//
    struct PC_abs
    {
        using factor_t = std::ratio<1000000000000000, 1>; // 1e+15
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = PC;
        static constexpr bool absolute = true;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "PC_abs";
        }
    };
    template<typename Value = long double>
    using Q_PC_abs = units::Quantity<Value, PC_abs>;
    namespace literals
    {
        static inline Q_PC_abs<long double> operator "" _PC_abs_ (long double _v) {
            return Q_PC_abs<long double>(_v); }
        static inline Q_PC_abs<long double> operator "" _PC_abs_ (unsigned long long int _v) {
            return Q_PC_abs<long double>(_v); }
    }



//
// Unit "TC"
//
    struct TC
    {
        using factor_t = std::ratio<1000000000000, 1>; // 1e+12
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = TC;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "TC";
        }
    };
    template<typename Value = long double>
    using Q_TC = units::Quantity<Value, TC>;
    namespace literals
    {
        static inline Q_TC<long double> operator "" _TC_ (long double _v) {
            return Q_TC<long double>(_v); }
        static inline Q_TC<long double> operator "" _TC_ (unsigned long long int _v) {
            return Q_TC<long double>(_v); }
    }



//
// Unit "TC_abs"
//
    struct TC_abs
    {
        using factor_t = std::ratio<1000000000000, 1>; // 1e+12
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = TC;
        static constexpr bool absolute = true;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "TC_abs";
        }
    };
    template<typename Value = long double>
    using Q_TC_abs = units::Quantity<Value, TC_abs>;
    namespace literals
    {
        static inline Q_TC_abs<long double> operator "" _TC_abs_ (long double _v) {
            return Q_TC_abs<long double>(_v); }
        static inline Q_TC_abs<long double> operator "" _TC_abs_ (unsigned long long int _v) {
            return Q_TC_abs<long double>(_v); }
    }



//
// Unit "GC"
//
    struct GC
    {
        using factor_t = std::ratio<1000000000, 1>; // 1e+09
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = GC;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "GC";
        }
    };
    template<typename Value = long double>
    using Q_GC = units::Quantity<Value, GC>;
    namespace literals
    {
        static inline Q_GC<long double> operator "" _GC_ (long double _v) {
            return Q_GC<long double>(_v); }
        static inline Q_GC<long double> operator "" _GC_ (unsigned long long int _v) {
            return Q_GC<long double>(_v); }
    }



//
// Unit "GC_abs"
//
    struct GC_abs
    {
        using factor_t = std::ratio<1000000000, 1>; // 1e+09
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = GC;
        static constexpr bool absolute = true;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "GC_abs";
        }
    };
    template<typename Value = long double>
    using Q_GC_abs = units::Quantity<Value, GC_abs>;
    namespace literals
    {
        static inline Q_GC_abs<long double> operator "" _GC_abs_ (long double _v) {
            return Q_GC_abs<long double>(_v); }
        static inline Q_GC_abs<long double> operator "" _GC_abs_ (unsigned long long int _v) {
            return Q_GC_abs<long double>(_v); }
    }



//
// Unit "MC"
//
    struct MC
    {
        using factor_t = std::ratio<1000000, 1>; // 1e+06
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = MC;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "MC";
        }
    };
    template<typename Value = long double>
    using Q_MC = units::Quantity<Value, MC>;
    namespace literals
    {
        static inline Q_MC<long double> operator "" _MC_ (long double _v) {
            return Q_MC<long double>(_v); }
        static inline Q_MC<long double> operator "" _MC_ (unsigned long long int _v) {
            return Q_MC<long double>(_v); }
    }



//
// Unit "MC_abs"
//
    struct MC_abs
    {
        using factor_t = std::ratio<1000000, 1>; // 1e+06
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = MC;
        static constexpr bool absolute = true;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "MC_abs";
        }
    };
    template<typename Value = long double>
    using Q_MC_abs = units::Quantity<Value, MC_abs>;
    namespace literals
    {
        static inline Q_MC_abs<long double> operator "" _MC_abs_ (long double _v) {
            return Q_MC_abs<long double>(_v); }
        static inline Q_MC_abs<long double> operator "" _MC_abs_ (unsigned long long int _v) {
            return Q_MC_abs<long double>(_v); }
    }



//
// Unit "kC"
//
    struct kC
    {
        using factor_t = std::ratio<1000, 1>; // 1000
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = kC;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "kC";
        }
    };
    template<typename Value = long double>
    using Q_kC = units::Quantity<Value, kC>;
    namespace literals
    {
        static inline Q_kC<long double> operator "" _kC_ (long double _v) {
            return Q_kC<long double>(_v); }
        static inline Q_kC<long double> operator "" _kC_ (unsigned long long int _v) {
            return Q_kC<long double>(_v); }
    }



//
// Unit "kC_abs"
//
    struct kC_abs
    {
        using factor_t = std::ratio<1000, 1>; // 1000
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = kC;
        static constexpr bool absolute = true;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "kC_abs";
        }
    };
    template<typename Value = long double>
    using Q_kC_abs = units::Quantity<Value, kC_abs>;
    namespace literals
    {
        static inline Q_kC_abs<long double> operator "" _kC_abs_ (long double _v) {
            return Q_kC_abs<long double>(_v); }
        static inline Q_kC_abs<long double> operator "" _kC_abs_ (unsigned long long int _v) {
            return Q_kC_abs<long double>(_v); }
    }



//
// Unit "hC"
//
    struct hC
    {
        using factor_t = std::ratio<100, 1>; // 100
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = hC;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "hC";
        }
    };
    template<typename Value = long double>
    using Q_hC = units::Quantity<Value, hC>;
    namespace literals
    {
        static inline Q_hC<long double> operator "" _hC_ (long double _v) {
            return Q_hC<long double>(_v); }
        static inline Q_hC<long double> operator "" _hC_ (unsigned long long int _v) {
            return Q_hC<long double>(_v); }
    }



//
// Unit "hC_abs"
//
    struct hC_abs
    {
        using factor_t = std::ratio<100, 1>; // 100
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = hC;
        static constexpr bool absolute = true;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "hC_abs";
        }
    };
    template<typename Value = long double>
    using Q_hC_abs = units::Quantity<Value, hC_abs>;
    namespace literals
    {
        static inline Q_hC_abs<long double> operator "" _hC_abs_ (long double _v) {
            return Q_hC_abs<long double>(_v); }
        static inline Q_hC_abs<long double> operator "" _hC_abs_ (unsigned long long int _v) {
            return Q_hC_abs<long double>(_v); }
    }



//
// Unit "daC"
//
    struct daC
    {
        using factor_t = std::ratio<10, 1>; // 10
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = daC;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "daC";
        }
    };
    template<typename Value = long double>
    using Q_daC = units::Quantity<Value, daC>;
    namespace literals
    {
        static inline Q_daC<long double> operator "" _daC_ (long double _v) {
            return Q_daC<long double>(_v); }
        static inline Q_daC<long double> operator "" _daC_ (unsigned long long int _v) {
            return Q_daC<long double>(_v); }
    }



//
// Unit "daC_abs"
//
    struct daC_abs
    {
        using factor_t = std::ratio<10, 1>; // 10
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = daC;
        static constexpr bool absolute = true;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "daC_abs";
        }
    };
    template<typename Value = long double>
    using Q_daC_abs = units::Quantity<Value, daC_abs>;
    namespace literals
    {
        static inline Q_daC_abs<long double> operator "" _daC_abs_ (long double _v) {
            return Q_daC_abs<long double>(_v); }
        static inline Q_daC_abs<long double> operator "" _daC_abs_ (unsigned long long int _v) {
            return Q_daC_abs<long double>(_v); }
    }



//
// Unit "C"
//
    struct C
    {
        using factor_t = std::ratio<1, 1>; // 1
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = C;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "C";
        }
    };
    template<typename Value = long double>
    using Q_C = units::Quantity<Value, C>;
    namespace literals
    {
        static inline Q_C<long double> operator "" _C_ (long double _v) {
            return Q_C<long double>(_v); }
        static inline Q_C<long double> operator "" _C_ (unsigned long long int _v) {
            return Q_C<long double>(_v); }
    }



//
// Unit "C_abs"
//
    struct C_abs
    {
        using factor_t = std::ratio<1, 1>; // 1
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = C;
        static constexpr bool absolute = true;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "C_abs";
        }
    };
    template<typename Value = long double>
    using Q_C_abs = units::Quantity<Value, C_abs>;
    namespace literals
    {
        static inline Q_C_abs<long double> operator "" _C_abs_ (long double _v) {
            return Q_C_abs<long double>(_v); }
        static inline Q_C_abs<long double> operator "" _C_abs_ (unsigned long long int _v) {
            return Q_C_abs<long double>(_v); }
    }



//
// Unit "dC"
//
    struct dC
    {
        using factor_t = std::ratio<1, 10>; // 0.1
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = dC;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "dC";
        }
    };
    template<typename Value = long double>
    using Q_dC = units::Quantity<Value, dC>;
    namespace literals
    {
        static inline Q_dC<long double> operator "" _dC_ (long double _v) {
            return Q_dC<long double>(_v); }
        static inline Q_dC<long double> operator "" _dC_ (unsigned long long int _v) {
            return Q_dC<long double>(_v); }
    }



//
// Unit "dC_abs"
//
    struct dC_abs
    {
        using factor_t = std::ratio<1, 10>; // 0.1
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = dC;
        static constexpr bool absolute = true;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "dC_abs";
        }
    };
    template<typename Value = long double>
    using Q_dC_abs = units::Quantity<Value, dC_abs>;
    namespace literals
    {
        static inline Q_dC_abs<long double> operator "" _dC_abs_ (long double _v) {
            return Q_dC_abs<long double>(_v); }
        static inline Q_dC_abs<long double> operator "" _dC_abs_ (unsigned long long int _v) {
            return Q_dC_abs<long double>(_v); }
    }



//
// Unit "cC"
//
    struct cC
    {
        using factor_t = std::ratio<1, 100>; // 0.01
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = cC;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "cC";
        }
    };
    template<typename Value = long double>
    using Q_cC = units::Quantity<Value, cC>;
    namespace literals
    {
        static inline Q_cC<long double> operator "" _cC_ (long double _v) {
            return Q_cC<long double>(_v); }
        static inline Q_cC<long double> operator "" _cC_ (unsigned long long int _v) {
            return Q_cC<long double>(_v); }
    }



//
// Unit "cC_abs"
//
    struct cC_abs
    {
        using factor_t = std::ratio<1, 100>; // 0.01
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = cC;
        static constexpr bool absolute = true;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "cC_abs";
        }
    };
    template<typename Value = long double>
    using Q_cC_abs = units::Quantity<Value, cC_abs>;
    namespace literals
    {
        static inline Q_cC_abs<long double> operator "" _cC_abs_ (long double _v) {
            return Q_cC_abs<long double>(_v); }
        static inline Q_cC_abs<long double> operator "" _cC_abs_ (unsigned long long int _v) {
            return Q_cC_abs<long double>(_v); }
    }



//
// Unit "mC"
//
    struct mC
    {
        using factor_t = std::ratio<1, 1000>; // 0.001
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = mC;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "mC";
        }
    };
    template<typename Value = long double>
    using Q_mC = units::Quantity<Value, mC>;
    namespace literals
    {
        static inline Q_mC<long double> operator "" _mC_ (long double _v) {
            return Q_mC<long double>(_v); }
        static inline Q_mC<long double> operator "" _mC_ (unsigned long long int _v) {
            return Q_mC<long double>(_v); }
    }



//
// Unit "mC_abs"
//
    struct mC_abs
    {
        using factor_t = std::ratio<1, 1000>; // 0.001
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = mC;
        static constexpr bool absolute = true;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "mC_abs";
        }
    };
    template<typename Value = long double>
    using Q_mC_abs = units::Quantity<Value, mC_abs>;
    namespace literals
    {
        static inline Q_mC_abs<long double> operator "" _mC_abs_ (long double _v) {
            return Q_mC_abs<long double>(_v); }
        static inline Q_mC_abs<long double> operator "" _mC_abs_ (unsigned long long int _v) {
            return Q_mC_abs<long double>(_v); }
    }



//
// Unit "EK"
//
    struct EK
    {
        using factor_t = std::ratio<1000000000000000000, 1>; // 1e+18
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = EK;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "EK";
        }
    };
    template<typename Value = long double>
    using Q_EK = units::Quantity<Value, EK>;
    namespace literals
    {
        static inline Q_EK<long double> operator "" _EK_ (long double _v) {
            return Q_EK<long double>(_v); }
        static inline Q_EK<long double> operator "" _EK_ (unsigned long long int _v) {
            return Q_EK<long double>(_v); }
    }



//
// Unit "EK_abs"
//
    struct EK_abs
    {
        using factor_t = std::ratio<1000000000000000000, 1>; // 1e+18
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = EK;
        static constexpr bool absolute = true;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "EK_abs";
        }
    };
    template<typename Value = long double>
    using Q_EK_abs = units::Quantity<Value, EK_abs>;
    namespace literals
    {
        static inline Q_EK_abs<long double> operator "" _EK_abs_ (long double _v) {
            return Q_EK_abs<long double>(_v); }
        static inline Q_EK_abs<long double> operator "" _EK_abs_ (unsigned long long int _v) {
            return Q_EK_abs<long double>(_v); }
    }



//
// Unit "PK"
//
    struct PK
    {
        using factor_t = std::ratio<1000000000000000, 1>; // 1e+15
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = PK;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "PK";
        }
    };
    template<typename Value = long double>
    using Q_PK = units::Quantity<Value, PK>;
    namespace literals
    {
        static inline Q_PK<long double> operator "" _PK_ (long double _v) {
            return Q_PK<long double>(_v); }
        static inline Q_PK<long double> operator "" _PK_ (unsigned long long int _v) {
            return Q_PK<long double>(_v); }
    }



//
// Unit "PK_abs"
//
    struct PK_abs
    {
        using factor_t = std::ratio<1000000000000000, 1>; // 1e+15
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = PK;
        static constexpr bool absolute = true;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "PK_abs";
        }
    };
    template<typename Value = long double>
    using Q_PK_abs = units::Quantity<Value, PK_abs>;
    namespace literals
    {
        static inline Q_PK_abs<long double> operator "" _PK_abs_ (long double _v) {
            return Q_PK_abs<long double>(_v); }
        static inline Q_PK_abs<long double> operator "" _PK_abs_ (unsigned long long int _v) {
            return Q_PK_abs<long double>(_v); }
    }



//
// Unit "TK"
//
    struct TK
    {
        using factor_t = std::ratio<1000000000000, 1>; // 1e+12
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = TK;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "TK";
        }
    };
    template<typename Value = long double>
    using Q_TK = units::Quantity<Value, TK>;
    namespace literals
    {
        static inline Q_TK<long double> operator "" _TK_ (long double _v) {
            return Q_TK<long double>(_v); }
        static inline Q_TK<long double> operator "" _TK_ (unsigned long long int _v) {
            return Q_TK<long double>(_v); }
    }



//
// Unit "TK_abs"
//
    struct TK_abs
    {
        using factor_t = std::ratio<1000000000000, 1>; // 1e+12
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = TK;
        static constexpr bool absolute = true;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "TK_abs";
        }
    };
    template<typename Value = long double>
    using Q_TK_abs = units::Quantity<Value, TK_abs>;
    namespace literals
    {
        static inline Q_TK_abs<long double> operator "" _TK_abs_ (long double _v) {
            return Q_TK_abs<long double>(_v); }
        static inline Q_TK_abs<long double> operator "" _TK_abs_ (unsigned long long int _v) {
            return Q_TK_abs<long double>(_v); }
    }



//
// Unit "GK"
//
    struct GK
    {
        using factor_t = std::ratio<1000000000, 1>; // 1e+09
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = GK;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "GK";
        }
    };
    template<typename Value = long double>
    using Q_GK = units::Quantity<Value, GK>;
    namespace literals
    {
        static inline Q_GK<long double> operator "" _GK_ (long double _v) {
            return Q_GK<long double>(_v); }
        static inline Q_GK<long double> operator "" _GK_ (unsigned long long int _v) {
            return Q_GK<long double>(_v); }
    }



//
// Unit "GK_abs"
//
    struct GK_abs
    {
        using factor_t = std::ratio<1000000000, 1>; // 1e+09
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = GK;
        static constexpr bool absolute = true;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "GK_abs";
        }
    };
    template<typename Value = long double>
    using Q_GK_abs = units::Quantity<Value, GK_abs>;
    namespace literals
    {
        static inline Q_GK_abs<long double> operator "" _GK_abs_ (long double _v) {
            return Q_GK_abs<long double>(_v); }
        static inline Q_GK_abs<long double> operator "" _GK_abs_ (unsigned long long int _v) {
            return Q_GK_abs<long double>(_v); }
    }



//
// Unit "MK"
//
    struct MK
    {
        using factor_t = std::ratio<1000000, 1>; // 1e+06
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = MK;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "MK";
        }
    };
    template<typename Value = long double>
    using Q_MK = units::Quantity<Value, MK>;
    namespace literals
    {
        static inline Q_MK<long double> operator "" _MK_ (long double _v) {
            return Q_MK<long double>(_v); }
        static inline Q_MK<long double> operator "" _MK_ (unsigned long long int _v) {
            return Q_MK<long double>(_v); }
    }



//
// Unit "MK_abs"
//
    struct MK_abs
    {
        using factor_t = std::ratio<1000000, 1>; // 1e+06
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = MK;
        static constexpr bool absolute = true;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "MK_abs";
        }
    };
    template<typename Value = long double>
    using Q_MK_abs = units::Quantity<Value, MK_abs>;
    namespace literals
    {
        static inline Q_MK_abs<long double> operator "" _MK_abs_ (long double _v) {
            return Q_MK_abs<long double>(_v); }
        static inline Q_MK_abs<long double> operator "" _MK_abs_ (unsigned long long int _v) {
            return Q_MK_abs<long double>(_v); }
    }



//
// Unit "kK"
//
    struct kK
    {
        using factor_t = std::ratio<1000, 1>; // 1000
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = kK;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "kK";
        }
    };
    template<typename Value = long double>
    using Q_kK = units::Quantity<Value, kK>;
    namespace literals
    {
        static inline Q_kK<long double> operator "" _kK_ (long double _v) {
            return Q_kK<long double>(_v); }
        static inline Q_kK<long double> operator "" _kK_ (unsigned long long int _v) {
            return Q_kK<long double>(_v); }
    }



//
// Unit "kK_abs"
//
    struct kK_abs
    {
        using factor_t = std::ratio<1000, 1>; // 1000
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = kK;
        static constexpr bool absolute = true;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "kK_abs";
        }
    };
    template<typename Value = long double>
    using Q_kK_abs = units::Quantity<Value, kK_abs>;
    namespace literals
    {
        static inline Q_kK_abs<long double> operator "" _kK_abs_ (long double _v) {
            return Q_kK_abs<long double>(_v); }
        static inline Q_kK_abs<long double> operator "" _kK_abs_ (unsigned long long int _v) {
            return Q_kK_abs<long double>(_v); }
    }



//
// Unit "hK"
//
    struct hK
    {
        using factor_t = std::ratio<100, 1>; // 100
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = hK;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "hK";
        }
    };
    template<typename Value = long double>
    using Q_hK = units::Quantity<Value, hK>;
    namespace literals
    {
        static inline Q_hK<long double> operator "" _hK_ (long double _v) {
            return Q_hK<long double>(_v); }
        static inline Q_hK<long double> operator "" _hK_ (unsigned long long int _v) {
            return Q_hK<long double>(_v); }
    }



//
// Unit "hK_abs"
//
    struct hK_abs
    {
        using factor_t = std::ratio<100, 1>; // 100
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = hK;
        static constexpr bool absolute = true;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "hK_abs";
        }
    };
    template<typename Value = long double>
    using Q_hK_abs = units::Quantity<Value, hK_abs>;
    namespace literals
    {
        static inline Q_hK_abs<long double> operator "" _hK_abs_ (long double _v) {
            return Q_hK_abs<long double>(_v); }
        static inline Q_hK_abs<long double> operator "" _hK_abs_ (unsigned long long int _v) {
            return Q_hK_abs<long double>(_v); }
    }



//
// Unit "daK"
//
    struct daK
    {
        using factor_t = std::ratio<10, 1>; // 10
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = daK;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "daK";
        }
    };
    template<typename Value = long double>
    using Q_daK = units::Quantity<Value, daK>;
    namespace literals
    {
        static inline Q_daK<long double> operator "" _daK_ (long double _v) {
            return Q_daK<long double>(_v); }
        static inline Q_daK<long double> operator "" _daK_ (unsigned long long int _v) {
            return Q_daK<long double>(_v); }
    }



//
// Unit "daK_abs"
//
    struct daK_abs
    {
        using factor_t = std::ratio<10, 1>; // 10
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = daK;
        static constexpr bool absolute = true;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "daK_abs";
        }
    };
    template<typename Value = long double>
    using Q_daK_abs = units::Quantity<Value, daK_abs>;
    namespace literals
    {
        static inline Q_daK_abs<long double> operator "" _daK_abs_ (long double _v) {
            return Q_daK_abs<long double>(_v); }
        static inline Q_daK_abs<long double> operator "" _daK_abs_ (unsigned long long int _v) {
            return Q_daK_abs<long double>(_v); }
    }



//
// Unit "K"
//
    struct K
    {
        using factor_t = std::ratio<1, 1>; // 1
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = K;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "K";
        }
    };
    template<typename Value = long double>
    using Q_K = units::Quantity<Value, K>;
    namespace literals
    {
        static inline Q_K<long double> operator "" _K_ (long double _v) {
            return Q_K<long double>(_v); }
        static inline Q_K<long double> operator "" _K_ (unsigned long long int _v) {
            return Q_K<long double>(_v); }
    }



//
// Unit "K_abs"
//
    struct K_abs
    {
        using factor_t = std::ratio<1, 1>; // 1
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = K;
        static constexpr bool absolute = true;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "K_abs";
        }
    };
    template<typename Value = long double>
    using Q_K_abs = units::Quantity<Value, K_abs>;
    namespace literals
    {
        static inline Q_K_abs<long double> operator "" _K_abs_ (long double _v) {
            return Q_K_abs<long double>(_v); }
        static inline Q_K_abs<long double> operator "" _K_abs_ (unsigned long long int _v) {
            return Q_K_abs<long double>(_v); }
    }



//
// Unit "dK"
//
    struct dK
    {
        using factor_t = std::ratio<1, 10>; // 0.1
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = dK;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "dK";
        }
    };
    template<typename Value = long double>
    using Q_dK = units::Quantity<Value, dK>;
    namespace literals
    {
        static inline Q_dK<long double> operator "" _dK_ (long double _v) {
            return Q_dK<long double>(_v); }
        static inline Q_dK<long double> operator "" _dK_ (unsigned long long int _v) {
            return Q_dK<long double>(_v); }
    }



//
// Unit "dK_abs"
//
    struct dK_abs
    {
        using factor_t = std::ratio<1, 10>; // 0.1
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = dK;
        static constexpr bool absolute = true;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "dK_abs";
        }
    };
    template<typename Value = long double>
    using Q_dK_abs = units::Quantity<Value, dK_abs>;
    namespace literals
    {
        static inline Q_dK_abs<long double> operator "" _dK_abs_ (long double _v) {
            return Q_dK_abs<long double>(_v); }
        static inline Q_dK_abs<long double> operator "" _dK_abs_ (unsigned long long int _v) {
            return Q_dK_abs<long double>(_v); }
    }



//
// Unit "cK"
//
    struct cK
    {
        using factor_t = std::ratio<1, 100>; // 0.01
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = cK;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "cK";
        }
    };
    template<typename Value = long double>
    using Q_cK = units::Quantity<Value, cK>;
    namespace literals
    {
        static inline Q_cK<long double> operator "" _cK_ (long double _v) {
            return Q_cK<long double>(_v); }
        static inline Q_cK<long double> operator "" _cK_ (unsigned long long int _v) {
            return Q_cK<long double>(_v); }
    }



//
// Unit "cK_abs"
//
    struct cK_abs
    {
        using factor_t = std::ratio<1, 100>; // 0.01
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = cK;
        static constexpr bool absolute = true;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "cK_abs";
        }
    };
    template<typename Value = long double>
    using Q_cK_abs = units::Quantity<Value, cK_abs>;
    namespace literals
    {
        static inline Q_cK_abs<long double> operator "" _cK_abs_ (long double _v) {
            return Q_cK_abs<long double>(_v); }
        static inline Q_cK_abs<long double> operator "" _cK_abs_ (unsigned long long int _v) {
            return Q_cK_abs<long double>(_v); }
    }



//
// Unit "mK"
//
    struct mK
    {
        using factor_t = std::ratio<1, 1000>; // 0.001
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = mK;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "mK";
        }
    };
    template<typename Value = long double>
    using Q_mK = units::Quantity<Value, mK>;
    namespace literals
    {
        static inline Q_mK<long double> operator "" _mK_ (long double _v) {
            return Q_mK<long double>(_v); }
        static inline Q_mK<long double> operator "" _mK_ (unsigned long long int _v) {
            return Q_mK<long double>(_v); }
    }



//
// Unit "mK_abs"
//
    struct mK_abs
    {
        using factor_t = std::ratio<1, 1000>; // 0.001
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = mK;
        static constexpr bool absolute = true;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "mK_abs";
        }
    };
    template<typename Value = long double>
    using Q_mK_abs = units::Quantity<Value, mK_abs>;
    namespace literals
    {
        static inline Q_mK_abs<long double> operator "" _mK_abs_ (long double _v) {
            return Q_mK_abs<long double>(_v); }
        static inline Q_mK_abs<long double> operator "" _mK_abs_ (unsigned long long int _v) {
            return Q_mK_abs<long double>(_v); }
    }



//
// Unit "EF"
//
    struct EF
    {
        using factor_t = std::ratio<555555500000000000, 1>; // 5.55556e+17
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = EF;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "EF";
        }
    };
    template<typename Value = long double>
    using Q_EF = units::Quantity<Value, EF>;
    namespace literals
    {
        static inline Q_EF<long double> operator "" _EF_ (long double _v) {
            return Q_EF<long double>(_v); }
        static inline Q_EF<long double> operator "" _EF_ (unsigned long long int _v) {
            return Q_EF<long double>(_v); }
    }



//
// Unit "EF_abs"
//
    struct EF_abs
    {
        using factor_t = std::ratio<555555500000000000, 1>; // 5.55556e+17
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = EF;
        static constexpr bool absolute = true;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "EF_abs";
        }
    };
    template<typename Value = long double>
    using Q_EF_abs = units::Quantity<Value, EF_abs>;
    namespace literals
    {
        static inline Q_EF_abs<long double> operator "" _EF_abs_ (long double _v) {
            return Q_EF_abs<long double>(_v); }
        static inline Q_EF_abs<long double> operator "" _EF_abs_ (unsigned long long int _v) {
            return Q_EF_abs<long double>(_v); }
    }



//
// Unit "PF"
//
    struct PF
    {
        using factor_t = std::ratio<555555500000000, 1>; // 5.55556e+14
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = PF;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "PF";
        }
    };
    template<typename Value = long double>
    using Q_PF = units::Quantity<Value, PF>;
    namespace literals
    {
        static inline Q_PF<long double> operator "" _PF_ (long double _v) {
            return Q_PF<long double>(_v); }
        static inline Q_PF<long double> operator "" _PF_ (unsigned long long int _v) {
            return Q_PF<long double>(_v); }
    }



//
// Unit "PF_abs"
//
    struct PF_abs
    {
        using factor_t = std::ratio<555555500000000, 1>; // 5.55556e+14
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = PF;
        static constexpr bool absolute = true;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "PF_abs";
        }
    };
    template<typename Value = long double>
    using Q_PF_abs = units::Quantity<Value, PF_abs>;
    namespace literals
    {
        static inline Q_PF_abs<long double> operator "" _PF_abs_ (long double _v) {
            return Q_PF_abs<long double>(_v); }
        static inline Q_PF_abs<long double> operator "" _PF_abs_ (unsigned long long int _v) {
            return Q_PF_abs<long double>(_v); }
    }



//
// Unit "TF"
//
    struct TF
    {
        using factor_t = std::ratio<555555500000, 1>; // 5.55556e+11
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = TF;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "TF";
        }
    };
    template<typename Value = long double>
    using Q_TF = units::Quantity<Value, TF>;
    namespace literals
    {
        static inline Q_TF<long double> operator "" _TF_ (long double _v) {
            return Q_TF<long double>(_v); }
        static inline Q_TF<long double> operator "" _TF_ (unsigned long long int _v) {
            return Q_TF<long double>(_v); }
    }



//
// Unit "TF_abs"
//
    struct TF_abs
    {
        using factor_t = std::ratio<555555500000, 1>; // 5.55556e+11
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = TF;
        static constexpr bool absolute = true;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "TF_abs";
        }
    };
    template<typename Value = long double>
    using Q_TF_abs = units::Quantity<Value, TF_abs>;
    namespace literals
    {
        static inline Q_TF_abs<long double> operator "" _TF_abs_ (long double _v) {
            return Q_TF_abs<long double>(_v); }
        static inline Q_TF_abs<long double> operator "" _TF_abs_ (unsigned long long int _v) {
            return Q_TF_abs<long double>(_v); }
    }



//
// Unit "GF"
//
    struct GF
    {
        using factor_t = std::ratio<555555500, 1>; // 5.55556e+08
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = GF;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "GF";
        }
    };
    template<typename Value = long double>
    using Q_GF = units::Quantity<Value, GF>;
    namespace literals
    {
        static inline Q_GF<long double> operator "" _GF_ (long double _v) {
            return Q_GF<long double>(_v); }
        static inline Q_GF<long double> operator "" _GF_ (unsigned long long int _v) {
            return Q_GF<long double>(_v); }
    }



//
// Unit "GF_abs"
//
    struct GF_abs
    {
        using factor_t = std::ratio<555555500, 1>; // 5.55556e+08
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = GF;
        static constexpr bool absolute = true;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "GF_abs";
        }
    };
    template<typename Value = long double>
    using Q_GF_abs = units::Quantity<Value, GF_abs>;
    namespace literals
    {
        static inline Q_GF_abs<long double> operator "" _GF_abs_ (long double _v) {
            return Q_GF_abs<long double>(_v); }
        static inline Q_GF_abs<long double> operator "" _GF_abs_ (unsigned long long int _v) {
            return Q_GF_abs<long double>(_v); }
    }



//
// Unit "MF"
//
    struct MF
    {
        using factor_t = std::ratio<1111111, 2>; // 555556
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = MF;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "MF";
        }
    };
    template<typename Value = long double>
    using Q_MF = units::Quantity<Value, MF>;
    namespace literals
    {
        static inline Q_MF<long double> operator "" _MF_ (long double _v) {
            return Q_MF<long double>(_v); }
        static inline Q_MF<long double> operator "" _MF_ (unsigned long long int _v) {
            return Q_MF<long double>(_v); }
    }



//
// Unit "MF_abs"
//
    struct MF_abs
    {
        using factor_t = std::ratio<1111111, 2>; // 555556
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = MF;
        static constexpr bool absolute = true;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "MF_abs";
        }
    };
    template<typename Value = long double>
    using Q_MF_abs = units::Quantity<Value, MF_abs>;
    namespace literals
    {
        static inline Q_MF_abs<long double> operator "" _MF_abs_ (long double _v) {
            return Q_MF_abs<long double>(_v); }
        static inline Q_MF_abs<long double> operator "" _MF_abs_ (unsigned long long int _v) {
            return Q_MF_abs<long double>(_v); }
    }



//
// Unit "kF"
//
    struct kF
    {
        using factor_t = std::ratio<1111111, 2000>; // 555.555
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = kF;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "kF";
        }
    };
    template<typename Value = long double>
    using Q_kF = units::Quantity<Value, kF>;
    namespace literals
    {
        static inline Q_kF<long double> operator "" _kF_ (long double _v) {
            return Q_kF<long double>(_v); }
        static inline Q_kF<long double> operator "" _kF_ (unsigned long long int _v) {
            return Q_kF<long double>(_v); }
    }



//
// Unit "kF_abs"
//
    struct kF_abs
    {
        using factor_t = std::ratio<1111111, 2000>; // 555.555
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = kF;
        static constexpr bool absolute = true;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "kF_abs";
        }
    };
    template<typename Value = long double>
    using Q_kF_abs = units::Quantity<Value, kF_abs>;
    namespace literals
    {
        static inline Q_kF_abs<long double> operator "" _kF_abs_ (long double _v) {
            return Q_kF_abs<long double>(_v); }
        static inline Q_kF_abs<long double> operator "" _kF_abs_ (unsigned long long int _v) {
            return Q_kF_abs<long double>(_v); }
    }



//
// Unit "hF"
//
    struct hF
    {
        using factor_t = std::ratio<1111111, 20000>; // 55.5555
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = hF;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "hF";
        }
    };
    template<typename Value = long double>
    using Q_hF = units::Quantity<Value, hF>;
    namespace literals
    {
        static inline Q_hF<long double> operator "" _hF_ (long double _v) {
            return Q_hF<long double>(_v); }
        static inline Q_hF<long double> operator "" _hF_ (unsigned long long int _v) {
            return Q_hF<long double>(_v); }
    }



//
// Unit "hF_abs"
//
    struct hF_abs
    {
        using factor_t = std::ratio<1111111, 20000>; // 55.5555
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = hF;
        static constexpr bool absolute = true;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "hF_abs";
        }
    };
    template<typename Value = long double>
    using Q_hF_abs = units::Quantity<Value, hF_abs>;
    namespace literals
    {
        static inline Q_hF_abs<long double> operator "" _hF_abs_ (long double _v) {
            return Q_hF_abs<long double>(_v); }
        static inline Q_hF_abs<long double> operator "" _hF_abs_ (unsigned long long int _v) {
            return Q_hF_abs<long double>(_v); }
    }



//
// Unit "daF"
//
    struct daF
    {
        using factor_t = std::ratio<1111111, 200000>; // 5.55556
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = daF;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "daF";
        }
    };
    template<typename Value = long double>
    using Q_daF = units::Quantity<Value, daF>;
    namespace literals
    {
        static inline Q_daF<long double> operator "" _daF_ (long double _v) {
            return Q_daF<long double>(_v); }
        static inline Q_daF<long double> operator "" _daF_ (unsigned long long int _v) {
            return Q_daF<long double>(_v); }
    }



//
// Unit "daF_abs"
//
    struct daF_abs
    {
        using factor_t = std::ratio<1111111, 200000>; // 5.55556
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = daF;
        static constexpr bool absolute = true;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "daF_abs";
        }
    };
    template<typename Value = long double>
    using Q_daF_abs = units::Quantity<Value, daF_abs>;
    namespace literals
    {
        static inline Q_daF_abs<long double> operator "" _daF_abs_ (long double _v) {
            return Q_daF_abs<long double>(_v); }
        static inline Q_daF_abs<long double> operator "" _daF_abs_ (unsigned long long int _v) {
            return Q_daF_abs<long double>(_v); }
    }



//
// Unit "F"
//
    struct F
    {
        using factor_t = std::ratio<5, 9>; // 0.555555
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = F;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "F";
        }
    };
    template<typename Value = long double>
    using Q_F = units::Quantity<Value, F>;
    namespace literals
    {
        static inline Q_F<long double> operator "" _F_ (long double _v) {
            return Q_F<long double>(_v); }
        static inline Q_F<long double> operator "" _F_ (unsigned long long int _v) {
            return Q_F<long double>(_v); }
    }



//
// Unit "F_abs"
//
    struct F_abs
    {
        using factor_t = std::ratio<5, 9>; // 0.555555
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = F;
        static constexpr bool absolute = true;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "F_abs";
        }
    };
    template<typename Value = long double>
    using Q_F_abs = units::Quantity<Value, F_abs>;
    namespace literals
    {
        static inline Q_F_abs<long double> operator "" _F_abs_ (long double _v) {
            return Q_F_abs<long double>(_v); }
        static inline Q_F_abs<long double> operator "" _F_abs_ (unsigned long long int _v) {
            return Q_F_abs<long double>(_v); }
    }



//
// Unit "dF"
//
    struct dF
    {
        using factor_t = std::ratio<1, 18>; // 0.0555556
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = dF;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "dF";
        }
    };
    template<typename Value = long double>
    using Q_dF = units::Quantity<Value, dF>;
    namespace literals
    {
        static inline Q_dF<long double> operator "" _dF_ (long double _v) {
            return Q_dF<long double>(_v); }
        static inline Q_dF<long double> operator "" _dF_ (unsigned long long int _v) {
            return Q_dF<long double>(_v); }
    }



//
// Unit "dF_abs"
//
    struct dF_abs
    {
        using factor_t = std::ratio<1, 18>; // 0.0555556
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = dF;
        static constexpr bool absolute = true;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "dF_abs";
        }
    };
    template<typename Value = long double>
    using Q_dF_abs = units::Quantity<Value, dF_abs>;
    namespace literals
    {
        static inline Q_dF_abs<long double> operator "" _dF_abs_ (long double _v) {
            return Q_dF_abs<long double>(_v); }
        static inline Q_dF_abs<long double> operator "" _dF_abs_ (unsigned long long int _v) {
            return Q_dF_abs<long double>(_v); }
    }



//
// Unit "cF"
//
    struct cF
    {
        using factor_t = std::ratio<1, 180>; // 0.00555556
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = cF;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "cF";
        }
    };
    template<typename Value = long double>
    using Q_cF = units::Quantity<Value, cF>;
    namespace literals
    {
        static inline Q_cF<long double> operator "" _cF_ (long double _v) {
            return Q_cF<long double>(_v); }
        static inline Q_cF<long double> operator "" _cF_ (unsigned long long int _v) {
            return Q_cF<long double>(_v); }
    }



//
// Unit "cF_abs"
//
    struct cF_abs
    {
        using factor_t = std::ratio<1, 180>; // 0.00555556
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = cF;
        static constexpr bool absolute = true;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "cF_abs";
        }
    };
    template<typename Value = long double>
    using Q_cF_abs = units::Quantity<Value, cF_abs>;
    namespace literals
    {
        static inline Q_cF_abs<long double> operator "" _cF_abs_ (long double _v) {
            return Q_cF_abs<long double>(_v); }
        static inline Q_cF_abs<long double> operator "" _cF_abs_ (unsigned long long int _v) {
            return Q_cF_abs<long double>(_v); }
    }



//
// Unit "mF"
//
    struct mF
    {
        using factor_t = std::ratio<1, 1800>; // 0.000555555
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = mF;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "mF";
        }
    };
    template<typename Value = long double>
    using Q_mF = units::Quantity<Value, mF>;
    namespace literals
    {
        static inline Q_mF<long double> operator "" _mF_ (long double _v) {
            return Q_mF<long double>(_v); }
        static inline Q_mF<long double> operator "" _mF_ (unsigned long long int _v) {
            return Q_mF<long double>(_v); }
    }



//
// Unit "mF_abs"
//
    struct mF_abs
    {
        using factor_t = std::ratio<1, 1800>; // 0.000555555
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = mF;
        static constexpr bool absolute = true;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "mF_abs";
        }
    };
    template<typename Value = long double>
    using Q_mF_abs = units::Quantity<Value, mF_abs>;
    namespace literals
    {
        static inline Q_mF_abs<long double> operator "" _mF_abs_ (long double _v) {
            return Q_mF_abs<long double>(_v); }
        static inline Q_mF_abs<long double> operator "" _mF_abs_ (unsigned long long int _v) {
            return Q_mF_abs<long double>(_v); }
    }



//
// Unit "uF"
//
    struct uF
    {
        using factor_t = std::ratio<5, 9000001>; // 5.55555e-07
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = uF;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "uF";
        }
    };
    template<typename Value = long double>
    using Q_uF = units::Quantity<Value, uF>;
    namespace literals
    {
        static inline Q_uF<long double> operator "" _uF_ (long double _v) {
            return Q_uF<long double>(_v); }
        static inline Q_uF<long double> operator "" _uF_ (unsigned long long int _v) {
            return Q_uF<long double>(_v); }
    }



//
// Unit "uF_abs"
//
    struct uF_abs
    {
        using factor_t = std::ratio<5, 9000001>; // 5.55555e-07
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = uF;
        static constexpr bool absolute = true;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "uF_abs";
        }
    };
    template<typename Value = long double>
    using Q_uF_abs = units::Quantity<Value, uF_abs>;
    namespace literals
    {
        static inline Q_uF_abs<long double> operator "" _uF_abs_ (long double _v) {
            return Q_uF_abs<long double>(_v); }
        static inline Q_uF_abs<long double> operator "" _uF_abs_ (unsigned long long int _v) {
            return Q_uF_abs<long double>(_v); }
    }



//
// Unit "ER"
//
    struct ER
    {
        using factor_t = std::ratio<555555500000000000, 1>; // 5.55556e+17
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = ER;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "ER";
        }
    };
    template<typename Value = long double>
    using Q_ER = units::Quantity<Value, ER>;
    namespace literals
    {
        static inline Q_ER<long double> operator "" _ER_ (long double _v) {
            return Q_ER<long double>(_v); }
        static inline Q_ER<long double> operator "" _ER_ (unsigned long long int _v) {
            return Q_ER<long double>(_v); }
    }



//
// Unit "ER_abs"
//
    struct ER_abs
    {
        using factor_t = std::ratio<555555500000000000, 1>; // 5.55556e+17
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = ER;
        static constexpr bool absolute = true;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "ER_abs";
        }
    };
    template<typename Value = long double>
    using Q_ER_abs = units::Quantity<Value, ER_abs>;
    namespace literals
    {
        static inline Q_ER_abs<long double> operator "" _ER_abs_ (long double _v) {
            return Q_ER_abs<long double>(_v); }
        static inline Q_ER_abs<long double> operator "" _ER_abs_ (unsigned long long int _v) {
            return Q_ER_abs<long double>(_v); }
    }



//
// Unit "PR"
//
    struct PR
    {
        using factor_t = std::ratio<555555500000000, 1>; // 5.55556e+14
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = PR;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "PR";
        }
    };
    template<typename Value = long double>
    using Q_PR = units::Quantity<Value, PR>;
    namespace literals
    {
        static inline Q_PR<long double> operator "" _PR_ (long double _v) {
            return Q_PR<long double>(_v); }
        static inline Q_PR<long double> operator "" _PR_ (unsigned long long int _v) {
            return Q_PR<long double>(_v); }
    }



//
// Unit "PR_abs"
//
    struct PR_abs
    {
        using factor_t = std::ratio<555555500000000, 1>; // 5.55556e+14
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = PR;
        static constexpr bool absolute = true;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "PR_abs";
        }
    };
    template<typename Value = long double>
    using Q_PR_abs = units::Quantity<Value, PR_abs>;
    namespace literals
    {
        static inline Q_PR_abs<long double> operator "" _PR_abs_ (long double _v) {
            return Q_PR_abs<long double>(_v); }
        static inline Q_PR_abs<long double> operator "" _PR_abs_ (unsigned long long int _v) {
            return Q_PR_abs<long double>(_v); }
    }



//
// Unit "TR"
//
    struct TR
    {
        using factor_t = std::ratio<555555500000, 1>; // 5.55556e+11
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = TR;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "TR";
        }
    };
    template<typename Value = long double>
    using Q_TR = units::Quantity<Value, TR>;
    namespace literals
    {
        static inline Q_TR<long double> operator "" _TR_ (long double _v) {
            return Q_TR<long double>(_v); }
        static inline Q_TR<long double> operator "" _TR_ (unsigned long long int _v) {
            return Q_TR<long double>(_v); }
    }



//
// Unit "TR_abs"
//
    struct TR_abs
    {
        using factor_t = std::ratio<555555500000, 1>; // 5.55556e+11
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = TR;
        static constexpr bool absolute = true;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "TR_abs";
        }
    };
    template<typename Value = long double>
    using Q_TR_abs = units::Quantity<Value, TR_abs>;
    namespace literals
    {
        static inline Q_TR_abs<long double> operator "" _TR_abs_ (long double _v) {
            return Q_TR_abs<long double>(_v); }
        static inline Q_TR_abs<long double> operator "" _TR_abs_ (unsigned long long int _v) {
            return Q_TR_abs<long double>(_v); }
    }



//
// Unit "GR"
//
    struct GR
    {
        using factor_t = std::ratio<555555500, 1>; // 5.55556e+08
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = GR;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "GR";
        }
    };
    template<typename Value = long double>
    using Q_GR = units::Quantity<Value, GR>;
    namespace literals
    {
        static inline Q_GR<long double> operator "" _GR_ (long double _v) {
            return Q_GR<long double>(_v); }
        static inline Q_GR<long double> operator "" _GR_ (unsigned long long int _v) {
            return Q_GR<long double>(_v); }
    }



//
// Unit "GR_abs"
//
    struct GR_abs
    {
        using factor_t = std::ratio<555555500, 1>; // 5.55556e+08
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = GR;
        static constexpr bool absolute = true;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "GR_abs";
        }
    };
    template<typename Value = long double>
    using Q_GR_abs = units::Quantity<Value, GR_abs>;
    namespace literals
    {
        static inline Q_GR_abs<long double> operator "" _GR_abs_ (long double _v) {
            return Q_GR_abs<long double>(_v); }
        static inline Q_GR_abs<long double> operator "" _GR_abs_ (unsigned long long int _v) {
            return Q_GR_abs<long double>(_v); }
    }



//
// Unit "MR"
//
    struct MR
    {
        using factor_t = std::ratio<1111111, 2>; // 555556
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = MR;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "MR";
        }
    };
    template<typename Value = long double>
    using Q_MR = units::Quantity<Value, MR>;
    namespace literals
    {
        static inline Q_MR<long double> operator "" _MR_ (long double _v) {
            return Q_MR<long double>(_v); }
        static inline Q_MR<long double> operator "" _MR_ (unsigned long long int _v) {
            return Q_MR<long double>(_v); }
    }



//
// Unit "MR_abs"
//
    struct MR_abs
    {
        using factor_t = std::ratio<1111111, 2>; // 555556
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = MR;
        static constexpr bool absolute = true;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "MR_abs";
        }
    };
    template<typename Value = long double>
    using Q_MR_abs = units::Quantity<Value, MR_abs>;
    namespace literals
    {
        static inline Q_MR_abs<long double> operator "" _MR_abs_ (long double _v) {
            return Q_MR_abs<long double>(_v); }
        static inline Q_MR_abs<long double> operator "" _MR_abs_ (unsigned long long int _v) {
            return Q_MR_abs<long double>(_v); }
    }



//
// Unit "kR"
//
    struct kR
    {
        using factor_t = std::ratio<1111111, 2000>; // 555.555
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = kR;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "kR";
        }
    };
    template<typename Value = long double>
    using Q_kR = units::Quantity<Value, kR>;
    namespace literals
    {
        static inline Q_kR<long double> operator "" _kR_ (long double _v) {
            return Q_kR<long double>(_v); }
        static inline Q_kR<long double> operator "" _kR_ (unsigned long long int _v) {
            return Q_kR<long double>(_v); }
    }



//
// Unit "kR_abs"
//
    struct kR_abs
    {
        using factor_t = std::ratio<1111111, 2000>; // 555.555
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = kR;
        static constexpr bool absolute = true;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "kR_abs";
        }
    };
    template<typename Value = long double>
    using Q_kR_abs = units::Quantity<Value, kR_abs>;
    namespace literals
    {
        static inline Q_kR_abs<long double> operator "" _kR_abs_ (long double _v) {
            return Q_kR_abs<long double>(_v); }
        static inline Q_kR_abs<long double> operator "" _kR_abs_ (unsigned long long int _v) {
            return Q_kR_abs<long double>(_v); }
    }



//
// Unit "hR"
//
    struct hR
    {
        using factor_t = std::ratio<1111111, 20000>; // 55.5555
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = hR;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "hR";
        }
    };
    template<typename Value = long double>
    using Q_hR = units::Quantity<Value, hR>;
    namespace literals
    {
        static inline Q_hR<long double> operator "" _hR_ (long double _v) {
            return Q_hR<long double>(_v); }
        static inline Q_hR<long double> operator "" _hR_ (unsigned long long int _v) {
            return Q_hR<long double>(_v); }
    }



//
// Unit "hR_abs"
//
    struct hR_abs
    {
        using factor_t = std::ratio<1111111, 20000>; // 55.5555
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = hR;
        static constexpr bool absolute = true;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "hR_abs";
        }
    };
    template<typename Value = long double>
    using Q_hR_abs = units::Quantity<Value, hR_abs>;
    namespace literals
    {
        static inline Q_hR_abs<long double> operator "" _hR_abs_ (long double _v) {
            return Q_hR_abs<long double>(_v); }
        static inline Q_hR_abs<long double> operator "" _hR_abs_ (unsigned long long int _v) {
            return Q_hR_abs<long double>(_v); }
    }



//
// Unit "daR"
//
    struct daR
    {
        using factor_t = std::ratio<1111111, 200000>; // 5.55556
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = daR;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "daR";
        }
    };
    template<typename Value = long double>
    using Q_daR = units::Quantity<Value, daR>;
    namespace literals
    {
        static inline Q_daR<long double> operator "" _daR_ (long double _v) {
            return Q_daR<long double>(_v); }
        static inline Q_daR<long double> operator "" _daR_ (unsigned long long int _v) {
            return Q_daR<long double>(_v); }
    }



//
// Unit "daR_abs"
//
    struct daR_abs
    {
        using factor_t = std::ratio<1111111, 200000>; // 5.55556
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = daR;
        static constexpr bool absolute = true;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "daR_abs";
        }
    };
    template<typename Value = long double>
    using Q_daR_abs = units::Quantity<Value, daR_abs>;
    namespace literals
    {
        static inline Q_daR_abs<long double> operator "" _daR_abs_ (long double _v) {
            return Q_daR_abs<long double>(_v); }
        static inline Q_daR_abs<long double> operator "" _daR_abs_ (unsigned long long int _v) {
            return Q_daR_abs<long double>(_v); }
    }



//
// Unit "R"
//
    struct R
    {
        using factor_t = std::ratio<5, 9>; // 0.555555
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = R;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "R";
        }
    };
    template<typename Value = long double>
    using Q_R = units::Quantity<Value, R>;
    namespace literals
    {
        static inline Q_R<long double> operator "" _R_ (long double _v) {
            return Q_R<long double>(_v); }
        static inline Q_R<long double> operator "" _R_ (unsigned long long int _v) {
            return Q_R<long double>(_v); }
    }



//
// Unit "R_abs"
//
    struct R_abs
    {
        using factor_t = std::ratio<5, 9>; // 0.555555
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = R;
        static constexpr bool absolute = true;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "R_abs";
        }
    };
    template<typename Value = long double>
    using Q_R_abs = units::Quantity<Value, R_abs>;
    namespace literals
    {
        static inline Q_R_abs<long double> operator "" _R_abs_ (long double _v) {
            return Q_R_abs<long double>(_v); }
        static inline Q_R_abs<long double> operator "" _R_abs_ (unsigned long long int _v) {
            return Q_R_abs<long double>(_v); }
    }



//
// Unit "dR"
//
    struct dR
    {
        using factor_t = std::ratio<1, 18>; // 0.0555556
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = dR;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "dR";
        }
    };
    template<typename Value = long double>
    using Q_dR = units::Quantity<Value, dR>;
    namespace literals
    {
        static inline Q_dR<long double> operator "" _dR_ (long double _v) {
            return Q_dR<long double>(_v); }
        static inline Q_dR<long double> operator "" _dR_ (unsigned long long int _v) {
            return Q_dR<long double>(_v); }
    }



//
// Unit "dR_abs"
//
    struct dR_abs
    {
        using factor_t = std::ratio<1, 18>; // 0.0555556
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = dR;
        static constexpr bool absolute = true;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "dR_abs";
        }
    };
    template<typename Value = long double>
    using Q_dR_abs = units::Quantity<Value, dR_abs>;
    namespace literals
    {
        static inline Q_dR_abs<long double> operator "" _dR_abs_ (long double _v) {
            return Q_dR_abs<long double>(_v); }
        static inline Q_dR_abs<long double> operator "" _dR_abs_ (unsigned long long int _v) {
            return Q_dR_abs<long double>(_v); }
    }



//
// Unit "cR"
//
    struct cR
    {
        using factor_t = std::ratio<1, 180>; // 0.00555556
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = cR;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "cR";
        }
    };
    template<typename Value = long double>
    using Q_cR = units::Quantity<Value, cR>;
    namespace literals
    {
        static inline Q_cR<long double> operator "" _cR_ (long double _v) {
            return Q_cR<long double>(_v); }
        static inline Q_cR<long double> operator "" _cR_ (unsigned long long int _v) {
            return Q_cR<long double>(_v); }
    }



//
// Unit "cR_abs"
//
    struct cR_abs
    {
        using factor_t = std::ratio<1, 180>; // 0.00555556
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = cR;
        static constexpr bool absolute = true;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "cR_abs";
        }
    };
    template<typename Value = long double>
    using Q_cR_abs = units::Quantity<Value, cR_abs>;
    namespace literals
    {
        static inline Q_cR_abs<long double> operator "" _cR_abs_ (long double _v) {
            return Q_cR_abs<long double>(_v); }
        static inline Q_cR_abs<long double> operator "" _cR_abs_ (unsigned long long int _v) {
            return Q_cR_abs<long double>(_v); }
    }



//
// Unit "mR"
//
    struct mR
    {
        using factor_t = std::ratio<1, 1800>; // 0.000555555
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = mR;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "mR";
        }
    };
    template<typename Value = long double>
    using Q_mR = units::Quantity<Value, mR>;
    namespace literals
    {
        static inline Q_mR<long double> operator "" _mR_ (long double _v) {
            return Q_mR<long double>(_v); }
        static inline Q_mR<long double> operator "" _mR_ (unsigned long long int _v) {
            return Q_mR<long double>(_v); }
    }



//
// Unit "mR_abs"
//
    struct mR_abs
    {
        using factor_t = std::ratio<1, 1800>; // 0.000555555
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = mR;
        static constexpr bool absolute = true;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "mR_abs";
        }
    };
    template<typename Value = long double>
    using Q_mR_abs = units::Quantity<Value, mR_abs>;
    namespace literals
    {
        static inline Q_mR_abs<long double> operator "" _mR_abs_ (long double _v) {
            return Q_mR_abs<long double>(_v); }
        static inline Q_mR_abs<long double> operator "" _mR_abs_ (unsigned long long int _v) {
            return Q_mR_abs<long double>(_v); }
    }



//
// Unit "uR"
//
    struct uR
    {
        using factor_t = std::ratio<5, 9000001>; // 5.55555e-07
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = uR;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "uR";
        }
    };
    template<typename Value = long double>
    using Q_uR = units::Quantity<Value, uR>;
    namespace literals
    {
        static inline Q_uR<long double> operator "" _uR_ (long double _v) {
            return Q_uR<long double>(_v); }
        static inline Q_uR<long double> operator "" _uR_ (unsigned long long int _v) {
            return Q_uR<long double>(_v); }
    }



//
// Unit "uR_abs"
//
    struct uR_abs
    {
        using factor_t = std::ratio<5, 9000001>; // 5.55555e-07
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = uR;
        static constexpr bool absolute = true;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "uR_abs";
        }
    };
    template<typename Value = long double>
    using Q_uR_abs = units::Quantity<Value, uR_abs>;
    namespace literals
    {
        static inline Q_uR_abs<long double> operator "" _uR_abs_ (long double _v) {
            return Q_uR_abs<long double>(_v); }
        static inline Q_uR_abs<long double> operator "" _uR_abs_ (unsigned long long int _v) {
            return Q_uR_abs<long double>(_v); }
    }



//
// Unit "ET"
//
    struct ET
    {
        using factor_t = std::ratio<1000000000000000000, 1>; // 1e+18
        using dimensions_t = dimensions::MagneticFlux;
        using offset_t = std::ratio<0, 1>;
        using relative_t = ET;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "ET";
        }
    };
    template<typename Value = long double>
    using Q_ET = units::Quantity<Value, ET>;
    namespace literals
    {
        static inline Q_ET<long double> operator "" _ET_ (long double _v) {
            return Q_ET<long double>(_v); }
        static inline Q_ET<long double> operator "" _ET_ (unsigned long long int _v) {
            return Q_ET<long double>(_v); }
    }



//
// Unit "PT"
//
    struct PT
    {
        using factor_t = std::ratio<1000000000000000, 1>; // 1e+15
        using dimensions_t = dimensions::MagneticFlux;
        using offset_t = std::ratio<0, 1>;
        using relative_t = PT;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "PT";
        }
    };
    template<typename Value = long double>
    using Q_PT = units::Quantity<Value, PT>;
    namespace literals
    {
        static inline Q_PT<long double> operator "" _PT_ (long double _v) {
            return Q_PT<long double>(_v); }
        static inline Q_PT<long double> operator "" _PT_ (unsigned long long int _v) {
            return Q_PT<long double>(_v); }
    }



//
// Unit "TT"
//
    struct TT
    {
        using factor_t = std::ratio<1000000000000, 1>; // 1e+12
        using dimensions_t = dimensions::MagneticFlux;
        using offset_t = std::ratio<0, 1>;
        using relative_t = TT;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "TT";
        }
    };
    template<typename Value = long double>
    using Q_TT = units::Quantity<Value, TT>;
    namespace literals
    {
        static inline Q_TT<long double> operator "" _TT_ (long double _v) {
            return Q_TT<long double>(_v); }
        static inline Q_TT<long double> operator "" _TT_ (unsigned long long int _v) {
            return Q_TT<long double>(_v); }
    }



//
// Unit "GT"
//
    struct GT
    {
        using factor_t = std::ratio<1000000000, 1>; // 1e+09
        using dimensions_t = dimensions::MagneticFlux;
        using offset_t = std::ratio<0, 1>;
        using relative_t = GT;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "GT";
        }
    };
    template<typename Value = long double>
    using Q_GT = units::Quantity<Value, GT>;
    namespace literals
    {
        static inline Q_GT<long double> operator "" _GT_ (long double _v) {
            return Q_GT<long double>(_v); }
        static inline Q_GT<long double> operator "" _GT_ (unsigned long long int _v) {
            return Q_GT<long double>(_v); }
    }



//
// Unit "MT"
//
    struct MT
    {
        using factor_t = std::ratio<1000000, 1>; // 1e+06
        using dimensions_t = dimensions::MagneticFlux;
        using offset_t = std::ratio<0, 1>;
        using relative_t = MT;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "MT";
        }
    };
    template<typename Value = long double>
    using Q_MT = units::Quantity<Value, MT>;
    namespace literals
    {
        static inline Q_MT<long double> operator "" _MT_ (long double _v) {
            return Q_MT<long double>(_v); }
        static inline Q_MT<long double> operator "" _MT_ (unsigned long long int _v) {
            return Q_MT<long double>(_v); }
    }



//
// Unit "kT"
//
    struct kT
    {
        using factor_t = std::ratio<1000, 1>; // 1000
        using dimensions_t = dimensions::MagneticFlux;
        using offset_t = std::ratio<0, 1>;
        using relative_t = kT;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "kT";
        }
    };
    template<typename Value = long double>
    using Q_kT = units::Quantity<Value, kT>;
    namespace literals
    {
        static inline Q_kT<long double> operator "" _kT_ (long double _v) {
            return Q_kT<long double>(_v); }
        static inline Q_kT<long double> operator "" _kT_ (unsigned long long int _v) {
            return Q_kT<long double>(_v); }
    }



//
// Unit "hT"
//
    struct hT
    {
        using factor_t = std::ratio<100, 1>; // 100
        using dimensions_t = dimensions::MagneticFlux;
        using offset_t = std::ratio<0, 1>;
        using relative_t = hT;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "hT";
        }
    };
    template<typename Value = long double>
    using Q_hT = units::Quantity<Value, hT>;
    namespace literals
    {
        static inline Q_hT<long double> operator "" _hT_ (long double _v) {
            return Q_hT<long double>(_v); }
        static inline Q_hT<long double> operator "" _hT_ (unsigned long long int _v) {
            return Q_hT<long double>(_v); }
    }



//
// Unit "daT"
//
    struct daT
    {
        using factor_t = std::ratio<10, 1>; // 10
        using dimensions_t = dimensions::MagneticFlux;
        using offset_t = std::ratio<0, 1>;
        using relative_t = daT;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "daT";
        }
    };
    template<typename Value = long double>
    using Q_daT = units::Quantity<Value, daT>;
    namespace literals
    {
        static inline Q_daT<long double> operator "" _daT_ (long double _v) {
            return Q_daT<long double>(_v); }
        static inline Q_daT<long double> operator "" _daT_ (unsigned long long int _v) {
            return Q_daT<long double>(_v); }
    }



//
// Unit "T"
//
    struct T
    {
        using factor_t = std::ratio<1, 1>; // 1
        using dimensions_t = dimensions::MagneticFlux;
        using offset_t = std::ratio<0, 1>;
        using relative_t = T;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "T";
        }
    };
    template<typename Value = long double>
    using Q_T = units::Quantity<Value, T>;
    namespace literals
    {
        static inline Q_T<long double> operator "" _T_ (long double _v) {
            return Q_T<long double>(_v); }
        static inline Q_T<long double> operator "" _T_ (unsigned long long int _v) {
            return Q_T<long double>(_v); }
    }



//
// Unit "dT"
//
    struct dT
    {
        using factor_t = std::ratio<1, 10>; // 0.1
        using dimensions_t = dimensions::MagneticFlux;
        using offset_t = std::ratio<0, 1>;
        using relative_t = dT;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "dT";
        }
    };
    template<typename Value = long double>
    using Q_dT = units::Quantity<Value, dT>;
    namespace literals
    {
        static inline Q_dT<long double> operator "" _dT_ (long double _v) {
            return Q_dT<long double>(_v); }
        static inline Q_dT<long double> operator "" _dT_ (unsigned long long int _v) {
            return Q_dT<long double>(_v); }
    }



//
// Unit "cT"
//
    struct cT
    {
        using factor_t = std::ratio<1, 100>; // 0.01
        using dimensions_t = dimensions::MagneticFlux;
        using offset_t = std::ratio<0, 1>;
        using relative_t = cT;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "cT";
        }
    };
    template<typename Value = long double>
    using Q_cT = units::Quantity<Value, cT>;
    namespace literals
    {
        static inline Q_cT<long double> operator "" _cT_ (long double _v) {
            return Q_cT<long double>(_v); }
        static inline Q_cT<long double> operator "" _cT_ (unsigned long long int _v) {
            return Q_cT<long double>(_v); }
    }



//
// Unit "mT"
//
    struct mT
    {
        using factor_t = std::ratio<1, 1000>; // 0.001
        using dimensions_t = dimensions::MagneticFlux;
        using offset_t = std::ratio<0, 1>;
        using relative_t = mT;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "mT";
        }
    };
    template<typename Value = long double>
    using Q_mT = units::Quantity<Value, mT>;
    namespace literals
    {
        static inline Q_mT<long double> operator "" _mT_ (long double _v) {
            return Q_mT<long double>(_v); }
        static inline Q_mT<long double> operator "" _mT_ (unsigned long long int _v) {
            return Q_mT<long double>(_v); }
    }



//
// Unit "EG"
//
    struct EG
    {
        using factor_t = std::ratio<100000000000000, 1>; // 1e+14
        using dimensions_t = dimensions::MagneticFlux;
        using offset_t = std::ratio<0, 1>;
        using relative_t = EG;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "EG";
        }
    };
    template<typename Value = long double>
    using Q_EG = units::Quantity<Value, EG>;
    namespace literals
    {
        static inline Q_EG<long double> operator "" _EG_ (long double _v) {
            return Q_EG<long double>(_v); }
        static inline Q_EG<long double> operator "" _EG_ (unsigned long long int _v) {
            return Q_EG<long double>(_v); }
    }



//
// Unit "PG"
//
    struct PG
    {
        using factor_t = std::ratio<100000000000, 1>; // 1e+11
        using dimensions_t = dimensions::MagneticFlux;
        using offset_t = std::ratio<0, 1>;
        using relative_t = PG;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "PG";
        }
    };
    template<typename Value = long double>
    using Q_PG = units::Quantity<Value, PG>;
    namespace literals
    {
        static inline Q_PG<long double> operator "" _PG_ (long double _v) {
            return Q_PG<long double>(_v); }
        static inline Q_PG<long double> operator "" _PG_ (unsigned long long int _v) {
            return Q_PG<long double>(_v); }
    }



//
// Unit "TG"
//
    struct TG
    {
        using factor_t = std::ratio<100000000, 1>; // 1e+08
        using dimensions_t = dimensions::MagneticFlux;
        using offset_t = std::ratio<0, 1>;
        using relative_t = TG;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "TG";
        }
    };
    template<typename Value = long double>
    using Q_TG = units::Quantity<Value, TG>;
    namespace literals
    {
        static inline Q_TG<long double> operator "" _TG_ (long double _v) {
            return Q_TG<long double>(_v); }
        static inline Q_TG<long double> operator "" _TG_ (unsigned long long int _v) {
            return Q_TG<long double>(_v); }
    }



//
// Unit "GG"
//
    struct GG
    {
        using factor_t = std::ratio<100000, 1>; // 100000
        using dimensions_t = dimensions::MagneticFlux;
        using offset_t = std::ratio<0, 1>;
        using relative_t = GG;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "GG";
        }
    };
    template<typename Value = long double>
    using Q_GG = units::Quantity<Value, GG>;
    namespace literals
    {
        static inline Q_GG<long double> operator "" _GG_ (long double _v) {
            return Q_GG<long double>(_v); }
        static inline Q_GG<long double> operator "" _GG_ (unsigned long long int _v) {
            return Q_GG<long double>(_v); }
    }



//
// Unit "MG"
//
    struct MG
    {
        using factor_t = std::ratio<100, 1>; // 100
        using dimensions_t = dimensions::MagneticFlux;
        using offset_t = std::ratio<0, 1>;
        using relative_t = MG;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "MG";
        }
    };
    template<typename Value = long double>
    using Q_MG = units::Quantity<Value, MG>;
    namespace literals
    {
        static inline Q_MG<long double> operator "" _MG_ (long double _v) {
            return Q_MG<long double>(_v); }
        static inline Q_MG<long double> operator "" _MG_ (unsigned long long int _v) {
            return Q_MG<long double>(_v); }
    }



//
// Unit "kG"
//
    struct kG
    {
        using factor_t = std::ratio<1, 10>; // 0.1
        using dimensions_t = dimensions::MagneticFlux;
        using offset_t = std::ratio<0, 1>;
        using relative_t = kG;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "kG";
        }
    };
    template<typename Value = long double>
    using Q_kG = units::Quantity<Value, kG>;
    namespace literals
    {
        static inline Q_kG<long double> operator "" _kG_ (long double _v) {
            return Q_kG<long double>(_v); }
        static inline Q_kG<long double> operator "" _kG_ (unsigned long long int _v) {
            return Q_kG<long double>(_v); }
    }



//
// Unit "hG"
//
    struct hG
    {
        using factor_t = std::ratio<1, 100>; // 0.01
        using dimensions_t = dimensions::MagneticFlux;
        using offset_t = std::ratio<0, 1>;
        using relative_t = hG;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "hG";
        }
    };
    template<typename Value = long double>
    using Q_hG = units::Quantity<Value, hG>;
    namespace literals
    {
        static inline Q_hG<long double> operator "" _hG_ (long double _v) {
            return Q_hG<long double>(_v); }
        static inline Q_hG<long double> operator "" _hG_ (unsigned long long int _v) {
            return Q_hG<long double>(_v); }
    }



//
// Unit "daG"
//
    struct daG
    {
        using factor_t = std::ratio<1, 1000>; // 0.001
        using dimensions_t = dimensions::MagneticFlux;
        using offset_t = std::ratio<0, 1>;
        using relative_t = daG;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "daG";
        }
    };
    template<typename Value = long double>
    using Q_daG = units::Quantity<Value, daG>;
    namespace literals
    {
        static inline Q_daG<long double> operator "" _daG_ (long double _v) {
            return Q_daG<long double>(_v); }
        static inline Q_daG<long double> operator "" _daG_ (unsigned long long int _v) {
            return Q_daG<long double>(_v); }
    }



//
// Unit "G"
//
    struct G
    {
        using factor_t = std::ratio<1, 10000>; // 0.0001
        using dimensions_t = dimensions::MagneticFlux;
        using offset_t = std::ratio<0, 1>;
        using relative_t = G;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "G";
        }
    };
    template<typename Value = long double>
    using Q_G = units::Quantity<Value, G>;
    namespace literals
    {
        static inline Q_G<long double> operator "" _G_ (long double _v) {
            return Q_G<long double>(_v); }
        static inline Q_G<long double> operator "" _G_ (unsigned long long int _v) {
            return Q_G<long double>(_v); }
    }



//
// Unit "dG"
//
    struct dG
    {
        using factor_t = std::ratio<1, 100000>; // 1e-05
        using dimensions_t = dimensions::MagneticFlux;
        using offset_t = std::ratio<0, 1>;
        using relative_t = dG;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "dG";
        }
    };
    template<typename Value = long double>
    using Q_dG = units::Quantity<Value, dG>;
    namespace literals
    {
        static inline Q_dG<long double> operator "" _dG_ (long double _v) {
            return Q_dG<long double>(_v); }
        static inline Q_dG<long double> operator "" _dG_ (unsigned long long int _v) {
            return Q_dG<long double>(_v); }
    }



//
// Unit "cG"
//
    struct cG
    {
        using factor_t = std::ratio<1, 1000000>; // 1e-06
        using dimensions_t = dimensions::MagneticFlux;
        using offset_t = std::ratio<0, 1>;
        using relative_t = cG;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "cG";
        }
    };
    template<typename Value = long double>
    using Q_cG = units::Quantity<Value, cG>;
    namespace literals
    {
        static inline Q_cG<long double> operator "" _cG_ (long double _v) {
            return Q_cG<long double>(_v); }
        static inline Q_cG<long double> operator "" _cG_ (unsigned long long int _v) {
            return Q_cG<long double>(_v); }
    }



//
// Unit "EPa"
//
    struct EPa
    {
        using factor_t = std::ratio<1000000000000000000, 1>; // 1e+18
        using dimensions_t = dimensions::Pressure;
        using offset_t = std::ratio<0, 1>;
        using relative_t = EPa;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "EPa";
        }
    };
    template<typename Value = long double>
    using Q_EPa = units::Quantity<Value, EPa>;
    namespace literals
    {
        static inline Q_EPa<long double> operator "" _EPa_ (long double _v) {
            return Q_EPa<long double>(_v); }
        static inline Q_EPa<long double> operator "" _EPa_ (unsigned long long int _v) {
            return Q_EPa<long double>(_v); }
    }



//
// Unit "PPa"
//
    struct PPa
    {
        using factor_t = std::ratio<1000000000000000, 1>; // 1e+15
        using dimensions_t = dimensions::Pressure;
        using offset_t = std::ratio<0, 1>;
        using relative_t = PPa;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "PPa";
        }
    };
    template<typename Value = long double>
    using Q_PPa = units::Quantity<Value, PPa>;
    namespace literals
    {
        static inline Q_PPa<long double> operator "" _PPa_ (long double _v) {
            return Q_PPa<long double>(_v); }
        static inline Q_PPa<long double> operator "" _PPa_ (unsigned long long int _v) {
            return Q_PPa<long double>(_v); }
    }



//
// Unit "TPa"
//
    struct TPa
    {
        using factor_t = std::ratio<1000000000000, 1>; // 1e+12
        using dimensions_t = dimensions::Pressure;
        using offset_t = std::ratio<0, 1>;
        using relative_t = TPa;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "TPa";
        }
    };
    template<typename Value = long double>
    using Q_TPa = units::Quantity<Value, TPa>;
    namespace literals
    {
        static inline Q_TPa<long double> operator "" _TPa_ (long double _v) {
            return Q_TPa<long double>(_v); }
        static inline Q_TPa<long double> operator "" _TPa_ (unsigned long long int _v) {
            return Q_TPa<long double>(_v); }
    }



//
// Unit "GPa"
//
    struct GPa
    {
        using factor_t = std::ratio<1000000000, 1>; // 1e+09
        using dimensions_t = dimensions::Pressure;
        using offset_t = std::ratio<0, 1>;
        using relative_t = GPa;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "GPa";
        }
    };
    template<typename Value = long double>
    using Q_GPa = units::Quantity<Value, GPa>;
    namespace literals
    {
        static inline Q_GPa<long double> operator "" _GPa_ (long double _v) {
            return Q_GPa<long double>(_v); }
        static inline Q_GPa<long double> operator "" _GPa_ (unsigned long long int _v) {
            return Q_GPa<long double>(_v); }
    }



//
// Unit "MPa"
//
    struct MPa
    {
        using factor_t = std::ratio<1000000, 1>; // 1e+06
        using dimensions_t = dimensions::Pressure;
        using offset_t = std::ratio<0, 1>;
        using relative_t = MPa;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "MPa";
        }
    };
    template<typename Value = long double>
    using Q_MPa = units::Quantity<Value, MPa>;
    namespace literals
    {
        static inline Q_MPa<long double> operator "" _MPa_ (long double _v) {
            return Q_MPa<long double>(_v); }
        static inline Q_MPa<long double> operator "" _MPa_ (unsigned long long int _v) {
            return Q_MPa<long double>(_v); }
    }



//
// Unit "kPa"
//
    struct kPa
    {
        using factor_t = std::ratio<1000, 1>; // 1000
        using dimensions_t = dimensions::Pressure;
        using offset_t = std::ratio<0, 1>;
        using relative_t = kPa;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "kPa";
        }
    };
    template<typename Value = long double>
    using Q_kPa = units::Quantity<Value, kPa>;
    namespace literals
    {
        static inline Q_kPa<long double> operator "" _kPa_ (long double _v) {
            return Q_kPa<long double>(_v); }
        static inline Q_kPa<long double> operator "" _kPa_ (unsigned long long int _v) {
            return Q_kPa<long double>(_v); }
    }



//
// Unit "hPa"
//
    struct hPa
    {
        using factor_t = std::ratio<100, 1>; // 100
        using dimensions_t = dimensions::Pressure;
        using offset_t = std::ratio<0, 1>;
        using relative_t = hPa;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "hPa";
        }
    };
    template<typename Value = long double>
    using Q_hPa = units::Quantity<Value, hPa>;
    namespace literals
    {
        static inline Q_hPa<long double> operator "" _hPa_ (long double _v) {
            return Q_hPa<long double>(_v); }
        static inline Q_hPa<long double> operator "" _hPa_ (unsigned long long int _v) {
            return Q_hPa<long double>(_v); }
    }



//
// Unit "daPa"
//
    struct daPa
    {
        using factor_t = std::ratio<10, 1>; // 10
        using dimensions_t = dimensions::Pressure;
        using offset_t = std::ratio<0, 1>;
        using relative_t = daPa;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "daPa";
        }
    };
    template<typename Value = long double>
    using Q_daPa = units::Quantity<Value, daPa>;
    namespace literals
    {
        static inline Q_daPa<long double> operator "" _daPa_ (long double _v) {
            return Q_daPa<long double>(_v); }
        static inline Q_daPa<long double> operator "" _daPa_ (unsigned long long int _v) {
            return Q_daPa<long double>(_v); }
    }



//
// Unit "Pa"
//
    struct Pa
    {
        using factor_t = std::ratio<1, 1>; // 1
        using dimensions_t = dimensions::Pressure;
        using offset_t = std::ratio<0, 1>;
        using relative_t = Pa;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "Pa";
        }
    };
    template<typename Value = long double>
    using Q_Pa = units::Quantity<Value, Pa>;
    namespace literals
    {
        static inline Q_Pa<long double> operator "" _Pa_ (long double _v) {
            return Q_Pa<long double>(_v); }
        static inline Q_Pa<long double> operator "" _Pa_ (unsigned long long int _v) {
            return Q_Pa<long double>(_v); }
    }



//
// Unit "dPa"
//
    struct dPa
    {
        using factor_t = std::ratio<1, 10>; // 0.1
        using dimensions_t = dimensions::Pressure;
        using offset_t = std::ratio<0, 1>;
        using relative_t = dPa;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "dPa";
        }
    };
    template<typename Value = long double>
    using Q_dPa = units::Quantity<Value, dPa>;
    namespace literals
    {
        static inline Q_dPa<long double> operator "" _dPa_ (long double _v) {
            return Q_dPa<long double>(_v); }
        static inline Q_dPa<long double> operator "" _dPa_ (unsigned long long int _v) {
            return Q_dPa<long double>(_v); }
    }



//
// Unit "cPa"
//
    struct cPa
    {
        using factor_t = std::ratio<1, 100>; // 0.01
        using dimensions_t = dimensions::Pressure;
        using offset_t = std::ratio<0, 1>;
        using relative_t = cPa;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "cPa";
        }
    };
    template<typename Value = long double>
    using Q_cPa = units::Quantity<Value, cPa>;
    namespace literals
    {
        static inline Q_cPa<long double> operator "" _cPa_ (long double _v) {
            return Q_cPa<long double>(_v); }
        static inline Q_cPa<long double> operator "" _cPa_ (unsigned long long int _v) {
            return Q_cPa<long double>(_v); }
    }



//
// Unit "mPa"
//
    struct mPa
    {
        using factor_t = std::ratio<1, 1000>; // 0.001
        using dimensions_t = dimensions::Pressure;
        using offset_t = std::ratio<0, 1>;
        using relative_t = mPa;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "mPa";
        }
    };
    template<typename Value = long double>
    using Q_mPa = units::Quantity<Value, mPa>;
    namespace literals
    {
        static inline Q_mPa<long double> operator "" _mPa_ (long double _v) {
            return Q_mPa<long double>(_v); }
        static inline Q_mPa<long double> operator "" _mPa_ (unsigned long long int _v) {
            return Q_mPa<long double>(_v); }
    }



//
// Unit "Tbar"
//
    struct Tbar
    {
        using factor_t = std::ratio<100000000000000000, 1>; // 1e+17
        using dimensions_t = dimensions::Pressure;
        using offset_t = std::ratio<0, 1>;
        using relative_t = Tbar;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "Tbar";
        }
    };
    template<typename Value = long double>
    using Q_Tbar = units::Quantity<Value, Tbar>;
    namespace literals
    {
        static inline Q_Tbar<long double> operator "" _Tbar_ (long double _v) {
            return Q_Tbar<long double>(_v); }
        static inline Q_Tbar<long double> operator "" _Tbar_ (unsigned long long int _v) {
            return Q_Tbar<long double>(_v); }
    }



//
// Unit "Gbar"
//
    struct Gbar
    {
        using factor_t = std::ratio<100000000000000, 1>; // 1e+14
        using dimensions_t = dimensions::Pressure;
        using offset_t = std::ratio<0, 1>;
        using relative_t = Gbar;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "Gbar";
        }
    };
    template<typename Value = long double>
    using Q_Gbar = units::Quantity<Value, Gbar>;
    namespace literals
    {
        static inline Q_Gbar<long double> operator "" _Gbar_ (long double _v) {
            return Q_Gbar<long double>(_v); }
        static inline Q_Gbar<long double> operator "" _Gbar_ (unsigned long long int _v) {
            return Q_Gbar<long double>(_v); }
    }



//
// Unit "Mbar"
//
    struct Mbar
    {
        using factor_t = std::ratio<100000000000, 1>; // 1e+11
        using dimensions_t = dimensions::Pressure;
        using offset_t = std::ratio<0, 1>;
        using relative_t = Mbar;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "Mbar";
        }
    };
    template<typename Value = long double>
    using Q_Mbar = units::Quantity<Value, Mbar>;
    namespace literals
    {
        static inline Q_Mbar<long double> operator "" _Mbar_ (long double _v) {
            return Q_Mbar<long double>(_v); }
        static inline Q_Mbar<long double> operator "" _Mbar_ (unsigned long long int _v) {
            return Q_Mbar<long double>(_v); }
    }



//
// Unit "kbar"
//
    struct kbar
    {
        using factor_t = std::ratio<100000000, 1>; // 1e+08
        using dimensions_t = dimensions::Pressure;
        using offset_t = std::ratio<0, 1>;
        using relative_t = kbar;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "kbar";
        }
    };
    template<typename Value = long double>
    using Q_kbar = units::Quantity<Value, kbar>;
    namespace literals
    {
        static inline Q_kbar<long double> operator "" _kbar_ (long double _v) {
            return Q_kbar<long double>(_v); }
        static inline Q_kbar<long double> operator "" _kbar_ (unsigned long long int _v) {
            return Q_kbar<long double>(_v); }
    }



//
// Unit "hbar"
//
    struct hbar
    {
        using factor_t = std::ratio<10000000, 1>; // 1e+07
        using dimensions_t = dimensions::Pressure;
        using offset_t = std::ratio<0, 1>;
        using relative_t = hbar;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "hbar";
        }
    };
    template<typename Value = long double>
    using Q_hbar = units::Quantity<Value, hbar>;
    namespace literals
    {
        static inline Q_hbar<long double> operator "" _hbar_ (long double _v) {
            return Q_hbar<long double>(_v); }
        static inline Q_hbar<long double> operator "" _hbar_ (unsigned long long int _v) {
            return Q_hbar<long double>(_v); }
    }



//
// Unit "dabar"
//
    struct dabar
    {
        using factor_t = std::ratio<1000000, 1>; // 1e+06
        using dimensions_t = dimensions::Pressure;
        using offset_t = std::ratio<0, 1>;
        using relative_t = dabar;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "dabar";
        }
    };
    template<typename Value = long double>
    using Q_dabar = units::Quantity<Value, dabar>;
    namespace literals
    {
        static inline Q_dabar<long double> operator "" _dabar_ (long double _v) {
            return Q_dabar<long double>(_v); }
        static inline Q_dabar<long double> operator "" _dabar_ (unsigned long long int _v) {
            return Q_dabar<long double>(_v); }
    }



//
// Unit "bar"
//
    struct bar
    {
        using factor_t = std::ratio<100000, 1>; // 100000
        using dimensions_t = dimensions::Pressure;
        using offset_t = std::ratio<0, 1>;
        using relative_t = bar;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "bar";
        }
    };
    template<typename Value = long double>
    using Q_bar = units::Quantity<Value, bar>;
    namespace literals
    {
        static inline Q_bar<long double> operator "" _bar_ (long double _v) {
            return Q_bar<long double>(_v); }
        static inline Q_bar<long double> operator "" _bar_ (unsigned long long int _v) {
            return Q_bar<long double>(_v); }
    }



//
// Unit "dbar"
//
    struct dbar
    {
        using factor_t = std::ratio<10000, 1>; // 10000
        using dimensions_t = dimensions::Pressure;
        using offset_t = std::ratio<0, 1>;
        using relative_t = dbar;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "dbar";
        }
    };
    template<typename Value = long double>
    using Q_dbar = units::Quantity<Value, dbar>;
    namespace literals
    {
        static inline Q_dbar<long double> operator "" _dbar_ (long double _v) {
            return Q_dbar<long double>(_v); }
        static inline Q_dbar<long double> operator "" _dbar_ (unsigned long long int _v) {
            return Q_dbar<long double>(_v); }
    }



//
// Unit "cbar"
//
    struct cbar
    {
        using factor_t = std::ratio<1000, 1>; // 1000
        using dimensions_t = dimensions::Pressure;
        using offset_t = std::ratio<0, 1>;
        using relative_t = cbar;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "cbar";
        }
    };
    template<typename Value = long double>
    using Q_cbar = units::Quantity<Value, cbar>;
    namespace literals
    {
        static inline Q_cbar<long double> operator "" _cbar_ (long double _v) {
            return Q_cbar<long double>(_v); }
        static inline Q_cbar<long double> operator "" _cbar_ (unsigned long long int _v) {
            return Q_cbar<long double>(_v); }
    }



//
// Unit "mbar"
//
    struct mbar
    {
        using factor_t = std::ratio<100, 1>; // 100
        using dimensions_t = dimensions::Pressure;
        using offset_t = std::ratio<0, 1>;
        using relative_t = mbar;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "mbar";
        }
    };
    template<typename Value = long double>
    using Q_mbar = units::Quantity<Value, mbar>;
    namespace literals
    {
        static inline Q_mbar<long double> operator "" _mbar_ (long double _v) {
            return Q_mbar<long double>(_v); }
        static inline Q_mbar<long double> operator "" _mbar_ (unsigned long long int _v) {
            return Q_mbar<long double>(_v); }
    }



//
// Unit "ubar"
//
    struct ubar
    {
        using factor_t = std::ratio<1, 10>; // 0.1
        using dimensions_t = dimensions::Pressure;
        using offset_t = std::ratio<0, 1>;
        using relative_t = ubar;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "ubar";
        }
    };
    template<typename Value = long double>
    using Q_ubar = units::Quantity<Value, ubar>;
    namespace literals
    {
        static inline Q_ubar<long double> operator "" _ubar_ (long double _v) {
            return Q_ubar<long double>(_v); }
        static inline Q_ubar<long double> operator "" _ubar_ (unsigned long long int _v) {
            return Q_ubar<long double>(_v); }
    }



//
// Unit "nbar"
//
    struct nbar
    {
        using factor_t = std::ratio<1, 10000>; // 0.0001
        using dimensions_t = dimensions::Pressure;
        using offset_t = std::ratio<0, 1>;
        using relative_t = nbar;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "nbar";
        }
    };
    template<typename Value = long double>
    using Q_nbar = units::Quantity<Value, nbar>;
    namespace literals
    {
        static inline Q_nbar<long double> operator "" _nbar_ (long double _v) {
            return Q_nbar<long double>(_v); }
        static inline Q_nbar<long double> operator "" _nbar_ (unsigned long long int _v) {
            return Q_nbar<long double>(_v); }
    }



//
// Unit "psi"
//
    struct psi
    {
        using factor_t = std::ratio<172369, 25>; // 6894.76
        using dimensions_t = dimensions::Pressure;
        using offset_t = std::ratio<0, 1>;
        using relative_t = psi;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "psi";
        }
    };
    template<typename Value = long double>
    using Q_psi = units::Quantity<Value, psi>;
    namespace literals
    {
        static inline Q_psi<long double> operator "" _psi_ (long double _v) {
            return Q_psi<long double>(_v); }
        static inline Q_psi<long double> operator "" _psi_ (unsigned long long int _v) {
            return Q_psi<long double>(_v); }
    }



//
// Unit "atm"
//
    struct atm
    {
        using factor_t = std::ratio<101325, 1>; // 101325
        using dimensions_t = dimensions::Pressure;
        using offset_t = std::ratio<0, 1>;
        using relative_t = atm;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "atm";
        }
    };
    template<typename Value = long double>
    using Q_atm = units::Quantity<Value, atm>;
    namespace literals
    {
        static inline Q_atm<long double> operator "" _atm_ (long double _v) {
            return Q_atm<long double>(_v); }
        static inline Q_atm<long double> operator "" _atm_ (unsigned long long int _v) {
            return Q_atm<long double>(_v); }
    }



//
// Unit "torr"
//
    struct torr
    {
        using factor_t = std::ratio<66661, 500>; // 133.322
        using dimensions_t = dimensions::Pressure;
        using offset_t = std::ratio<0, 1>;
        using relative_t = torr;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "torr";
        }
    };
    template<typename Value = long double>
    using Q_torr = units::Quantity<Value, torr>;
    namespace literals
    {
        static inline Q_torr<long double> operator "" _torr_ (long double _v) {
            return Q_torr<long double>(_v); }
        static inline Q_torr<long double> operator "" _torr_ (unsigned long long int _v) {
            return Q_torr<long double>(_v); }
    }

} /*namespace mks*/
} /*namespace units*/
} /*namespace chandra*/
#endif /*CHANDRA_MKS_UNITS_H*/
