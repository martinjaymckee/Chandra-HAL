#ifndef CHANDRA_VALUE_MAP_H
#define CHANDRA_VALUE_MAP_H

#include "meta.h"
#include "value-limit.h"

//
// TODO: THE VALUE MAPPING FUNCTIONALITY NEEDS *LOADS* OF CLEANUP.  WHILE IT WORKS, IT'S NOT INTUITIVE
//  AND IT'S PROBABLY NOT ALL THAT EFFICIENT.  IT ALSO IS RATHER FRAGILE.  AS MUCH AS POSSIBLE,
//  TEMPLATE FUNCTION PARAMATER ARGUMENT DEDUCTION SHOULD BE USED TO SELECT TYPES.  ALSO, IT IS
//  IMPORTANT TO MAKE THESE FUNCTIONS AS EFFICIENT AS POSSIBLE AS THEY WILL FORM THE VERY CENTRAL
//  FUNCTIONALITY OF SOME APPLICATIONS.
//
namespace chandra
{
namespace signal
{

//
// TODO: Add an Interpolation Flags type that can be used by the different Interpolation routines to return calculation data.

//	There should be things like: Clipped, Overflow( calculation ), Underflow( calculation ), etc.  Very likely the best way 
//	to do this would be to always return a class that has both the value and the flags included...
//
//	Additionally, this data should be available ( in a sticky form ) in a static base class.  Flags would be set in static
//	members and anyone would be able to check them afterward.  The flags could also be cleared, either as a group or
//	individually (perhaps using a mask).
//

//
// Maps a value linearly between two value ranges...
//
template< class Src, class Dest = Src,
          class Calc = typename chandra::meta::calc_type<Src, Dest>::generic >
class LinearMap
{
	public:        
        using src_value_t = Src;
        using dest_value_t = Dest;
        using calc_t = Calc;

        LinearMap(const src_value_t& _src_min, const src_value_t& _src_max,
                  const dest_value_t& _dest_min, const dest_value_t& _dest_max,
                  bool _inverted = false, bool _do_clip_src = true, bool _do_clip_dest = true ) :
            src_min_( _src_min ), src_max_( _src_max ),
            dest_min_( _dest_min ), dest_max_( _dest_max ),
			inverted_( _inverted ), do_clip_src_( _do_clip_src ), do_clip_dest_( _do_clip_dest ), 
			clip_src( _src_min, _src_max ), clip_dest( _dest_min, _dest_max ) {}

		//
		// Map a value from the source range into the destination range
		//
		template< class op_value_t >
		dest_value_t forward( const op_value_t& _value ) const {
            const calc_t input_value = do_clip_src_ ?
                        clip_src( _value ) : static_cast< calc_t >( _value );
            calc_t raw_value = 0;
			
			if( !inverted() ) {
                raw_value = map(input_value, src_min_, src_max_, dest_min_, dest_max_);
			} else {
                raw_value = map(input_value, src_min_, src_max_, dest_max_, dest_min_);
			}
			
            return static_cast<dest_value_t>( do_clip_dest_ ? clip_dest( raw_value ) : raw_value );
		}
		
		template< class op_value_t >
		dest_value_t operator () ( const op_value_t& _value ) const { return forward( _value ); }
		
		//
		// Map a value from the destination range into the source range
		//
		template< class op_value_t >		
		src_value_t reverse( const op_value_t& _value ) const {
            const calc_t input_value = do_clip_src_ ?
                        clip_dest( _value ) : static_cast<calc_t >( _value );
            calc_t raw_value = 0;
			
			if( !inverted() ) {
                raw_value = map( input_value, dest_min_, dest_max_, src_min_, src_max_);
			} else {
                raw_value = map( input_value, dest_min_, dest_max_, src_max_, src_min_);
			}
			
			return static_cast< src_value_t >( do_clip_dest_ ? clip_src( raw_value ) : raw_value );
		}
		
		//
		// Check Validity
		//
        constexpr bool isSrcRangeValid() const { return src_min_ <= src_max_; }
        constexpr bool isDestRangeValid() const { return dest_min_ <= dest_max_; }
        constexpr bool valid() const { return isSrcRangeValid() && isDestRangeValid(); }
		
