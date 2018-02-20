#ifndef CHANDRA_QUATERNION_H
#define CHANDRA_QUATERNION_H

#include "matrix.h"
#include "matrix_ops.h"

namespace chandra
{
namespace math
{

template<typename Value>
class Quaternion
{
    public:
        using value_t = Value;
        using ref_t = Quaternion<Value>;

        //
        // Construction
        //

        //  Construct a Quaternion to Transform From Vector 1 to Vector 2
        //      --> From the LOL Engine Blog :
        //      --> "Beautiful maths simplification: quaternion from two vectors -- final version"

        // TODO: MODIFY TO HANDLE EXACTLY OPPOSITE VECTORS....
        template<typename V1, typename V2>
        static constexpr auto Transform(
                const Matrix<V1, 3, 1>& _src,
                const Matrix<V2, 3, 1>& _dest
        ) {
            using calc_t = typename std::common_type<V1, V2>::type;
            constexpr calc_t threshold(1e-6);
            const auto norm_src_norm_dest = sqrt(dot(_src, _src) * dot(_dest, _dest));
            auto w = norm_src_norm_dest + dot(_src, _dest);
            ref_t q;

            if(w < (threshold*norm_src_norm_dest)) { // Vectors point in opposite directions
                q.w = 0;
                if(abs(_src(0)) > abs(_src(2))) {
                    q.x = -_src(1); q.y = _src(0); q.z = 0;
                } else {
                    q.x = 0; q.y = -_src(2); q.z = _src(1);
                }
            } else { // Normal Can Be Found
                const auto vn = cross(_dest, _src);
                q.w = w; q.x = vn(0); q.y = vn(1); q.z = vn(2);
            }
            return q.normalized();
        }

        //  Construct a Quaternion to Transform from Unit Vector 1 to Unit Vector 2
        template<typename V1, typename V2>
        static constexpr auto UnitTransform(
                const Matrix<V1, 3, 1>& _src,
                const Matrix<V2, 3, 1>& _dest
        ) {
            using calc_t = typename std::common_type<V1, V2>::type;
            constexpr calc_t one(1);
            constexpr calc_t two(2);
            constexpr calc_t half(0.5);

            constexpr auto m = sqrt(two + (two * dot(_src, _dest)));
            constexpr auto vn = (one/m) * cross(_src, _dest);
            return ref_t(half*m, vn.x, vn.y, vn.z);
        }

        //  Construct a Quaternion From Angle-Axis (Components)
        template<typename V1, typename V2, typename V3, typename V4>
        static constexpr auto AngleAxis(
                const V1& _alpha,
                const V2& _x, const V3& _y, const V4& _z
        ) {
            constexpr auto half_alpha = _alpha / value_t(2);
            const auto c = cos(half_alpha);
            const auto s = sin(half_alpha);
            ref_t q;

            q.w = c;
            q.x = s*_x;
            q.y = s*_y;
            q.z = s*_z;

            return q;
        }

        //  Construct a Quaternion From Angle-Axis (Vector)
        template<typename V1, typename V2>
        static constexpr ref_t AngleAxis(
                const V1& _alpha,
                const Matrix<V2, 3, 1>& _vec
        ) {
            return ref_t::AngleAxis(_alpha, _vec(0), _vec(1), _vec(2));
        }

        //  Construct a Pure Quaternion From a Vector
        template<typename V>
        static constexpr ref_t Pure(const Matrix<V, 3, 1>& _vec) {
            return ref_t(0, _vec(0), _vec(1), _vec(2));
        }

        //  Default Constructor
        constexpr Quaternion() : w(0), x(0), y(0), z(0) {}

        //  Direct Value Constructor
        explicit constexpr Quaternion(
                const value_t& _w,
                const value_t& _x = value_t(0),
                const value_t& _y = value_t(0),
                const value_t& _z = value_t(0)
        ) : w(_w), x(_x), y(_y), z(_z) {}

        //  Construction from vector
        template<typename V>
        explicit constexpr Quaternion(const Matrix<V, 4, 1>& _vec)
            : w(_vec(0)), x(_vec(1)), y(_vec(2)), z(_vec(3)) {}

        //  Copy Constructor
        template<typename V>
        constexpr Quaternion(const Quaternion<V>& _q) : w(_q.w), x(_q.x), y(_q.y), z(_q.z) {}

        //
        // Arithmetic Operations
        //

        //  Negative Quaternion
        constexpr ref_t operator - () { return ref_t(-w, -x, -y, -z); }

        //  Addition
        template<typename V>
        ref_t& operator += (const Quaternion<V>& _q) {
            w += _q.w;
            x += _q.x;
            y += _q.y;
            z += _q.z;
            return *this;
        }

        //  Subtraction
        template<typename V>
        ref_t& operator -= (const Quaternion<V>& _q) {
            w -= _q.w;
            x -= _q.x;
            y -= _q.y;
            z -= _q.z;
            return *this;
        }

        //  Multiplication By Scalar
        template<typename V>
        ref_t& operator *= (const V& _c) {
            w *= _c;
            x *= _c;
            y *= _c;
            z *= _c;
            return *this;
        }

        //  Multiplication By Quaternion
        template<typename V>
        ref_t& operator *= (const Quaternion<V>& _r) {
            const auto t_w = (w * _r.w) - (x * _r.x) - (y * _r.y) - (z * _r.z);
            const auto t_x = (x * _r.w) + (w * _r.x) - (z * _r.y) + (y * _r.z);
            const auto t_y = (y * _r.w) + (z * _r.x) + (w * _r.y) - (x * _r.z);
            const auto t_z = (z * _r.w) - (y * _r.x) + (x * _r.y) + (w * _r.z);
            w = t_w;
            x = t_x;
            y = t_y;
            z = t_z;
            return *this;
        }

        // Division By Scalar
        template<typename V>
        ref_t& operator /= (const V& _c) {
            w /= _c;
            x /= _c;
            y /= _c;
            z /= _c;
            return *this;
        }

        //  Division By Quaternion
        template<typename V>
        ref_t& operator /= (const Quaternion<V>& _r) {
            const auto r_norm = (w*w) + (x*x) + (y*y) + (z*z);
            const auto t_w = (w * _r.w) + (x * _r.x) + (y * _r.y) + (z * _r.z);
            const auto t_x = (x * _r.w) - (w * _r.x) - (z * _r.y) + (y * _r.z);
            const auto t_y = (y * _r.w) + (z * _r.x) - (w * _r.y) - (x * _r.z);
            const auto t_z = (z * _r.w) - (y * _r.x) + (x * _r.y) - (w * _r.z);
            w = t_w/r_norm;
            x = t_x/r_norm;
            y = t_y/r_norm;
            z = t_z/r_norm;
            return *this;
        }

        //  Quaternion Norm
        auto norm() const { return (w*w) + (x*x) + (y*y) + (z*z); }

        //  Quaternion Magnitude
        auto magnitude() const { return sqrt(norm()); }

        //  Normalized Quaternion
        ref_t normalized() const {
            const auto m = magnitude();
            return ref_t(w/m, x/m, y/m, z/m);
        }

        //
        // Components
        //
        value_t w;
        value_t x;
        value_t y;
        value_t z;
};


} /*namespace math*/
} /*namespace chandra*/

#endif /*CHANDRA_QUATERNION_H*/

