#ifndef CHANDRA_MOCK_IMU_H
#define CHANDRA_MOCK_IMU_H

#include <iostream>
#include <vector>
using namespace std;

#include "../inertial.h"

namespace chandra
{
namespace drivers
{
template<typename Value>
struct MockIMUState
{
        using vector_t = math::Matrix<Value, 3, 1>;

        MockIMUState() : t(0), accel(0), gyro(0), valid(false) {}

        MockIMUState(Value _t, vector_t _accel, vector_t _gyro)
            : t(_t), accel(_accel), gyro(_gyro), valid(true) {}

        MockIMUState(const MockIMUState<Value>& _other)
            : t(_other.t), accel(_other.accel), gyro(_other.gyro), valid(_other.valid){}

        MockIMUState<Value>& operator = (const MockIMUState<Value>& _other) {
            t = _other.t;
            accel = _other.accel;
            gyro = _other.gyro;
            valid = _other.valid;
            return *this;
        }

        Value t;
        vector_t accel;
        vector_t gyro;
        bool valid;
};

template<typename Stream, typename Value>
Stream& operator << (Stream& _stream, const MockIMUState<Value>& _state) {
    _stream << "t = " << _state.t;
    _stream << ", accel = " << _state.accel.T();
    _stream << ", gyro = " << _state.gyro.T();
    return _stream;
}

template<typename Value>
class MockIMU : public AccelGyro<Value, 3>
{
    protected:
        using base_t = AccelGyro<Value, 3>;
        typename base_t::value_t accel_offset_;
        typename base_t::value_t gyro_offset_;
        typename base_t::value_t accel_gain_;
        typename base_t::value_t gyro_gain_;
        Value accel_sd_;
        Value gyro_sd_;
        std::vector<MockIMUState<Value>>& flight_;
        MockIMUState<Value> imu_state_;
        size_t state_idx_;
        Value t_;

    public:
        MockIMU(std::vector<MockIMUState<Value>>& _flight)
            : accel_offset_(9.81*40e-3), gyro_offset_(0.035),
              accel_gain_(0.5), gyro_gain_(1),
              accel_sd_(9.81*5e-3), gyro_sd_(1.31e-3),
              flight_(_flight), state_idx_(0), t_(0) {
            std::mt19937 generator(std::random_device{}());
            std::normal_distribution<Value> distribution(0.0, 9.81*40e-3);
            for(size_t row=0; row < base_t::value_t::rows; ++row){
                accel_offset_(row) = distribution(generator);
            }
            distribution = std::normal_distribution<Value>(0.0, 0.035);
            for(size_t row=0; row < base_t::value_t::rows; ++row){
                gyro_offset_(row) = distribution(generator);
            }
            distribution = std::normal_distribution<Value>(1.0, 0.01);
            for(size_t row=0; row < base_t::value_t::rows; ++row){
                accel_gain_(row) = distribution(generator);
            }
            cout << "Created a Mock IMU Object.  Configured with:\n";
            cout << "\tAccel Offset = " << accel_offset_.T() << ", s.d. = " << accel_sd_ << "\n";
            cout << "\tAccel Gain = " << accel_gain_.T() << "\n";
            cout << "\tGyro Offset = " << gyro_offset_.T() << ", s.d. = " << gyro_sd_ << "\n";
            cout << "\tAccel Gain = " << gyro_gain_.T() << "\n";
            cout << "\tFlight Config with " << flight_.size() << " states\n";

            /*cout << "\n\tFlight Config:\n";
            for(auto state: flight_) {
                cout << "\t\t" << state << "\n";
            }
            cout << "\n";*/
        }

        // THIS IS SPECIFIC TO THE MOCK OBJECT TO MAKE TIMEBASED TESTING EASIER
        Value setTime(Value _t) {
            t_ = _t;
            return t_;
        }

        // RETURNS TRUE IF NEW VALUES ARE AVAILABLE (possible to attempt to "force" a fresh read with the parameter)
        bool update(bool = false) {
            std::mt19937 generator(std::random_device{}());
            std::normal_distribution<Value> distribution;

            const auto state = getState();
            this->accel_raw_ = (chandra::math::emul(accel_gain_, state.accel) + accel_offset_);
            distribution = std::normal_distribution<Value>(0.0, accel_sd_);
            for(size_t row = 0; row < base_t::value_t::rows; ++row) {
                this->accel_raw_(row) += distribution(generator);
            }
            this->gyro_raw_ = chandra::math::emul(gyro_gain_, state.gyro) + gyro_offset_;
            distribution = std::normal_distribution<Value>(0.0, gyro_sd_);
            for(size_t row = 0; row < base_t::value_t::rows; ++row) {
                this->gyro_raw_(row) += distribution(generator);
            }
            return true;
        }

    protected:
        size_t nextIndex(size_t _idx) { return min(flight_.size() - 1, _idx+1); }

        MockIMUState<Value> nextState(size_t _idx) {
            return flight_[nextIndex(_idx)];
        }

        MockIMUState<Value> interpolateStates(
                auto t,
                const MockIMUState<Value> state_a,
                const MockIMUState<Value> state_b
        ) {
            if(state_a.t == state_b.t) return state_a;

            const auto t_range = state_b.t - state_a.t;
            const auto t_before = state_b.t - t;
            const auto e = t_before / t_range;
            const auto accel = (e * state_a.accel) + ((1.0-e) * state_b.accel);
            const auto gyro = (e * state_a.gyro) + ((1.0-e) * state_b.gyro);
            return {t, accel, gyro};
        }

        MockIMUState<Value> filterStates(
                auto e,
                const MockIMUState<Value> state_a,
                const MockIMUState<Value> state_b
        ) {
            const auto accel = (e * state_a.accel) + ((1.0-e) * state_b.accel);
            const auto gyro = (e * state_a.gyro) + ((1.0-e) * state_b.gyro);
            return {state_b.t, accel, gyro};
        }

        MockIMUState<Value> getState() {
            MockIMUState<Value> current_state = flight_[state_idx_];
            MockIMUState<Value> next_state = flight_[state_idx_];
            bool found = false;
            while(!found) {
                next_state = nextState(state_idx_);
                if(t_ >= next_state.t) {
                    current_state = next_state;
                    auto next_idx = nextIndex(state_idx_);
                    if(state_idx_ == next_idx) found = true;
                    state_idx_ = next_idx;
                } else {
                    found = true;
                }
            }

            const auto interp_state = interpolateStates(t_, current_state, next_state);
            imu_state_ = (imu_state_.valid) ?
                        filterStates(0.5, imu_state_, interp_state) :
                        interp_state;
            return imu_state_;
        }

};
} /*namespace drivers*/
} /*namespace chandra*/

#endif /*CHANDRA_MOCK_IMU_H*/

