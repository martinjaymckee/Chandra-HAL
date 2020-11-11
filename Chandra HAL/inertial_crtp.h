#ifndef CHANDRA_INERTIAL_CRTP_H
#define CHANDRA_INERTIAL_CRTP_H

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

namespace internal
{
template<class Value, class BaseUnits>
struct BaseInertialProxyImpl
{
    using scalar_t = Value;

    template<class... Args>
    BaseInertialProxyImpl(Args...) {}

    auto set_fs(const units::Quantity<scalar_t, BaseUnits>&) {
      return units::Quantity<scalar_t, BaseUnits>(0);
    }

    auto get_fs() {
      return units::Quantity<scalar_t, BaseUnits>(0);
    }

    auto set_odr(const units::Quantity<scalar_t, units::mks::Hz>&) {
      return units::Quantity<scalar_t, units::mks::Hz>(0);
    }

    auto get_odr() {
      return units::Quantity<scalar_t, units::mks::Hz>(0);
    }

    auto set_lpf(const units::Quantity<scalar_t, units::mks::Hz>&) {
      return units::Quantity<scalar_t, units::mks::Hz>(0);
    }

    auto get_lpf() {
      return units::Quantity<scalar_t, units::mks::Hz>(0);
    }

    auto set_hpf(const units::Quantity<scalar_t, units::mks::Hz>&) {
      return units::Quantity<scalar_t, units::mks::Hz>(0);
    }

    auto get_hpf() {
      return units::Quantity<scalar_t, units::mks::Hz>(0);
    }
};
} /*namespace internal*/

template<typename Derived, typename Value, size_t N>
class Inertial
{
    public:
        using scalar_t = Value;
        using value_t = chandra::math::Matrix<Value, N, 1>;
        using transform_t = chandra::math::Matrix<Value, N, N>;

    protected:
        template<class Owner, class BaseUnits, class Impl>
        class Proxy : public Impl
        {
            public:
                template<class... Args>
                Proxy(Owner& _owner, const transform_t& _R, const value_t& _v, Args... args)
                    : Impl(args...), owner_(_owner),
                      G(transform_t::Eye()),
                      R(_R), v(_v), o(0)
                {
                }

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
                    return units::Quantity<scalar_t, BaseUnits>(this->set_fs(_fs.value()));
                }

                auto fullscale() {
                    return units::Quantity<scalar_t, BaseUnits>(this->get_fs());
                }

                auto datarate(units::Quantity<scalar_t, units::mks::Hz> _odr) {
                    return units::Quantity<scalar_t, units::mks::Hz>(this->set_odr(_odr.value()));
                }

                auto datarate() {
                    return units::Quantity<scalar_t, units::mks::Hz>(this->get_odr());
                }

                auto lowpass(units::Quantity<scalar_t, units::mks::Hz> _freq) {
                    return units::Quantity<scalar_t, units::mks::Hz>(this->set_lpf(_freq.value()));
                }

                auto lowpass() {
                    return units::Quantity<scalar_t, units::mks::Hz>(this->get_lpf());
                }

                auto highpass(units::Quantity<scalar_t, units::mks::Hz> _freq) {
                    return units::Quantity<scalar_t, units::mks::Hz>(this->set_hpf(_freq.value()));
                }

                auto highpass() {
                    return units::Quantity<scalar_t, units::mks::Hz>(this->get_hpf());
                }

            protected:
                value_t value() const { // TODO: DECIDE IF THIS SHOULD BE PUBLIC
                    return A_ * (v - o);
                }

                Owner& owner_;
                transform_t G;
                const transform_t& R;
                const value_t& v;
                value_t o;
                transform_t A_;
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
    class Derived,
    class Value,
    class AccelImpl,
    size_t N = 3,
    class AccelUnits = units::mks::m_per_s2
>
class Accelerometer : public Inertial<Accelerometer<Derived, Value, AccelImpl, N, AccelUnits>, Value, N>
{
    protected:
        friend class Inertial<Accelerometer<Derived, Value, AccelImpl, N, AccelUnits>, Value, N>;
        using base_t = Inertial<Accelerometer<Derived, Value, AccelImpl, N, AccelUnits>, Value, N>;
        using accelerometer_proxy_t = typename base_t::template Proxy<Derived, AccelUnits, AccelImpl>;
        typename base_t::value_t accel_raw_;

