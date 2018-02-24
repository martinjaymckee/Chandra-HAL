#ifndef CHANDRA_INERTIAL_H
#define CHANDRA_INERTIAL_H

#include "units.h"
#include "matrix.h"
#include "matrix_ops.h"
#include "matrix_view.h"
#include "quantity.h"
#include "units.h"

namespace chandra
{
namespace drivers
{

template<typename Derived, typename Value, size_t N>
class Inertial
{
    public:
        using scalar_t = Value;
        using value_t = chandra::math::Matrix<Value, N, 1>;
        using transform_t = chandra::math::Matrix<Value, N, N>;

    protected:
        template<typename BaseUnits>
        class Proxy
        {
            public:
                Proxy(const transform_t& _R, const value_t& _v)
                    : G(transform_t::Eye()),
                      R(_R), v(_v), o(0) {
                    calcA();
                }

                template<typename V, typename U>
                auto offset(const units::Quantity<V, U>& _v) {
                    const auto new_o = chandra::units::convert<BaseUnits, U>(chandra::math::solve(A_, _v.value()));
                    o = new_o;
                    cout << "New offset = " << o << "\n";
                    return _v;
                }

                auto offset() const {
                    return units::Quantity<value_t, BaseUnits>{A_*o};
                }

                // Access Gain
                transform_t gain(const transform_t& _G) {
                    G = _G;
                    calcA();
                    return G;
                }

                transform_t gain(const scalar_t& _g) {
                    G = _g * transform_t::Eye();
                    calcA();
                    return G;
                }

                transform_t gain() const { return G; }

                // Current reading of the axes
                auto quantity() const {
                    return units::Quantity<value_t, BaseUnits>{value()};
                }

                auto operator () () const { return quantity(); }

                // Force a calculation of the A Matrix
                void calcA() { // NOTE: This must be called if R is updated
                    A_ = G*R;
                }

                // Access A
                transform_t A() const { return A_; }

            protected:
                value_t value() const { // TODO: DECIDE IF THIS SHOULD BE PUBLIC
                    return A_ * (v - o);
                }

                transform_t G;
                const transform_t& R;
                const value_t& v;
                value_t o;
                transform_t A_;
        };

    public:
        Inertial() : R(transform_t::Eye()) {}

        transform_t rotation() const { return R; }

        // Direct Matrix Assignment
        transform_t rotation(const transform_t _R) {
            R = _R;
            static_cast<Derived*>(this)->transformUpdate();
            return R;
        }

        //
        // TODO: IT IS BETTER TO SIMPLY CREATE ROTATION MATRICIES TO PASS IN
        //
        // Euler Angle Assignment -- TODO: VALIDATE EULER ANGLE INPUT
        transform_t rotation(auto yaw, auto pitch, auto roll) {
            // TODO: IMPLEMENT
            return R;
        }

        // Quaternion Assignment -- TODO: VALIDATE QUATERNION INPUT
        transform_t rotation(auto q) {
            // TODO: IMPLEMENT
            return R;
        }

        // Axis-Angle Assignement -- TODO: VALIDATE AXIS-ANGLE INPUT
        transform_t rotation(auto axis, auto angle) {
            // TODO: IMPLEMENT
            return R;
        }

    protected:
        void transformUpdate() {}
        transform_t R;
};

// TODO: THERE SHOULD BE AN EASY WAY TO OVERRIDE THE DEFAULT UNITS
template<
    typename Value,
    size_t N,
    typename AccelUnits = units::mks::m_per_s2>
class Accelerometer : public Inertial<Accelerometer<Value, N, AccelUnits>, Value, N>
{
    protected:
        friend class Inertial<Accelerometer<Value, N, AccelUnits>, Value, N>;
        using base_t = Inertial<Accelerometer<Value, N, AccelUnits>, Value, N>;
        using accelerometer_proxy_t = typename base_t::template Proxy<AccelUnits>;
        typename base_t::value_t accel_raw_;

    public:
        Accelerometer() : accelerometer(this->R, accel_raw_) {}
        accelerometer_proxy_t accelerometer;

    protected:
        void transformUpdate() { accelerometer.calcA(); }
};

template<
    typename Value,
    size_t N,
    typename GyroUnits = units::mks::rad_per_s>
class Gyroscope : public Inertial<Gyroscope<Value, N, GyroUnits>, Value, N>
{
    protected:
        friend class Inertial<Gyroscope<Value, N, GyroUnits>, Value, N>;
        using base_t = Inertial<Gyroscope<Value, N, GyroUnits>, Value, N>;
        using gyroscope_proxy_t = typename base_t::template Proxy<GyroUnits>;
        typename base_t::value_t gyro_raw_;

    public:
        Gyroscope() : gyroscope(this->R, gyro_raw_) {}
        gyroscope_proxy_t gyroscope;

    protected:
        void transformUpdate() { gyroscope.calcA(); }
};

// Declare Magnetometer baseclass

// Declare AccelGyro baseclass
template<
    typename Value,
    size_t N,
    typename AccelUnits = units::mks::m_per_s2,
    typename GyroUnits = units::mks::rad_per_s>
class AccelGyro : public Inertial<AccelGyro<Value, N, AccelUnits, GyroUnits>, Value, N>
{
    protected:
        friend class Inertial<AccelGyro<Value, N, AccelUnits, GyroUnits>, Value, N>;
        using base_t = Inertial<AccelGyro<Value, N, AccelUnits, GyroUnits>, Value, N>;
        using accelerometer_proxy_t = typename base_t::template Proxy<AccelUnits>;
        using gyroscope_proxy_t = typename base_t::template Proxy<GyroUnits>;
        typename base_t::value_t accel_raw_;
        typename base_t::value_t gyro_raw_;

    public:
        AccelGyro() : accel_raw_{1, 0, 0}, gyro_raw_{6.283185, 0, -3.14159},
            accelerometer(this->R, accel_raw_), gyroscope(this->R, gyro_raw_) {}
        accelerometer_proxy_t accelerometer;
        gyroscope_proxy_t gyroscope;

    protected:
        void transformUpdate() {
            accelerometer.calcA();
            gyroscope.calcA();
        }
};

// Declare AccelMag baseclass

// Declare AccelGyroMag baseclass

} /*namespace drivers*/
} /*namespace chandra*/

#endif /*CHANDRA_INERTIAL_H*/


