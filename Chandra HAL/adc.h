/*
 * adc.h
 *
 *  Created on: Jun 17, 2016
 *      Author: martin
 */

#ifndef CHANDRA_ADC_H
#define CHANDRA_ADC_H
#include <chrono>
using namespace std::chrono_literals;

#if defined(__LPC82X__) || defined(__LPC15XX__)
#include <chip.h>
#elif defined(__LPC84X__)
#include <LPC8xx.h>
#else
#error "Undefined processor type for USART implementation."
#endif

#include "chrono.h"
#include "chip_utils.h"

namespace chandra
{
namespace io
{

//
// AT THE MOMENT, THIS IS NOT TAKING FULL ADVANTAGE OF THE ADC PERIPHERAL'S CAPABILITIES.  IT WOULD BE GOOD
//	TO MAKE THIS USE TRIGGERS AND SO FORTH.
//

class ADC
{
    public:
        //
        // ADC Channel Proxy Class
        //
        class ADCChannel
        {
            public:
                ADCChannel(ADC& _adc, const uint8_t& _chan, const bool& _enable = true  ) : adc_(_adc), chan_(_chan), mask_(1UL<<_chan) {
                    if(_enable) enable(true);
                }

                bool enable( const bool& _enabled = true) {
                    #if defined(__LPC82X__)
                        const auto bit_offset = 13;
                    #elif defined(__LPC84X__)
                        const auto bit_offset = 14;
                    #elif defined(__LPC15XX__)
                        const auto bit_offset = (chan_ == 0) ? 0 : 12; // TODO: CHECK THIS
                    #endif
                    FixedFunctionIO::enable(0, chan_ + bit_offset, _enabled); // TODO: MAKE AN ADC WRAPPER CLASS FOR THIS???

                    #if defined(__LPC82X__) || defined(__LPC15XX__)
                    if( _enabled ) {
                        adc_.adc_.SEQ_CTRL[0] |= (1<<18) | mask_;
                    } else {
                        adc_.adc_.SEQ_CTRL[0] &= ~mask_;
                    }
                    #elif defined(__LPC84X__)
                    if( _enabled ) {
                        adc_.adc_.SEQA_CTRL |= (1<<18) | mask_;
                    } else {
                        adc_.adc_.SEQA_CTRL &= ~mask_;
                    }
                    #endif
                    return _enabled;
                }

                bool enabled() const {
                    #if defined(__LPC82X__)
                        const auto bit_offset = 13;
                    #elif defined(__LPC84X__)
                        const auto bit_offset = 14;
                    #elif defined(__LPC15XX__)
                        const auto bit_offset = (chan_ == 0) ? 0 : 12; // TODO: CHECK THIS
                    #endif

                    return FixedFunctionIO::enabled(0, chan_ + bit_offset);
                }

                uint8_t channel() const { return chan_; }

                template<class T>
                operator T () const {
                    #if defined(__LPC82X__) || defined(__LPC15XX__)
                    return static_cast<T>(adc_.adc_.DR[chan_]&0xFFFF);
                    #elif defined(__LPC84X__)
                    return static_cast<T>(adc_.adc_.DAT[chan_]&0xFFFF);
                    #endif
                }

                uint16_t raw() const { return this->operator uint16_t(); }

            private:
                ADC& adc_;
                uint8_t chan_;
                uint16_t mask_;
        };

        #if defined(__LPC82X__) || defined(__LPC15XX__)
        using adc_peripheral_t = LPC_ADC_T;
        #elif defined(__LPC84X__)
        using adc_peripheral_t = LPC_ADC_TypeDef;
        #else
        #error "ADC peripheral not defined for this processor type"
        #endif

