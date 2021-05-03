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
      // Number of steps
      // Number of samples
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

    struct CalCompleteResult
    {
      // accel calib
      // accel sd
      // gyro calib
      // gyro sd
      // mag calib
      // mag sd
    };

    // Constructor (imu, gravity, mag, Number of samples=10)
    IMUCalibrator(imu_t& _imu, gravity_t& _gravity)
      : imu_{_imu}, gravity_{_gravity} {}

    // Begin Calibration (samples)
    InitResult init(const size_t& _N=10) {
      N_ = _N;
      // Set To First Step
      // Initialize Step Storage
      // Get First Target Orientation
      return {};
    }

    // Calibrate Step (*Per-sample function, *reference orientation)
    // PerSampleFunc(step, sample, accel, gyro, mag)
    template<class PerSampleFunc>
    CalStepResult step(const PerSampleFunc& _func) {
      // Create sample buffer
      for(size_t idx = 0; idx < N_; ++idx) {
        // measure IMU (accel/gyro/mag)
        const auto accel = 0;
        const auto gyro = 0;
        const auto mag = 0;
        _func(step_, idx, accel, gyro, mag);
        // Add IMU measurements to sample buffer
      }
      // Store reference orientation
      // Calculate mean and sd from sample buffer
      return {};
    }

    CalStepResult step() {
      return step([](size_t, size_t, auto, auto, auto,){});
    }

    // Complete Calibration ()
    CalCompleteResult calibration(const bool& _apply=true) {
      // ***using reference orientations and samples***
      // Calculate the acceleration calibration
      // Calculate the gyro calibration
      // Calculate the magnetometer calibration
      if(_apply) {
        // Apply the calibration to the imu object
      }
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
