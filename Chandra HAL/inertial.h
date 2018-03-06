#ifndef CHANDRA_INERTIAL_H
#define CHANDRA_INERTIAL_H

#include "matrix.h"
#include "matrix_ops.h"
#include "matrix_view.h"
#include "quantity.h"
#include "rotation.h"
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
        template<typename Impl, typename BaseUnits>
        class Proxy
        {
            protected:
                using setter_t = scalar_t (Impl::*)(scalar_t);
                using getter_t = scalar_t (Impl::*)() const;

            public:
                Proxy(Impl& _owner,
                      const transform_t& _R, const value_t& _v, // Access Rotation and Raw Value
                      setter_t _set_fs, getter_t _get_fs,       // Full-Scale Config Functions
                      setter_t _set_odr, getter_t _get_odr,     // Ouput Data Rate Config Functions
                      setter_t _set_lpf, getter_t _get_lpf,     // Low-Pass Filter Config Functions
                      setter_t _set_hpf, getter_t _get_hpf)     // High-Pass Filter Config Functions
                    : owner_(_owner),
                      G(transform_t::Eye()),
                      R(_R), v(_v), o(0),
                      set_fs_(_set_fs), get_fs_(_get_fs),
                      set_odr_(_set_odr), get_odr_(_get_odr),
                      set_lpf_(_set_lpf), get_lpf_(_get_lpf),
                      set_hpf_(_set_hpf), get_hpf_(_get_hpf)
                {}

                //
                // Conversion and Transformation
                //
                template<typename V, typename U>
                auto offset(const units::Quantity<V, U>& _v) {
                    const auto new_o = chandra::units::convert<BaseUnits, U>(chandra::math::solve(A_, _v.value()));
                    o = new_o;
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

                //
                // Configuration
                //
                auto fullscale(units::Quantity<scalar_t, BaseUnits> _fs) {
                    return units::Quantity<scalar_t, BaseUnits>((owner_.*set_fs_)(_fs.value()));
                }

                auto fullscale() {
                    return units::Quantity<scalar_t, BaseUnits>((owner_.*get_fs_)());
                }

                auto datarate(units::Quantity<scalar_t, units::mks::Hz> _odr) {
                    return units::Quantity<scalar_t, units::mks::Hz>((owner_.*set_odr_)(_odr.value()));
                }

                auto datarate() {
                    return units::Quantity<scalar_t, units::mks::Hz>((owner_.*get_odr_)());
                }

                auto lowpass(units::Quantity<scalar_t, units::mks::Hz> _freq) {
                    return units::Quantity<scalar_t, units::mks::Hz>((owner_.*set_lpf_)(_freq.value()));
                }

                auto lowpass() {
                    return units::Quantity<scalar_t, units::mks::Hz>((owner_.*get_lpf_)());
                }

                auto highpass(units::Quantity<scalar_t, units::mks::Hz> _freq) {
                    return units::Quantity<scalar_t, units::mks::Hz>((owner_.*set_hpf_)(_freq.value()));
                }

                auto highpass() {
                    return units::Quantity<scalar_t, units::mks::Hz>((owner_.*get_hpf_)());
                }

            protected:
                value_t value() const { // TODO: DECIDE IF THIS SHOULD BE PUBLIC
                    return A_ * (v - o);
                }

                Impl& owner_;
                transform_t G;
                const transform_t& R;
                const value_t& v;
                value_t o;
                transform_t A_;
                setter_t set_fs_;
                getter_t get_fs_;
                setter_t set_odr_;
                getter_t get_odr_;
                setter_t set_lpf_;
                getter_t get_lpf_;
                setter_t set_hpf_;
                getter_t get_hpf_;
        };

    public:
        Inertial() : R(transform_t::Eye()) {}

        transform_t rotation() const { return R; }

        //
        // Update Rotation Matrix
        //
        //  Direct Matrix Assignment
        transform_t rotation(const transform_t _R) {
            R = _R;
            static_cast<Derived*>(this)->transformUpdate();
            return R;
        }

        //  Convert Rotation Object to Matrix
        transform_t rotation(auto _r) {
            R = math::dcm(_r);
            return R;
        }

        //  Convert Tait-Bryan Angles to Matrix
        transform_t rotation(auto roll, auto pitch, auto yaw) {
            R = math::dcm(roll, pitch, yaw);
            return R;
        }

     protected:
        void transformUpdate() {}
        transform_t R;
};

