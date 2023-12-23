/*
 * adc.h
 *
 *  Created on: Jun 17, 2016
 *      Author: martin
 */

#ifndef CHANDRA_ADC_H
#define CHANDRA_ADC_H
#include <chrono>
#include <limits>
// TODO: DECIDE IF THIS IS THE CORRECT PLACE TO DO THIS.  IS IT BETTER TO DO THS INSIDE THE CHANDRA NAMESPACE?
using namespace std::chrono_literals;

#if defined(__LPC82X__) || defined(__LPC15XX__)
#include <chip.h>
#elif defined(__LPC84X__)
#include <LPC8xx.h>
#else
#error "Undefined processor type for ADC implementation."
#endif

#include "chrono.h"
#include "chip_utils.h"
//#include "unitcs_mks.h"
//using namespace chandra::units::mks;

//
// TODO: THIS NEEDS TO HAVE A QUANTITY CONVERSION FUNCTIONALITY ADDED TO THE ADC.  THE MOST BASIC FORMAT SHOULD
// 	PROBABLY BE SOMETHING LIKE ADCCHANNEL::CONVERTER<QUANTITY>(GAIN,*OFFSET) WHERE QUANTITY DEFINES BOTH THE VALUE
//	TYPE AS WELL AS THE UNITS, GAIN IS A SCALAR QUANTITY (NOT UNITS CORRECTED....), AND THE OFFSET *IS* TO BE UNITS
//	CORRECT.  THIS IS THE CLEANEST FORMAT BUT IT ISN'T AS SAFE AS REQUIRING EVERYTHING TO BE UNITS CORRECT.... I DON'T
//	KNOW IF THE CORRECTNESS IS WORTH THE TROUBLE.
//
//	GAIN CONVERTS FROM ADC INPUT IN VOLTS TO THE OUTPUT QUANTITY AND THEREFORE HAS UNITS OF (OUTPUT UNITS) / VOLT.
//	HONESTLY, IF THERE IS A GOOD WAY TO MAKE CREATE GOOD ERROR MESSAGES FOR INCORRECT PARAMETERS, IT IS BETTER TO PUT
//
//

namespace chandra
{
namespace io
{
//
// ADC ADCSources
//
enum class ADCSource
{
	Pin = 0x00,
	CoreVoltage = 0x01,
	InternalReference = 0x02,
	Temperature = 0x03,
	HalfRail = 0x04
};

//
// AT THE MOMENT, THIS IS NOT TAKING FULL ADVANTAGE OF THE ADC PERIPHERAL'S CAPABILITIES.  IT WOULD BE GOOD
//	TO MAKE THIS USE TRIGGERS AND SO FORTH.
//
template<typename Value = float>
class ADC
{
    public:
		using value_t = Value;
        #if defined(__LPC82X__) || defined(__LPC15XX__)
        using adc_peripheral_t = LPC_ADC_T;
        #elif defined(__LPC84X__)
        using adc_peripheral_t = LPC_ADC_TypeDef;
        #else
        #error "ADC peripheral not defined for this processor type"
        #endif

        //
        // ADC Channel Proxy Class
        //
        class ADCChannel
        {
            public:
								template<class V>
								class ADCChannelResults
								{
										public:
											ADCChannelResults(const bool& _updated, const V& _value) :
												updated(_updated), value(_value) {}

											template<class V2>
											ADCChannelResults(const ADCChannelResults<V2>& _other) :
												updated(_other.updated),
												value(static_cast<V>(_other.value)) {}

											operator bool() const { return updated; }

											template<class T>
											operator T() const { return static_cast<T>(value); }

											bool updated{false};
											V value{0};
								};

                using raw_value_t = uint16_t;

                ADCChannel(ADC& _adc, const uint8_t& _chan, const bool& _enable = true  ) : adc_(_adc), chan_(_chan), mask_(1UL<<_chan) {
                    if(_enable) enable(true);
                }

