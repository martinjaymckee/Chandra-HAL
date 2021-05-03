#ifndef CHANDRA_IMU_CALIBRATE_H
#define CHANDRA_IMU_CALIBRATE_H

namespace chandra
{
namespace control
{

class IMUCal
{
  public:
    enum calibration_mode_t {
      Cubic,
      CubicOrthagonal,
      Tetrahedral,
      Invalid
    };

    enum accel_calibration_t
    {
      ThreeParameter,
      SixParameter,
      NineParameter,
      TwelveParameter
    };
}

namespace internal
{
template<IMUCal::calibration_mode_t Mode>
class CalibratorConfiguration
{
  public:


};

} /*namespace internal*/

template<class IMUType, class Gravity, class Magnetism, ImuCal::calibration_mode_t Mode>
class IMUCalibrator
{
  public:
    using imu_t = IMUType;
    using value_t = typename IMUType::value_t;
    using gravity_t = Gravity;
    using magnetism_t = Magnetism;
    using configuration_t = internal::CalibratorConfiguration<Mode>;

    struct InitResult
    {
      // Initial target orientation
    };

    struct CalStepResult
    {
      // step #
      // Next target orientation
      // accel mean / accel sd
      // gyro mean / gyro sd
      // mag mean / mag sd
    };

    struct CalCompleteResult {};

    // Constructor (imu, gravity, mag, Number of samples=10)
    IMUCalibrator(imu_t& _imu, gravity_t& _gravity, const size_t& _N=10)
      : imu_{_imu}, gravity_{_gravity}, N_{_N} {}
    // Begin Calibration ()
    InitResult init() {
      return {};
    }

    // Calibrate Step (*Per-sample function, *reference orientation)
    // PerSampleFunc(step, sample, accel, gyro, mag)
    template<class PerSampleFunc>
    CalStepResult step(const PerSampleFunc& _func) {
      (void) _func;
      return {};
    }

    CalStepResult step() {
      return step([](size_t, size_t, auto, auto, auto,){});
    }

    // Complete Calibration ()
    CalCompleteResult calibration() {
      return {};
    }

  protected:
    imu_t& imu_;
    gravity_t& gravity_;
    size_t N_;
    configuration_t config_;
};

} /*namespace control*/
} /*namespace chandra*/

#endif /*CHANDRA_IMU_CALIBRATE_H*/
