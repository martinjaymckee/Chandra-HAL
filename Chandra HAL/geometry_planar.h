#ifndef CHANDRA_GEOMETRY_CORE_H
#define CHANDRA_GEOMETRY_CORE_H

#include "coordinates.h"
#include "matrix_vectors.h"
#include "matrix_vector_ops.h"
#include "meta_types.h"

namespace chandra
{
namespace geometry
{
template<class Value, class Frame=chandra::aero::frames::None>
using Point3D = chandra::math::Vector3D<Value, true, Frame>;

template<class Value, class Frame=chandra::aero::frames::None>
class Line3D
{
  public:
      using value_t = Value;
      using frame_t = Frame;
    using vector_t = chandra::math::Vector3D<Value, true, Frame>;

    static constexpr Line3D FromPoints(vector_t _p0, vector_t _p1) {
        return Line3D(_p0, _p1 - _p0);
    }

    static constexpr Line3D FromPointVector(vector_t _p, vector_t _v) {
      return Line3D(_p, _v);
    }

    static constexpr Line3D FromVector(vector_t _v) {
        return Line3D( {value_t(0), value_t(0), value_t(0) }, _v);
    }

    constexpr Line3D(vector_t _origin, vector_t _direction)
      : origin_(_origin), direction_(_direction) {}

    template<class V>
    constexpr Line3D(const chandra::math::Vector3D<V, true, Frame>& _other) {
      origin_ = _other.origin();
      direction_ = _other.direction();
      // TODO: COEFFICIENTS
    }

    constexpr value_t a() const {
        return a_;
    }

    constexpr value_t b() const {
        return b_;
    }

    constexpr value_t c() const {
        return c_;
    }

    constexpr vector_t origin() const {
      return origin_;
    }

    constexpr vector_t direction() const {
      return direction_;
    }

  private:
      value_t a_;
      value_t b_;
      value_t c_;
    vector_t origin_;
    vector_t direction_;
};

template<class Stream, class Value, class Frame>
Stream& operator << (Stream& _stream, const Line3D<Value, Frame>& _l) {
    _stream << "Line3D(p0 = " << _l.origin() << ", v = " << _l.direction() << ")";
    return _stream;
}

template<class T>
struct TD;

template<class Value, class Frame=chandra::aero::frames::None>
class Plane3D
{
  public:
    using scalar_t = chandra::scalar_of_t<Value>;
    using value_t = Value;
    using frame_t = Frame;
    using vector_t = chandra::math::Vector3D<value_t, true, Frame>;

    static constexpr Plane3D FromPoints(vector_t _p0, vector_t _p1, vector_t _p2) {
        using namespace chandra::units;

        const auto La = _p1 - _p0;
        const auto Lb = _p2 - _p0;
        const auto n_2 = chandra::math::cross(La, Lb);

        const vector_t n{
            value_t(scalar_cast(n_2(0))),  // a
            value_t(scalar_cast(n_2(1))),  // b
            value_t(scalar_cast(n_2(2)))   // c
        };

        const value_t d{ chandra::units::scalar_cast(-chandra::math::dot(_p0, n)) }; // TODO: FIGURE OUT WHY EQUALITY IS WORKING WITH D NOT NEGATED....
      return Plane3D(scalar_t(scalar_cast(n(0))), scalar_t(scalar_cast(n(1))), scalar_t(scalar_cast(n(2))), d);
    }

    static constexpr Plane3D FromOriginAndNormal(vector_t _p0, vector_t _n) {
        using namespace chandra::units;
        const value_t d( value_t(scalar_cast((_p0(0)*_n(0)) + (_p0(1)*_n(1)) + (_p0(2)*_n(2)) ) ) );
        return Plane3D(scalar_t(scalar_cast(_n(0))), scalar_t(scalar_cast(_n(1))), scalar_t(scalar_cast(_n(2))), -d);
    }

