#ifndef CHANDRA_QUANTITY_H
#define CHANDRA_QUANTITY_H

#include <initializer_list>
#include <type_traits>

#include "dimensions.h"
#include "units_utils.h"

namespace chandra
{
namespace units
{

// TODO: ADD COMPARISON OPERATORS TO THE QUANTITY CLASS, ALLOW COMPARISONS BETWEEN QUANTITIES
//  WITH DIFFERENT VALUE AND UNIT TYPES
// TODO: RELATIVE UNITS (THOSE WITHOUT A BASE) ARE FINE, BUT OPERATIONS ON ABSOLUTE UNITS ARE
//  WEIRD.  IT MAKES SENSE TO PREVENT TOO MANY OPERATIONS, AND CERTAINLY THOSE WHICH DO NOT MAKE
//  ANY PHYSICAL SENSE.
// THERE IS A LOT THAT CAN BE DONE TO IMPROVE THE ERROR PROTECTION OF THIS CLASS

template<typename Value, class Units>
class Quantity
{
    protected:
        template<class T>
        constexpr bool match_quantity(T) { return false; }

        template<typename V, typename U>
        constexpr bool match_quantity(const Quantity<V, U>&) { return true; }

    public:
        using value_t = Value;
        using units_t = Units;

        explicit Quantity() : val_{0} {}
        template<class V>
        explicit Quantity(V _val) : val_(static_cast<value_t>(_val)) {}

        template<
          typename V,
          typename U,
          typename is_convertible = typename std::enable_if<std::is_same<typename U::dimensions_t, typename Units::dimensions_t>::value, U>::type
        >
        Quantity(const Quantity<V, U>& _other){
            val_ = units::convert<Value, Units, U>(_other.value());
        }

        template<
          typename V,
          typename U,
          typename is_convertible = typename std::enable_if<std::is_same<typename U::dimensions_t, typename Units::dimensions_t>::value, U>::type
        >
        Quantity(const Quantity<V, U>&& _other){
            val_ = units::convert<Value, Units, U>(_other.value());
        }

        // Assignment
        template<
          typename V,
          typename U,
          typename is_convertible = typename std::enable_if<std::is_same<typename U::dimensions_t, typename Units::dimensions_t>::value, U>::type
        >
        constexpr auto operator = (const Quantity<V, U>& _val) {
            val_ = units::convert<Value, Units, U>(_val);
            return *this;
        }

        //
        // Comparison Operations
        //
        //  Equality
        template<
          typename V,
          typename U,
          typename is_convertible = typename std::enable_if<std::is_same<typename U::dimensions_t, typename Units::dimensions_t>::value, U>::type
        >
        constexpr bool operator == (const Quantity<V, U>& _val) const {
            return val_ == units::convert<Value, Units, U>(_val.value());
        }

        //  Inequality
        template<
          typename V,
          typename U,
          typename is_convertible = typename std::enable_if<std::is_same<typename U::dimensions_t, typename Units::dimensions_t>::value, U>::type
        >
        constexpr bool operator != (const Quantity<V, U>& _val) const {
            return val_ != units::convert<Value, Units, U>(_val.value());
        }

        //  Greater Than
        template<
          typename V,
          typename U,
          typename is_convertible = typename std::enable_if<std::is_same<typename U::dimensions_t, typename Units::dimensions_t>::value, U>::type
        >
        constexpr bool operator > (const Quantity<V, U>& _val) const {
            return val_ > units::convert<Value, Units, U>(_val.value());
        }

        //  Greater Than or Equal
        template<
          typename V,
          typename U,
          typename is_convertible = typename std::enable_if<std::is_same<typename U::dimensions_t, typename Units::dimensions_t>::value, U>::type
        >
        constexpr bool operator >= (const Quantity<V, U>& _val) const {
            return val_ >= units::convert<Value, Units, U>(_val.value());
        }

        //  Less Than
        template<
          typename V,
          typename U,
          typename is_convertible = typename std::enable_if<std::is_same<typename U::dimensions_t, typename Units::dimensions_t>::value, U>::type
        >
        constexpr bool operator < (const Quantity<V, U>& _val) const {
            return val_ < units::convert<Value, Units, U>(_val.value());
        }

        //  Less Than or Equal
        template<
          typename V,
          typename U,
          typename is_convertible = typename std::enable_if<std::is_same<typename U::dimensions_t, typename Units::dimensions_t>::value, U>::type
        >
        constexpr bool operator <= (const Quantity<V, U>& _val) const {
            return val_ <= units::convert<Value, Units, U>(_val.value());
        }

        //
        // Arithmetic Operations
        //
        //  Negation
        constexpr auto operator - () const {
            return Quantity<value_t, Units>(-val_);
        }

        //  Addition
        template<
          typename V,
          typename U,
          typename is_convertible = typename std::enable_if<std::is_same<typename U::dimensions_t, typename Units::dimensions_t>::value, U>::type
        >
        constexpr auto operator += (const Quantity<V, U>& _val) {
            val_ += units::convert<Value, Units, U>(_val.value());
            return *this;
        }

        //  Subtraction
        template<
          typename V,
          typename U,
          typename is_convertible = typename std::enable_if<std::is_same<typename U::dimensions_t, typename Units::dimensions_t>::value, U>::type
        >
        constexpr auto operator -= (const Quantity<V, U>& _val) {
            val_ -= units::convert<Value, Units, U>(_val.value());
            return *this;
        }