                bool enable(
                    const bool& _enabled = true,
                    const ADCSource& _src = ADCSource::Pin)
                {
                    src(_src);

                    #if defined(__LPC15XX__)
                    if( _enabled ) {
                        adc_.adc_->SEQ_CTRL[0] |= mask_;
                    } else {
                        adc_.adc_->SEQ_CTRL[0] &= ~mask_;
                    }
										#elif defined(__LPC82X__)
										static_assert(false, "ADCChannel::enable() is undefined for LPC824");
										// TODO: IMPLEMENT FOR 82X
                    #elif defined(__LPC84X__)
                    if( _enabled ) {
                        adc_.adc_->SEQA_CTRL |= (1<<18) | mask_;
                    } else {
                        adc_.adc_->SEQA_CTRL &= ~mask_;
                    }
                    #endif
                    return _enabled;
                }

                bool channelEnabled() const {
                    #if defined(__LPC82X__) || defined(__LPC15XX__)
                        return adc_.adc_->SEQ_CTRL[0] & mask_;
                    #elif defined(__LPC84X__)
                        return adc_.adc_->SEQA_CTRL & mask_;
                    #endif
                }

                bool enabled() const {
                    return adc_.enabled() && channelEnabled();
                }

                bool src(const ADCSource& _src) {
                    if(_src == ADCSource::Pin) {
                        enablePin(true);
                        src_ = _src;
                        return true;
                    } else if(chan_ != 0){
                         return false;
                    }

										enablePin(false);
                #if defined(__LPC15XX__)
                    adc_.adc_->INSEL = uint32_t(_src);
				#else
                    return false;
                #endif
                    src_ = _src;
                    return true;
                }

                uint8_t channel() const { return chan_; }
                ADCSource src() const { return src_; }

                static constexpr value_t min() noexcept { return Value{0}; }
//                static constexpr value_t max() noexcept { return Value{0xFFF0}; }
								static constexpr value_t max() noexcept { return Value{0xFFF}; }

								ADCChannelResults<value_t> operator () () {
									const auto raw_results = this->raw();
//									const auto val_max = max();
									const value_t value = ((adc_.vref_*raw_results.value)/max());
									return {raw_results.updated, value};
								}

								ADCChannelResults<raw_value_t> raw() const {
										#if defined(__LPC82X__) || defined(__LPC15XX__)
										const auto data = adc_.adc_->DR[chan_];
										#elif defined(__LPC84X__)
										const auto data = adc_.adc_->DAT[chan_];
										#endif
										const uint16_t raw_data = ((data>>4)&0xFFF);
										return {bool(data&(1<<31)), raw_data};
								}

						protected:
                bool enablePin(const bool& _enable) {
                    #if defined(__LPC82X__)
                        const auto bit_offset = 13;
                    #elif defined(__LPC84X__)
                        const auto bit_offset = 14;
                    #elif defined(__LPC15XX__)
                        const auto bit_offset = adc_.num() * 12;
                    #endif
                    FixedFunctionIO::enable(0, chan_ + bit_offset, _enable); // TODO: MAKE AN ADC WRAPPER CLASS FOR THIS???
                    return true;
                }

            private:
                ADC<value_t>& adc_;
                uint8_t chan_;
                uint16_t mask_;
                ADCSource src_;
        };

        //
        // ADC Block Implementation
        //
        ADC(const uint8_t& _num, const value_t& _vref)
					: adc_(getADC(_num)), num_(_num), vref_(_vref) {
            switch(num_) {
                #if defined(__LPC82X__) || defined(__LPC84X__)
                    default:
                    case 0:
                        SystemClock::enable(0, 24);
                        PeripheralActivity::reset(0, 24);
                        PowerConfiguration::enable(0, 4);
												LPC_SYSCON->ADCCLKDIV = 1;                 // Enable clock, and divide-by-1 at this clock divider
											  LPC_SYSCON->ADCCLKSEL = 0; // Use fro_clk as source for ADC async clock
                        break;
                #elif defined(__LPC15XX__)
                    case 0:
                        SystemClock::enable(0, 27);
                        PeripheralActivity::reset(0, 27);
                        PowerConfiguration::enable(0, 10);
                        break;

                    case 1:
                        SystemClock::enable(0, 28);
                        PeripheralActivity::reset(0, 28);
                        PowerConfiguration::enable(0, 11);
                        break;
                #endif
            }
        }