		//
		// Range Parameters
		//
        constexpr src_value_t srcMin() const { return src_min_; }
        constexpr src_value_t srcMax() const { return src_max_; }
        constexpr src_value_t srcRange() const { return calcRange( src_min_, src_max_ ); }
		
        constexpr dest_value_t destMin() const { return dest_min_; }
        constexpr dest_value_t destMax() const { return dest_max_; }
        constexpr dest_value_t destRange() const { return calcRange( dest_min_, dest_max_ ); }
		
		//
		// Mapping Style
		//
		bool inverted( bool _inverted ) {
			inverted_ = _inverted;
			return inverted_;
		}
        constexpr bool inverted() const { return inverted_; }
		
	protected:
		template< class op_a_t, class op_b_t >
        constexpr calc_t calcRange(const op_a_t& _a, const op_b_t& _b ) const {
            return static_cast<calc_t>( _b ) - static_cast<calc_t>( _a );
		}
		
		template< class map_value_t, class src_op_t, class dest_op_t >
        constexpr calc_t map(const map_value_t& _value, const src_op_t& _src_min, const src_op_t& _src_max, const dest_op_t& _dest_min, const dest_op_t& _dest_max ) const {
            const calc_t dest_range = calcRange( _dest_min, _dest_max );
            const calc_t src_range = calcRange( _src_min, _src_max );
            return ( ( ( calc_t( _value ) - calc_t( _src_min ) ) * dest_range ) / src_range ) + calc_t( _dest_min );
		}
		
        const src_value_t& src_min_;
        const src_value_t& src_max_;
        const dest_value_t& dest_min_;
        const dest_value_t& dest_max_;
		bool inverted_;
		const bool do_clip_src_;
		const bool do_clip_dest_;
        Saturate<calc_t, src_value_t> clip_src;
        Saturate<calc_t, dest_value_t> clip_dest;
};

//
// Maps a value piecewise linearly between two value ranges with defined centers...
//	TODO: Figure out how to handle the _invert mapping on these...
template< class src_value_t, class dest_value_t = src_value_t,
          class calculation_t = typename chandra::meta::calc_type< src_value_t, dest_value_t >::generic >
class BilinearMap
{
	public:
		BilinearMap( const src_value_t& _src_min, const src_value_t& _src_center, const src_value_t& _src_max, 
			   const dest_value_t& _dest_min, const dest_value_t& _dest_center, const dest_value_t& _dest_max, 
			   bool _inverted = false, bool _do_clip_src = true, bool _do_clip_dest = true ) :
			src_min_( _src_min ), src_center_( _src_center ), src_max_( _src_max ), 
			dest_min_( _dest_min ), dest_center_( _dest_center ), dest_max_( _dest_max ),
			inverted_( _inverted ), do_clip_src_( _do_clip_src ), do_clip_dest_( _do_clip_dest ),
			clip_src( _src_min, _src_max ), clip_dest( _dest_min, _dest_max ) {}
		
		//
		// Map a value from the source range into the destination range
		//
		template< class op_value_t >		
		dest_value_t forward( const op_value_t& _value ) const {
			const calculation_t input_value = do_clip_src_ ? clip_src( _value ) : static_cast<calculation_t>( _value );
			const calculation_t raw_value = map( input_value, src_min_, src_center_, src_max_, dest_min_, dest_center_, dest_max_ );
			return static_cast<dest_value_t>( do_clip_dest_ ? clip_dest( raw_value ) : raw_value );
		}
		
		template< class op_value_t >
		dest_value_t operator () ( const op_value_t& _value ) const { return forward( _value ); }
		
		//
		// Map a value from the destination range into the source range
		//
		template< class op_value_t >		
		src_value_t reverse( const op_value_t& _value ) const {
			const calculation_t input_value = do_clip_src_ ? clip_dest( _value ) : static_cast<calculation_t>( _value );
			const calculation_t raw_value = map( input_value, dest_min_, dest_center_, dest_max_, src_min_, src_center_, src_max_ );
			return static_cast<src_value_t>( do_clip_dest_ ? clip_src( raw_value ) : raw_value ); 
		}
		
		//
		// Check Validity
		//
		bool isSrcRangeValid() const { return src_min_ <= src_max_; }
		bool isDestRangeValid() const { return dest_min_ <= dest_max_; }
		bool valid() const { return isSrcRangeValid() && isDestRangeValid(); }
		