    constexpr Plane3D(scalar_t _a, scalar_t _b, scalar_t _c, value_t _d)
        : a_(_a), b_(_b), c_(_c), d_(_d),
        origin_{ value_t(0), value_t(0), value_t(-_d / _c) }, // TODO: NEED TO DO SOMETHING HERE IF THE PLANE IS PARALLEL TO THE Y AXIS
        normal_{ value_t(_a), value_t(_b), value_t(_c) } {}

    constexpr scalar_t a() const {
      return a_;
    }

    constexpr scalar_t b() const {
      return b_;
    }

    constexpr scalar_t c() const {
      return c_;
    }

    constexpr value_t d() const {
      return d_;
    }

    constexpr vector_t origin() const {
      return origin_;
    }

    constexpr vector_t normal() const {
      return normal_;
    }

 //   template<class V>
 //   constexpr bool operator == (const Plane3D<V, Frame>& _other) const {
 //       return false;
 //   }

    protected:

  private:
    scalar_t a_;
    scalar_t b_;
    scalar_t c_;
    value_t d_;
    vector_t origin_;
    vector_t normal_;
};

template<class Stream, class Value, class Frame>
Stream& operator << (Stream& _stream, const Plane3D<Value, Frame>& _p) {
    _stream << "Plane3D(p0 = " << _p.origin() << ", n = " << _p.normal() << ")";
    return _stream;
}

//
// Check Parallel
//

// Line/Line
template<class V1, class V2, class Frame>
constexpr bool parallel(const Line3D<V1, Frame>& _a, const Line3D<V2, Frame>& _b) {
    const auto v_a = _a.direction();
    const auto v_b = _b.direction();
    const auto norm_a = chandra::math::norm(v_a);
    const auto norm_b = chandra::math::norm(v_b);
    const auto n = chandra::math::cross(v_a, v_b);
    return chandra::math::norm(n) <= (1e-9 * norm_a * norm_b); // TODO: NEED TO GET THE EPSILON VALUE FROM SOMEWHERE ELSE
}

// Plane/Line
template<class V1, class V2, class Frame>
constexpr bool parallel(const Plane3D<V1, Frame>& _p, const Line3D<V2, Frame>& _l) {
    using product_t = decltype(std::declval<V1>() * std::declval<V2>());
    const auto v_a = chandra::math::unit(_p.normal());
    const auto v_b = chandra::math::unit(_l.direction());
//    std::cout << v_a << " -- " << v_b << " -- " << chandra::math::dot(v_a, v_b) << "\n";
    return product_t(chandra::math::dot(v_a, v_b)) <= product_t(1e-12); // TODO: NEED TO GET THE EPSILON VALUE FROM SOMEWHERE ELSE
}

template<class V1, class V2, class Frame>
constexpr bool parallel(const Line3D<V1, Frame>& _l, const Plane3D<V2, Frame>& _p) {
    return parallel(_p, _l);
}


// Plane/Plane
template<class V1, class V2, class Frame>
constexpr bool parallel(const Plane3D<V1, Frame>& _a, const Plane3D<V2, Frame>& _b) {
    const auto v_a = _a.normal();
    const auto v_b = _b.normal();
    const auto norm_a = chandra::math::norm(v_a);
    const auto norm_b = chandra::math::norm(v_b);
    const auto n = chandra::math::cross(v_a, v_b);
    return chandra::math::norm(n) <= (1e-9 * norm_a * norm_b); // TODO: NEED TO GET THE EPSILON VALUE FROM SOMEWHERE ELSE
}


//
// Planar Intersections
//
//
// TODO: THESE INTERSECTION TEST FUNCTIONS SHOULD ALLOW FOR DIFFERENT VALUE TYPES AND FRAMES
//  AND DO THE APPROPRIATE CONVERSIONS BETWEEN
//

template<class Geom>
class IntersectionResult
{
public:
    constexpr IntersectionResult() : valid_(false) {}
    constexpr IntersectionResult(Geom _intersection)
        : valid_(true), intersection_(_intersection) {}

