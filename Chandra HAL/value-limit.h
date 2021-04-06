#ifndef CHANDRA_VALUE_LIMIT_H
#define CHANDRA_VALUE_LIMIT_H

#include "meta.h"

//
// TODO: NEED TO GO BACK AND CHECK EACH OF THESE FOR CORRECTNESS.... THESE ARE REALLY UGLY
//  IMPLEMENTATIONS, AND I DON'T TRUST THEM SEVERAL YEARS AFTER HAVING IMPLEMENTED THEM.
//

namespace chandra
{
namespace signal
{

//
// TODO: Add an Interpolation Flags type that can be used by the different Interpolation routines to return calculation data.

//	There should be things like: Clipped, Overflow( calculation ), Underflow( calculation ), etc.  Very likely the best way
//	to do this would be to always return a class that has both the value and the flags included... e.g.
enum class ValueStatus
{
    Clean,
    Clipped,
    Overflow,
    Underflow
};

namespace internal
{
template<typename Value>
struct MarkedValue
{
    const Value value;
    const ValueStatus status;
    operator Value() const { return value; }
};
}
// <--- This could be used as a return value in all cases... though it would get in the way of template
//  argument deduction and require explicit casts, in some cases

template< class value_t, class range_t = value_t >
class Exclude
{
	public:
		Exclude( range_t& _lower, range_t& _upper ) : lower_( _lower ), upper_( _upper ) {}

		//
		// Apply exclusion processing to a value
		//
		value_t operator () ( const value_t& _value ) const {
			if( willClip( _value ) ){
				if( ( upper_ - _value ) <= ( _value - lower_ ) ){ // Clip toward Lower constraint
					return lower_;
				}
				else { // Clip toward Upper constraint
					return upper_;
				}
			}
			else {
				return _value;
			}
		}

		//
		// Check if a value will be clipped
		//
		bool willClip( const value_t& _value ) const {
			return ( ( _value < static_cast< value_t >( upper_ ) ) && ( _value > static_cast< value_t >( lower_ ) ) );
		}

		//
		// Check Validity
		//
		bool valid() const { return upper_ <= lower_; }

		//
		// Range Parameters
		//
		range_t lower() const { return lower_; }
		range_t upper() const { return upper_; }
		range_t exclude_range() const { return upper_ - lower_; }

	protected:
		range_t& lower_;
		range_t& upper_;
};

template< class value_type, class range_type = value_type >
class Saturate
{
	public:
		typedef value_type value_t;
		typedef range_type range_t;

		Saturate( const range_t& _min, const range_t& _max ) : min_( _min ), max_( _max ) {}

		//
		// Apply saturation processing to a value
		//
		value_t operator () ( const value_t& _value ) const {
			if( _value > static_cast< value_t >( max_ ) ) {
				return max_;
			}
			else if( _value < static_cast< value_t >( min_ ) ) {
				return min_;
			}
			return _value;
		}

		//
		// Check if a value will be clipped
		//
		bool willClip( const value_t& _value ) const {
			return ( ( _value > static_cast< value_t >( max_ ) ) || ( _value < static_cast< value_t >( min_ ) ) );
		}

		//
		// Check Validity
		//
		bool valid() const { return min_ <= max_; }

		//
		// Range Parameters
		//
		range_t minimum() const { return min_; }
		range_t maximum() const { return max_; }
		range_t range() const { return max_ - min_; }

	protected:
		const range_t& min_;
		const range_t& max_;
};

template< class value_type, class range_type = value_type >
class SaturateNonNegative
{
	public:
		typedef value_type value_t;
		typedef range_type range_t;

		//
		// Apply saturation processing to a value
		//
		value_t operator () ( const value_t& _value ) const {
      if(_value < value_t{0}) return value_t{0};
			return _value;
		}

		//
		// Check if a value will be clipped
		//
		bool willClip( const value_t& _value ) const {
			return ( _value < value_t{0} );
		}

		//
		// Check Validity
		//
		bool valid() const { return true; }
};

template< class value_type, class range_type = value_type >
class SaturateNegative
{
	public:
		typedef value_type value_t;
		typedef range_type range_t;

		//
		// Apply saturation processing to a value
		//
		value_t operator () ( const value_t& _value ) const {
      if(_value >= value_t{0}) return value_t{0};
			return _value;
		}

		//
		// Check if a value will be clipped
		//
		bool willClip( const value_t& _value ) const {
			return ( _value >= value_t{0} );
		}

		//
		// Check Validity
		//
		bool valid() const { return true; }
};

} /*namespace signal*/
} /*namespace chandra*/

#endif /*CHANDRA_VALUE_LIMIT_H*/