        //
        // ADC Block Implementation
        //
        ADC(const uint8_t& _num) : adc_(getADC(_num)), num_(_num) {
            switch(num_) {
                #if defined(__LPC82X__) || defined(__LPC84X__)
                    default:
                    case 0:
                        SystemClock::enable(0, 24);
                        PeripheralActivity::reset(0, 24);
                        PowerConfiguration::enable(0, 4);
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

        bool init() { // TODO: THIS SHOULD BE CHANGED TO ACTUALLY INITIALIZE INTO THE CORRECT MODE ( INCLUDING TRIGGER )
            setADCClockDiv( chandra::chrono::frequency::main().value() ); // Defaults to the maximum allowable clock
            #if defined(__LPC82X__) || defined(__LPC15XX__)
            adc_.SEQ_CTRL[0] |= (0b11<<30); // Enable the Sequence and Set to "End-Of-Sequence" Mode
            #elif defined(__LPC84X__)
            LPC_SYSCON->PDRUNCFG &= ~(1<<4);
            adc_.SEQA_CTRL |= (0b11<<30);
            #endif
            calibrate();

            return valid();
        }

        uint8_t num() const { return num_; }

        ADCChannel operator [] ( const uint8_t _chan ) { return ADCChannel(*this, _chan); }

        bool valid() const { return true; } // TODO: THIS NEEDS TO BE IMPLEMENTED

        bool calibrate(bool _blocking = true) {
            const uint32_t ctrl = adc_.CTRL;
            const uint32_t div = (chandra::chrono::frequency::adc(num_).value() / 500000UL) - 1UL;
            if( div > 255 ) return false;

            adc_.CTRL = (1<<30) | div;

            if( _blocking ) {
                while( (adc_.CTRL & (1<<30)) == (1<<30)) {} // Loop until calibration done
                adc_.CTRL = ctrl; // Reset Control Register if blocking
            }

            return static_cast<bool>((adc_.CTRL & (1<<30)) == 0);
        }

        void sample(const bool& _blocking=false) { // NOTE: THE CURRENT BLOCKING IMPLEMENTATION IS A MAJOR HACK....
            #if defined(__LPC82X__) || defined(__LPC15XX__)
            adc_.SEQ_CTRL[0] |= (1<<26); // Enable the Sequence and Set to "End-Of-Sequence" Mode
            #elif defined(__LPC84X__)
            adc_.SEQA_CTRL |= (1<<26);
            #endif
            if(_blocking) chandra::chrono::delay(100us);
        }

        void burst() {
            #if defined(__LPC82X__) || defined(__LPC15XX__)
            adc_.SEQ_CTRL[0] |= (1<<27);
            #elif defined(__LPC84X__)
            adc_.SEQA_CTRL |= (1<<27);
            #endif
        } // This may be a decent way to do this, but it's not clear yet

    protected:
        static adc_peripheral_t& getADC(const uint8_t& _num) {
            switch(_num) {
                #if defined(__LPC82X__)
                default:
                case 0:
                    return *LPC_ADC;
                #elif defined(__LPC84X__)
                default:
                case 0:
                    return *LPC_ADC;
                #elif defined(__LPC15XX__)
                case 1:
                    return *LPC_ADC1;
                default:
                case 0:
                    return *LPC_ADC0;
                #endif
            }
        }

        uint32_t setADCClockDiv( const uint32_t& _f_cpu, const uint32_t& _f_adc ) {
            const uint32_t f_adc = (_f_adc > maximumADCClock()) ? maximumADCClock() : _f_adc;
            const uint32_t div = (_f_cpu / f_adc) - 1UL;
            if( div > 255 ) return 0;
            adc_.CTRL = (adc_.CTRL&0xFFFFF00) | div;
            return (_f_cpu + ( (div+1) / 2 ) ) / (div+1);
        }

        uint32_t setADCClockDiv( const uint32_t& _f_cpu ) {
            return setADCClockDiv(_f_cpu, maximumADCClock());
        }

        static uint32_t maximumADCClock() {
            #if defined(__LPC82X__) || defined(__LPC84X__) // TODO: CHECK 84X MAXIMUM CLOCK
                return 30000000UL;
            #elif defined(__LPC15XX__)
                return 50000000UL;
            #endif
        }

    private:
        adc_peripheral_t& adc_;
        uint8_t num_;
};

} /*namespace io*/
} /*namespace chandra*/

#endif /*CHANDRA_ADC_H*/