// TODO: THERE SHOULD BE AN EASY WAY TO OVERRIDE THE DEFAULT UNITS
template<
    typename Derived,
    typename Value,
    size_t N,
    typename AccelUnits = units::mks::m_per_s2>
class Accelerometer : public Inertial<Accelerometer<Derived, Value, N, AccelUnits>, Value, N>
{
    protected:
        friend class Inertial<Accelerometer<Derived, Value, N, AccelUnits>, Value, N>;
        using base_t = Inertial<Accelerometer<Derived, Value, N, AccelUnits>, Value, N>;
        using accelerometer_proxy_t = typename base_t::template Proxy<Derived, AccelUnits>;
        typename base_t::value_t accel_raw_;

    public:
        Accelerometer()
            : accelerometer(
                  static_cast<Derived&>(*this),
                  this->R, accel_raw_,
                  &Derived::set_accel_fs, &Derived::get_accel_fs,
                  &Derived::set_accel_odr, &Derived::get_accel_odr,
                  &Derived::set_accel_lpf, &Derived::get_accel_lpf,
                  &Derived::set_accel_hpf, &Derived::get_accel_hpf
              )
        {
            transformUpdate();
        }

        accelerometer_proxy_t accelerometer;

    protected:
        void transformUpdate() { accelerometer.calcA(); }
};

template<
    typename Derived,
    typename Value,
    size_t N,
    typename GyroUnits = units::mks::rad_per_s>
class Gyroscope : public Inertial<Gyroscope<Derived, Value, N, GyroUnits>, Value, N>
{
    protected:
        friend class Inertial<Gyroscope<Derived, Value, N, GyroUnits>, Value, N>;
        using base_t = Inertial<Gyroscope<Derived, Value, N, GyroUnits>, Value, N>;
        using gyroscope_proxy_t = typename base_t::template Proxy<Derived, GyroUnits>;
        typename base_t::value_t gyro_raw_;

    public:
        Gyroscope()
            : gyroscope(
                  static_cast<Derived&>(*this),
                  this->R, gyro_raw_,
                  &Derived::set_gyro_fs, &Derived::get_gyro_fs,
                  &Derived::set_gyro_odr, &Derived::get_gyro_odr,
                  &Derived::set_gyro_lpf, &Derived::get_gyro_lpf,
                  &Derived::set_gyro_hpf, &Derived::get_gyro_hpf
              )
        {
            transformUpdate();
        }

        gyroscope_proxy_t gyroscope;

    protected:
        void transformUpdate() { gyroscope.calcA(); }
};

// Declare Magnetometer baseclass

// Declare AccelGyro baseclass
template<    
    typename Derived,
    typename Value,
    size_t N,
    typename AccelUnits = units::mks::m_per_s2,
    typename GyroUnits = units::mks::rad_per_s>
class AccelGyro : public Inertial<AccelGyro<Derived, Value, N, AccelUnits, GyroUnits>, Value, N>
{
    protected:
        friend class Inertial<AccelGyro<Derived, Value, N, AccelUnits, GyroUnits>, Value, N>;
        using base_t = Inertial<AccelGyro<Derived, Value, N, AccelUnits, GyroUnits>, Value, N>;
        using accelerometer_proxy_t = typename base_t::template Proxy<Derived, AccelUnits>;
        using gyroscope_proxy_t = typename base_t::template Proxy<Derived, GyroUnits>;
        typename base_t::value_t accel_raw_;
        typename base_t::value_t gyro_raw_;

    public:
        AccelGyro()
            : accel_raw_{1, 0, 0}, gyro_raw_{6.283185, 0, -3.14159},
              accelerometer(
                  static_cast<Derived&>(*this),
                  this->R, accel_raw_,
                  &Derived::set_accel_fs, &Derived::get_accel_fs,
                  &Derived::set_accel_odr, &Derived::get_accel_odr,
                  &Derived::set_accel_lpf, &Derived::get_accel_lpf,
                  &Derived::set_accel_hpf, &Derived::get_accel_hpf
              ),
              gyroscope(
                  static_cast<Derived&>(*this),
                  this->R, gyro_raw_,
                  &Derived::set_gyro_fs, &Derived::get_gyro_fs,
                  &Derived::set_gyro_odr, &Derived::get_gyro_odr,
                  &Derived::set_gyro_lpf, &Derived::get_gyro_lpf,
                  &Derived::set_gyro_hpf, &Derived::get_gyro_hpf
              )
        {
            transformUpdate();
        }

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