        //  NOTE: SCALAR MULTIPLICATION AND DIVISION ONLY WORK IF V IS NOT A QUANTITY
        //      ALSO, THEY DO NOT WORK THE SAME WAY WITH UNITS THAT HAVE A BASE (LIKE ABSOLUTE TEMPERATURE)
        //  Scalar Multiplication -- This only works if V is not a quantity
        template<typename V, typename scalar = typename std::enable_if<!match_quantity(V()), void>::type>
        constexpr auto operator *= (const V& _val) {
            static_assert(
                !match_quantity(_val),
                "Quantity multiply-assign only available for scalars"
            );
            val_ *= _val;
            return *this;
        }

        //  Scalar Division
        template<typename V, typename scalar = typename std::enable_if<!match_quantity(V()), void>::type>
        constexpr auto operator /= (const V& _val) {
            static_assert(
                !match_quantity(_val),
                "Quantity divide-assign only available for scalars"
            );
            val_ /= _val;
            return *this;
        }

        constexpr value_t value() const { return val_; }

    protected:
        value_t val_;
};

template<typename V1, typename U1, typename V2, typename U2>
constexpr auto operator + (const Quantity<V1, U1>& _a, const Quantity<V2, U2>& _b) {
    // THIS SHOULDN'T WORK IF BOTH ARE ABSOLUTE UNITS
    using Value = std::common_type_t<V1, V2>;
    using return_t = Quantity<Value, U1>;
    return return_t(_a.value() + convert<Value, U1, U2>(_b.value()));
}

template<typename V1, typename U1, typename V2, typename U2>
constexpr auto operator - (const Quantity<V1, U1>& _a, const Quantity<V2, U2>& _b) {
    // THIS SHOULD WORK ONLY IF BOTH ARE EITHER RELATIVE OR ABSOLUTE UNITS
    using Value = std::common_type_t<V1, V2>;
    using return_t = Quantity<Value, U1>;
    return return_t(_a.value() - convert<Value, U1, U2>(_b.value()));
}

// MULTIPLICATION AND DIVISION SHOULD WORK ONLY IF BOTH UNITS ARE RELATIVE

//
// Multiplication
//
template<typename V1, typename U1, typename V2, typename U2>
constexpr auto operator * (const Quantity<V1, U1>& _a, const Quantity<V2, U2>& _b) {
    static_assert(
        !(U1::absolute || U2::absolute),
        "Attempting to multiply units which are not relative"
    );
    using value_t = std::common_type_t<V1, V2>;
    using return_units_t = internal::MultUnits<U1, U2>;
    using return_t = Quantity<value_t, return_units_t>;
    return return_t(_a.value() * _b.value());
}

template<typename V1, typename U1, typename Scalar, typename Valid = typename std::enable_if<std::is_fundamental<Scalar>::value, Scalar>::type>
constexpr auto operator * (const Quantity<V1, U1>& _a, const Scalar& _s) {
    static_assert(
        !U1::absolute,
        "Attempting to multiply a unit which is not relative by a scalar"
    );
    using value_t = std::common_type_t<V1, Scalar>;
    using return_t = Quantity<value_t, U1>;
    return return_t(_a.value() * _s);
}

template<typename Scalar, typename V1, typename U1, typename Valid = typename std::enable_if<std::is_fundamental<Scalar>::value, Scalar>::type>
constexpr auto operator * (const Scalar& _s, const Quantity<V1, U1>& _a) {
    static_assert(
        !U1::absolute,
        "Attempting to multiply a unit which is not relative by a scalar"
    );
    using value_t = std::common_type_t<V1, Scalar>;
    using return_t = Quantity<value_t, U1>;
    return return_t(_s * _a.value());
}

template<typename V1, typename U1, typename V2, typename U2>
constexpr auto operator / (const Quantity<V1, U1>& _a, const Quantity<V2, U2>& _b) {
    static_assert(
        !(U1::absolute || U2::absolute),
        "Attempting to divide units which are not relative"
    );
    using value_t = std::common_type_t<V1, V2>;
    using return_units_t = internal::DivUnits<U1, U2>;
    using return_t = Quantity<value_t, return_units_t>;
    return return_t(_a.value() / _b.value());
}

template<typename V1, typename U1, typename Scalar, typename Valid = typename std::enable_if<std::is_fundamental<Scalar>::value, Scalar>::type>
constexpr auto operator / (const Quantity<V1, U1>& _a, const Scalar& _s) {
    static_assert(
        !U1::absolute,
        "Attempting to divide a non-relative unit by a scalar"
    );
    using value_t = std::common_type_t<V1, Scalar>;
    using return_t = Quantity<value_t, U1>;
    return return_t(_a.value() / _s);
}

template<typename Stream, typename Value, typename Units>
Stream& operator << (Stream& _stream, const Quantity<Value, Units>& _q) {
    _stream << _q.value() << ' ';
    Units::streamname(_stream);
    return _stream;
}

template<typename Units, typename Value, typename BaseUnits>
constexpr auto as(const Quantity<Value, BaseUnits>& _val) {
    return Quantity<Value, Units>{units::convert<Value, Units, BaseUnits>(_val.value())};
}

template<typename Units, typename Value>
constexpr auto as(const Value& _val) {
    return Quantity<Value, Units>{_val};
}

} /*namespace units*/
} /*namespace chandra*/
#endif /*CHANDRA_QUANTITY_H*/