        // TODO: THIS SHOULD BE CHANGED TO ACTUALLY INITIALIZE INTO THE CORRECT MODE ( INCLUDING TRIGGER )
        bool init( const chandra::chrono::frequency::rep& _f_adc = maximumADCClock()) {
            setADCClockDiv(_f_adc); // Defaults to the maximum allowable clock
            #if defined(__LPC82X__)
            adc_->SEQ_CTRL[0] |= (0b11<<30); // Enable the Sequence and Set to "End-Of-Sequence" Mode
            #elif defined(__LPC15XX__)
            adc_->SEQ_CTRL[0] |= (0b11<<30); // Enable the Sequence and Set to "End-Of-Sequence" Mode
            #elif defined(__LPC84X__)
            adc_->SEQA_CTRL |= (0b11<<30);
						adc_->CTRL |= (1<<31);
            #endif

            calibrate();

            return valid();
        }

        uint8_t num() const { return num_; }

        ADCChannel operator [] ( const uint8_t _chan ) { return ADCChannel(*this, _chan); }

        bool enabled() const { return true; } // TODO: THIS NEEDS TO BE IMPLEMENTED
        bool valid() const { return true; } // TODO: THIS NEEDS TO BE IMPLEMENTED

        bool calibrate(bool _blocking = true) {
            const uint32_t ctrl = adc_->CTRL;
            const uint32_t div = calcADCClockDiv(
							500000UL,
							chandra::chrono::frequency::adc(num_).value()
						) - 1UL;

            adc_->CTRL = (1<<31) | (1<<30) | div;

            if( _blocking ) {
                while( (adc_->CTRL & (1<<30)) == (1<<30)) {} // Loop until calibration done
                adc_->CTRL = ctrl; // Reset Control Register if blocking
            }

            return static_cast<bool>((adc_->CTRL & (1<<30)) == 0);
        }

        void sample(const bool& _blocking=false) { // NOTE: THE CURRENT BLOCKING IMPLEMENTATION IS A MAJOR HACK....
            #if defined(__LPC82X__) || defined(__LPC15XX__)
            adc_->SEQ_CTRL[0] |= (1<<26); // Enable the Sequence and Set to "End-Of-Sequence" Mode
            #elif defined(__LPC84X__)
            adc_->SEQA_CTRL |= (1<<26);
            #endif
            if(_blocking) chandra::chrono::delay(100us);
        }

        void burst() {
            #if defined(__LPC82X__) || defined(__LPC15XX__)
            adc_->SEQ_CTRL[0] |= (1<<27);
            #elif defined(__LPC84X__)
            adc_->SEQA_CTRL |= (1<<27);
            #endif
        } // This may be a decent way to do this, but it's not clear yet

    protected:
        static adc_peripheral_t* getADC(const uint8_t& _num) {
            switch(_num) {
                #if defined(__LPC82X__)
                default:
                case 0:
                    return LPC_ADC;
                #elif defined(__LPC84X__)
                default:
                case 0:
                    return LPC_ADC;
                #elif defined(__LPC15XX__)
                case 1:
                    return LPC_ADC1;
                default:
                case 0:
                    return LPC_ADC0;
                #endif
            }
        }

        uint32_t setADCClockDiv( const chandra::chrono::frequency::rep& _f_adc, const chandra::chrono::frequency::rep& _f_cpu ) {
            const auto f_adc = (_f_adc > maximumADCClock()) ? maximumADCClock() : _f_adc;
            const uint32_t div = calcADCClockDiv(f_adc.value(), _f_cpu.value()) - 1UL;
            adc_->CTRL = (adc_->CTRL&0xFFFFF00) | div;
            return (_f_cpu.value() + ( (div+1) / 2 ) ) / (div+1);
        }

