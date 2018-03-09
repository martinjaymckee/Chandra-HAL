/*
 * chip_utils.h
 *
 *  Created on: Jun 14, 2016
 *      Author: martin
 */

//
// Include Implementation Dependent Chip Utilities
//
#if defined(__LPC82X__)
#include "implementation/lpc82x_chip_utils.h"
#elif defined(__LPC84X__)
#include "implementation/lpc84x_chip_utils.h"
#elif defined(__LPC15XX__)
#include "implementation/lpc15xx_chip_utils.h"
#endif


//
// Implementation Independent Chip Utilities
//
#ifndef CHANDRA_INDEPENDENT_CHIP_UTILS_H
#define CHANDRA_INDEPENDENT_CHIP_UTILS_H
namespace chandra
{

class ScopedEnable
{
	public:
		ScopedEnable(const uint8_t& _reg=0, const uint8_t& _bit=255) : reg_(_reg), bit_(_bit) {
			entry_ = SystemClock::state(_reg, _bit);
			SystemClock::enable(_reg, _bit, true);
		}

		ScopedEnable(ScopedEnable& _other) : reg_(_other.reg_), bit_(_other.bit_) {
			entry_ = _other.entry_;
			SystemClock::enable(reg_, bit_, true);
		}

		~ScopedEnable() {
			if(!entry_) {
				SystemClock::enable(reg_, bit_, false);
			}
		}

	private:
		const uint8_t reg_;
		const uint8_t bit_;
		bool entry_;
};

} /*namespace chandra*/
#endif /*CHANDRA_INDEPENDENT_CHIP_UTILS_H*/