		//
		// Range Parameters
		//
		src_value_t srcMin() const { return src_min_; }
		src_value_t srcCenter() const { return src_center_; }
		src_value_t srcMax() const { return src_max_; }
		src_value_t srcRange() const { return src_value_t( calcRange( src_min_, src_max_ ) ); }
		
		dest_value_t destMin() const { return dest_min_; }
		dest_value_t destCenter() const { return dest_center_; }
		dest_value_t destMax() const { return dest_max_; }
		dest_value_t destRange() const { return dest_value_t( calcRange( dest_min_, dest_max_ ) ); }
		
		//
		// Mapping Style
		//
		bool inverted( bool _inverted ) {
			inverted_ = _inverted;
			return inverted_;
		}
		bool inverted() const { return inverted_; }
		
	protected:
		template< class op_a_t, class op_b_t >
		calculation_t calcRange( const op_a_t& _a, const op_b_t& _b ) const { 
			return static_cast<calculation_t>(_b) - static_cast<calculation_t>(_a); 
		}
		
		template< class map_value_t, class src_op_t, class dest_op_t >
		calculation_t map( const map_value_t& _value, src_op_t& _src_min, src_op_t& _src_center, src_op_t& _src_max, dest_op_t& _dest_min, dest_op_t& _dest_center, dest_op_t& _dest_max ) const {
			if( inverted() ){
				if( _value < _src_center ) return LinearMap<src_op_t, dest_op_t, calculation_t>( _src_min, _src_center, _dest_center, _dest_max, true, false, false ).forward( _value );
				return LinearMap<src_op_t, dest_op_t, calculation_t>( _src_center, _src_max, _dest_min, _dest_center, true, false, false ).forward( _value );				
			} else {
				if( _value < _src_center ) return LinearMap<src_op_t, dest_op_t, calculation_t>( _src_min, _src_center, _dest_min, _dest_center, false, false, false ).forward( _value );
				return LinearMap<src_op_t, dest_op_t, calculation_t>( _src_center, _src_max, _dest_center, _dest_max, false, false, false ).forward( _value );				
			}
		}
		
		const src_value_t& src_min_;
		const src_value_t& src_center_;
		const src_value_t& src_max_;
		const dest_value_t& dest_min_;
		const dest_value_t& dest_center_;
		const dest_value_t& dest_max_;
		bool inverted_;
		const bool do_clip_src_;
		const bool do_clip_dest_;		
		Saturate< calculation_t, src_value_t > clip_src;
		Saturate< calculation_t, dest_value_t > clip_dest;
};

//
// Combines two values based on a weight in the range [0, 1.0]
//	TODO: THIS SHOULD HAVE THE ABILITY TO CONTROL CLIPPING ON BOTH SOURCE AND DESTINATION
//
template< class Src, class Dest = Src,
          class Calc = typename chandra::meta::calc_type<Src, Dest>::generic >
class WeightedAverage
{
	protected:
        using calc_t = Calc;

	public:
        using src_value_t = Src;
        using dest_value_t = Dest;

        WeightedAverage(const src_value_t& _src_min, const src_value_t& _src_max,
                        const dest_value_t& _dest_min, const dest_value_t& _dest_max)
			:	zero_(0), one_(1), weight_constraint_(zero_, one_),
				input_constraint_(_src_min, _src_max),
				output_constraint_(_dest_min, _dest_max) {}

		dest_value_t operator () (const src_value_t& _a, const src_value_t& _e, const src_value_t& _b) {
			const calc_t a = input_constraint_(_a);
			const calc_t e = input_constraint_(_e);
			const calc_t b = input_constraint_(_b);
			const calc_t val = (e * (a - b)) + b;
			return output_constraint_(val);
		}

	private:
		const calc_t zero_;
		const calc_t one_;
		Saturate<src_value_t, calc_t> weight_constraint_;
		Saturate<src_value_t, calc_t> input_constraint_;
		Saturate<calc_t, dest_value_t> output_constraint_;
};

} /*namespace signal*/
} /*namespace chandra*/

#endif /*CHANDRA_VALUE_MAP_H*/