    public:
      template<class... Args>
        Accelerometer(Args... args)
            : accelerometer(
                  static_cast<Derived&>(*this),
                  this->R, accel_raw_, args...
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
    class GyroImpl,
    size_t N = 3,
    typename GyroUnits = units::mks::rad_per_s
>
class Gyroscope : public Inertial<Gyroscope<Derived, Value, GyroImpl, N, GyroUnits>, Value, N>
{
    protected:
        friend class Inertial<Gyroscope<Derived, Value, GyroImpl, N, GyroUnits>, Value, N>;
        using base_t = Inertial<Gyroscope<Derived, Value, GyroImpl, N, GyroUnits>, Value, N>;
        using gyroscope_proxy_t = typename base_t::template Proxy<Derived, GyroUnits, GyroImpl>;
        typename base_t::value_t gyro_raw_;

    public:
        template<class... Args>
        Gyroscope(Args... args)
            : gyroscope(
                  static_cast<Derived&>(*this),
                  this->R, gyro_raw_, args...
              )
        {
            transformUpdate();
        }

        gyroscope_proxy_t gyroscope;

    protected:
        void transformUpdate() { gyroscope.calcA(); }
};

// Declare Magnetometer baseclass
template<
    class Derived,
    class Value,
    class MagImpl,
    size_t N = 3,
    class MagUnits = units::mks::T
>
class Magnetometer : public Inertial<Magnetometer<Derived, Value, MagImpl, N, MagUnits>, Value, N>
{
    protected:
        friend class Inertial<Magnetometer<Derived, Value, MagImpl, N, MagUnits>, Value, N>;
        using base_t = Inertial<Magnetometer<Derived, Value, MagImpl, N, MagUnits>, Value, N>;
        using magnetometer_proxy_t = typename base_t::template Proxy<Derived, MagUnits, MagImpl>;
        typename base_t::value_t mag_raw_;

    public:
      template<class... Args>
        Magnetometer(Args... args)
            : magnetometer(
                  static_cast<Derived&>(*this),
                  this->R, mag_raw_, args...
              )
        {
            transformUpdate();
        }

        magnetometer_proxy_t magnetometer;

    protected:
        void transformUpdate() { magnetometer.calcA(); }
};

// Declare AccelGyro baseclass
template<
    typename Derived,
    typename Value,
    class AccelImpl,
    class GyroImpl,
    size_t N = 3,
    typename AccelUnits = units::mks::m_per_s2,
    typename GyroUnits = units::mks::rad_per_s
>
class AccelGyro : public Inertial<AccelGyro<Derived, Value, AccelImpl, GyroImpl, N, AccelUnits, GyroUnits>, Value, N>
{
    protected:
        friend class Inertial<AccelGyro<Derived, Value, AccelImpl, GyroImpl, N, AccelUnits, GyroUnits>, Value, N>;
        using base_t = Inertial<AccelGyro<Derived, Value, AccelImpl, GyroImpl, N, AccelUnits, GyroUnits>, Value, N>;
        using accelerometer_proxy_t = typename base_t::template Proxy<Derived, AccelUnits, AccelImpl>;
        using gyroscope_proxy_t = typename base_t::template Proxy<Derived, GyroUnits, GyroImpl>;
        typename base_t::value_t accel_raw_;
        typename base_t::value_t gyro_raw_;

    public:
        template<class... Args>
        AccelGyro(Args... args)
            : accel_raw_{1, 0, 0}, gyro_raw_{6.283185, 0, -3.14159},
              accelerometer(
                  static_cast<Derived&>(*this),
                  this->R, accel_raw_, args...
              ),
              gyroscope(
                  static_cast<Derived&>(*this),
                  this->R, gyro_raw_, args...
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
template<
    typename Derived,
    typename Value,
    class AccelImpl,
    class MagImpl,
    size_t N = 3,
    typename AccelUnits = units::mks::m_per_s2,
    typename MagUnits = units::mks::T
>
class AccelMag : public Inertial<AccelMag<Derived, Value, AccelImpl, MagImpl, N, AccelUnits, MagUnits>, Value, N>
{
    protected:
        friend class Inertial<AccelMag<Derived, Value, AccelImpl, MagImpl, N, AccelUnits, MagUnits>, Value, N>;
        using base_t = Inertial<AccelMag<Derived, Value, AccelImpl, MagImpl, N, AccelUnits, MagUnits>, Value, N>;
        using accelerometer_proxy_t = typename base_t::template Proxy<Derived, AccelUnits, AccelImpl>;
        using magnetometer_proxy_t = typename base_t::template Proxy<Derived, MagUnits, MagImpl>;
        typename base_t::value_t accel_raw_;
        typename base_t::value_t mag_raw_;

    public:
        template<class... Args>
        AccelMag(Args... args)
            : accel_raw_{}, mag_raw_{},
              accelerometer(
                  static_cast<Derived&>(*this),
                  this->R, accel_raw_, args...
              ),
              magnetometer(
                  static_cast<Derived&>(*this),
                  this->R, mag_raw_, args...
              )
        {
            transformUpdate();
        }

        accelerometer_proxy_t accelerometer;
        magnetometer_proxy_t magnetometer;

    protected:
        void transformUpdate() {
            accelerometer.calcA();
            magnetometer.calcA();
        }
};

// Declare AccelGyroMag baseclass
template<
    typename Derived,
    typename Value,
    class AccelImpl,
    class GyroImpl,
    class MagImpl,
    size_t N = 3,
    typename AccelUnits = units::mks::m_per_s2,
    typename GyroUnits = units::mks::rad_per_s,
    typename MagUnits = units::mks::T
>
class AccelGyroMag : public Inertial<AccelGyroMag<Derived, Value, AccelImpl, GyroImpl, MagImpl, N, AccelUnits, GyroUnits, MagUnits>, Value, N>
{
    protected:
        friend class Inertial<AccelGyroMag<Derived, Value, AccelImpl, GyroImpl, MagImpl, N, AccelUnits, GyroUnits, MagUnits>, Value, N>;
        using base_t = Inertial<AccelGyroMag<Derived, Value, AccelImpl, GyroImpl, MagImpl, N, AccelUnits, GyroUnits, MagUnits>, Value, N>;
        using accelerometer_proxy_t = typename base_t::template Proxy<Derived, AccelUnits, AccelImpl>;
        using gyroscope_proxy_t = typename base_t::template Proxy<Derived, GyroUnits, GyroImpl>;
        using magnetometer_proxy_t = typename base_t::template Proxy<Derived, MagUnits, MagImpl>;
        typename base_t::value_t accel_raw_;
        typename base_t::value_t gyro_raw_;
        typename base_t::value_t mag_raw_;

    public:
        template<class... Args>
        AccelGyroMag(Args... args)
            : accel_raw_{}, gyro_raw_{}, mag_raw_{},
              accelerometer(
                  static_cast<Derived&>(*this),
                  this->R, accel_raw_, args...
              ),
              gyroscope(
                  static_cast<Derived&>(*this),
                  this->R, gyro_raw_, args...
              ),
              magnetometer(
                  static_cast<Derived&>(*this),
                  this->R, mag_raw_, args...
              )
        {
            transformUpdate();
        }

        accelerometer_proxy_t accelerometer;
        gyroscope_proxy_t gyroscope;
        magnetometer_proxy_t magnetometer;

    protected:
        void transformUpdate() {
            accelerometer.calcA();
            gyroscope.calcA();
            magnetometer.calcA();
        }
};
} /*namespace drivers*/
} /*namespace chandra*/

#endif /*CHANDRA_INERTIAL_CRTP_H*/
