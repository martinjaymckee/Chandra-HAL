#ifndef CHANDRA_KALMAN_H
#define CHANDRA_KALMAN_H

namespace Chandra
{
namespace control
{
namespace detail
{
// Base for state variables
template<class Value, uint8_t StateSize>
class KalmanFilterStateBase
{

};

// Base for measurement variables
template<class Value, uint8_t MeasurementSize>
class KalmanFilterMeasurementBase
{

};

// Base for input variables
template<class Value, uint8_t InputSize>
class KalmanFilterInputBase
{

};

template<class Value>
class KalmanFilterInputBase<Value, 0>
{

};

// Base for calculation core

template<class Value, uint8_t StateSize, uint8_t MeasurementSize, uint8_t InputSize>
class KalmanFilterBase
{

};

template<class Value, uint8_t StateSize, uint8_t MeasurementSize>
class KalmanFilterBase<Value, StateSize, MeasurementSize, 0>
{

};
} /*namespace detail*/

template<class Value, uint8_t StateSize, uint8_t MeasurementSize, uint8_t InputSize=0>
class KalmanFilter : public detail::KalmanFilterBase<Value, StateSize, MeasurementSize, InputSize>
{

};

} /*namespace control*/
} /*namespace chandra*/

#endif /*CHANDRA_KALMAN_H*/