        uint32_t setADCClockDiv( const chandra::chrono::frequency::rep& _f_adc ) {
            return setADCClockDiv(_f_adc, chandra::chrono::frequency::main());
        }

        static chandra::chrono::frequency::rep maximumADCClock() {
            #if defined(__LPC82X__) || defined(__LPC84X__)
                return chandra::chrono::frequency::rep{30000000};
            #elif defined(__LPC15XX__)
                return chandra::chrono::frequency::rep{50000000};
            #endif
        }

        static uint8_t calcADCClockDiv(
            const uint32_t& _f_adc,
            const uint32_t& _f_cpu )
        {
            const uint32_t base_div = (_f_cpu / _f_adc);
            const uint32_t div = base_div + (((base_div * _f_adc) < _f_cpu) ? 1 : 0);
            return (div > 255) ? 255 : div;
        }

    private:
        volatile adc_peripheral_t* adc_;
        uint8_t num_;
				value_t vref_;
};

} /*namespace io*/

} /*namespace chandra*/
/*
// TODO: THE STANDARD SAYS YOU SHOULDN'T DO THIS.  RATHER THAN USING THE ENTIRE STD NAMESPACE HOWEVER, THIS SEEMS
//	LIKE A BETTER OPTION.
namespace std
{
template <>
class numeric_limits<chandra::io::ADC::ADCChannel>
{
	public:
		using Value = float; // TODO: THIS IS A HACK. THIS SHOULD COME FROM THE CHANNEL TYPE
		static constexpr bool is_specialized = true;
		static constexpr Value min() noexcept { return Value{0}; }
		// TODO: THIS MAX IS BASED ON THE FACT THAT THIS IS 12-BIT SHIFTED LEFT BY 4 BITS.
		//	IF FILTERING IS ADDED TO THE ADC, THIS COULD BE THE FULL 16-BIT VALUE.  OR, IF THE
		//	CHANNEL IS CONFIGURED AS 10-BIT, IT WOULD BE EVEN SMALLER.... NOT SURE WHAT TO DO.
		static constexpr Value max() noexcept { return Value{0xFFF0}; }
		static constexpr Value lowest() noexcept { return Value{0}; }
//   static constexpr int  digits = 0;
//   static constexpr int  digits10 = 0;
		static constexpr bool is_signed = numeric_limits<Value>::is_signed;
		static constexpr bool is_integer = numeric_limits<Value>::is_integer;
		static constexpr bool is_exact = numeric_limits<Value>::is_exact;
//   static constexpr int radix = 0;
		static constexpr Value epsilon() noexcept { return Value{0}; }
		static constexpr Value round_error() noexcept { return Value{0}; }
//
//   static constexpr int  min_exponent = 0;
//   static constexpr int  min_exponent10 = 0;
//   static constexpr int  max_exponent = 0;
//   static constexpr int  max_exponent10 = 0;
//
		static constexpr bool has_infinity = numeric_limits<Value>::has_infinity;
		static constexpr bool has_quiet_NaN = numeric_limits<Value>::has_quiet_NaN;
		static constexpr bool has_signaling_NaN = numeric_limits<Value>::has_signaling_NaN;
//   static constexpr float_denorm_style has_denorm = denorm_absent;
//   static constexpr bool has_denorm_loss = false;
//   static constexpr T infinity() noexcept { return T(); }
//   static constexpr T quiet_NaN() noexcept { return T(); }
//   static constexpr T signaling_NaN() noexcept { return T(); }
//   static constexpr T denorm_min() noexcept { return T(); }
//
		static constexpr bool is_iec559 = numeric_limits<Value>::is_iec559;
		static constexpr bool is_bounded = numeric_limits<Value>::is_bounded;
		static constexpr bool is_modulo = numeric_limits<Value>::is_modulo;

		static constexpr bool traps = numeric_limits<Value>::traps;
		static constexpr bool tinyness_before = numeric_limits<Value>::tinyness_before;
//   static constexpr float_round_style round_style = round_toward_zero;
};
}*/
#endif /*CHANDRA_ADC_H*/