    constexpr operator bool() const { return valid_; }
    constexpr Geom intersection() const { return intersection_; }

private:
    bool valid_;
    Geom intersection_;
};

// Line3D/Point3D
template<class V1, class V2, class Frame>
constexpr auto intersect(Line3D<V1, Frame> _l, Point3D<V2, Frame> _p) {
//    static_assert(false, "Unimplemented: intersect(Line, Point)");
    return IntersectionResult<Point3D<V1, Frame>>();
}

template<class V1, class V2, class Frame>
constexpr auto intersect(Point3D<V1, Frame> _p, Line3D<V2, Frame> _l) {
    return intersect(_l, _p);
}

// Line3D/Line3D
template<class V1, class V2, class Frame>
constexpr auto intersect(Line3D<V1, Frame> _a, Line3D<V2, Frame> _b) {
//    static_assert(false, "Unimplemented: intersect(Line, Line)");
    return IntersectionResult<Point3D<V1, Frame>>();
}

// Plane3D/Point3D
template<class V1, class V2, class Frame>
constexpr auto intersect(Plane3D<V1, Frame> _l, Point3D<V2, Frame> _p) {
//    static_assert(false, "Unimplemented: intersect(Plane, Point)");
    return IntersectionResult<Point3D<V1, Frame>>();
}

template<class V1, class V2, class Frame>
constexpr auto intersect(Point3D<V1, Frame> _p, Plane3D<V2, Frame> _l) {
    return intersect(_l, _p);
}

// Plane3D/Line3D Intersection
template<class V1, class V2, class Frame>
constexpr auto intersect(Plane3D<V1, Frame> _plane, Line3D<V2, Frame> _line) {
    using geom_t = typename Line3D<V1, Frame>::vector_t;
    using result_t = IntersectionResult<geom_t>;

    if(parallel(_plane, _line)) {
        return result_t();
    }

    const auto a = _plane.a();
    const auto b = _plane.b();
    const auto c = _plane.c();
    const auto d = _plane.d();
    const auto p = _line.origin();
    const auto v = _line.direction();

    const auto t = -(a * p.x + b * p.y + c * p.z + d) / (a * v.x + b * v.y + c * v.z);
    return result_t(p + t * v);
}

template<class V1, class V2, class Frame>
constexpr auto intersect(Line3D<V1, Frame> _line, Plane3D<V2, Frame> _plane) {
    return intersect(_plane, _line);
}

// Plane3D/Plane3D
template<class V1, class V2, class Frame>
constexpr auto intersect(Plane3D<V1, Frame> _a, Plane3D<V2, Frame> _b) {
//    static_assert(false, "Unimplemented: intersect(Plane, Plane)");
    return IntersectionResult<Line3D<V1, Frame>>();
}


//
// Planar Distance
//

// Point3D/Point3D
template<class V1, class V2, class Frame>
constexpr auto distance(const Point3D<V1, Frame>& _a, const Point3D<V2, Frame>& _b) {
    return V1(magnitude(_a - _b));
}

// Line3D/Point3D
template<class V1, class V2, class Frame>
constexpr auto distance(const Line3D<V1, Frame>& _l, const Point3D<V2, Frame>& _p) {
    const auto v_a = _l.direction();
    const auto v_b = _p - _l.origin();
    if (chandra::math::magnitude(v_b) <= V1(1e-12)) return V1(0); // TODO: NEED TO GET THIS THRESHOLD SOMEWHERE....
    return V1(sqrt(chandra::math::norm(chandra::math::cross(v_a, v_b)) / chandra::math::norm(v_b)));
}

template<class V1, class V2, class Frame>
constexpr auto distance(const Point3D<V1, Frame>& _p, const Line3D<V2, Frame>& _l) {
    return distance(_l, _p);
}

// Line3D/Line3D
template<class V1, class V2, class Frame>
constexpr auto distance(const Line3D<V1, Frame>& _a, const Line3D<V2, Frame>& _b) {
//    const auto N = chandra::math::cross(_a.direction(), _b.direction());
//    const auto a = chandra::math::dot(N, (_a.origin() - _b.origin())) / chandra::math::norm(N);
//    std::cout << a << '\n';
    //    TD<decltype(a)> b;

    if (parallel(_a, _b)) return distance(_a, _b.origin()); // Use line/point distance on parallel lines
    const auto n = chandra::math::cross(_a.direction(), _b.direction());
    return V1(chandra::math::dot(n, (_a.origin() - _b.origin())) / chandra::math::magnitude(n));
}

// Plane3D/Point3D
template<class V1, class V2, class Frame>
constexpr auto distance(const Plane3D<V1, Frame>& _plane, const Point3D<V2, Frame> _p) {
    const auto a = _plane.a();
    const auto b = _plane.b();
    const auto c = _plane.c();
    const auto d = _plane.d();

    return V1((a*_p.x + b*_p.y + c*_p.z + d) / sqrt(a*a + b*b + c*c));
}

template<class V1, class V2, class Frame>
constexpr auto distance(const Point3D<V1, Frame>& _p, const Plane3D<V2, Frame> _plane) {
    return distance(_plane, _p);
}

// Plane3D/Line3D
template<class V1, class V2, class Frame>
constexpr auto distance(const Plane3D<V1, Frame>& _plane, const Line3D<V2, Frame> _l) {
    if (parallel(_plane, _l)) return distance(_plane, _l.origin());
    return V1(0);
}

template<class V1, class V2, class Frame>
constexpr auto distance(const Line3D<V1, Frame>& _l, const Plane3D<V2, Frame> _plane) {
    return distance(_plane, _l);
}

// Plane3D/Plane3D
template<class V1, class V2, class Frame>
constexpr auto distance(const Plane3D<V1, Frame>& _a, const Plane3D<V2, Frame>& _b) {
    if (parallel(_a, _b)) return distance(_a, _b.origin());
    return V1(0);
}


//
// Colinearity/Coplanarity
//
// Line/Line
template<class V1, class V2, class Frame>
constexpr bool colinear(const Line3D<V1, Frame>& _a, const Line3D<V2, Frame>& _b) {
    if (parallel(_a, _b)) {
        if (distance(_a, _b) < V1(1e-9)) { // TODO: NEED TO ACTUALLY GET THIS THRESHOLD VALUE FROM SOMEWHERE
            return true;
        }
    }

    return false;
}

// Plane/Line
template<class V1, class V2, class Frame>
constexpr bool coplanar(const Plane3D<V1, Frame>& _p, const Line3D<V2, Frame>& _l) {
    if (parallel(_p, _l)) {
        if (distance(_p, _l) < V1(1e-9)) { // TODO: NEED TO ACTUALLY GET THIS THRESHOLD VALUE FROM SOMEWHERE
            return true;
        }
    }

    return false;
}

template<class V1, class V2, class Frame>
constexpr bool coplanar(const Line3D<V1, Frame>& _l, const Plane3D<V2, Frame>& _p) {
    return coplanar(_p, _l);
}


// Plane/Plane
template<class V1, class V2, class Frame>
constexpr bool coplanar(const Plane3D<V1, Frame>& _a, const Plane3D<V2, Frame>& _b) {
    if (parallel(_a, _b)) {
        if (distance(_a, _b) < V1(1e-9)) { // TODO: NEED TO ACTUALLY GET THIS THRESHOLD VALUE FROM SOMEWHERE
            return true;
        }
    }
    return false;
}

//
// Planar Equality
//

// Line/Line
template<class V1, class V2, class Frame>
constexpr bool operator == (const Line3D<V1, Frame>& _a, const Line3D<V2, Frame>& _b) {
    return colinear(_a, _b);
}

// Plane/Plane
template<class V1, class V2, class Frame>
constexpr bool operator == (const Plane3D<V1, Frame>& _a, const Plane3D<V2, Frame>& _b) {
    return coplanar(_a, _b);
}

// TODO: INTERSECTIONS BETWEEN SPHERES, ELLIPSOIDS, CIRCLES, RAYS, LINE SEGMENTS, ETC.
} /*namespace geometry*/
} /*namespace chandra*/

#endif /*CHANDRA_GEOMETRY_CORE_H*/
