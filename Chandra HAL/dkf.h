#ifndef CHANDRA_DKF_H
#define CHANDRA_DKF_H

#include <Eigen/Core>

namespace chandra
{
namespace control
{

template<class Value, uint32_t States, uint32_t Measurements, uint32_t Inputs=0>
class DiscreteKalmanFilter
{
  public:
    using value_t = Value;
    using StateVector = Eigen::Matrix<value_t, States, 1>;
    using StateCovarainceMatrix = Eigen::Matrix<value_t, States, States>;
    using ProcessMatrix = Eigen::Matrix<value_t, States, States>;
    using MeasurementVector = Eigen::Matrix<value_t, Measurements, 1>;
    using MeasurementMatrix = Eigen::Matrix<value_t, Measurments, States>;
    using MeasurementCovarianceMatrix = Eigen::Matrix<value_t, Measurement, Measurement>;
    using ControlVector = Eigen::Matrix<value_t, Inputs, 1>;
    using ControlMatrix = Eigen::Matrix<value_t, States, Inputs>;
    using KalmanGainMatrix = Eigen::Matrix<value_t, States, Measurements>;
};

} /* namespace control */
} /* namespace chandra */

#endif /*CHANDRA_DKF_H*/
