/*
 * meta_core.h
 *
 *  Created on: May 19, 2017
 *      Author: martin
 */

#ifndef CHANDRA_META_CORE_H
#define CHANDRA_META_CORE_H

namespace chandra
{
namespace meta
{

struct null_type{}; // This is a general purpose type to use as a non-type
typedef null_type null_t;

// This class can be used to force an error message displying the type, T
template<class T>
class TD;

namespace impl
{

//
// Static Assert
//	This is simplified ( just implements gcc support ) version of the static assertion in the boost library
//
template < bool err > struct STATIC_ASSERTION_FAILURE;
template <> struct STATIC_ASSERTION_FAILURE<true> { enum { value = 1 }; };
template< int value > struct static_assert_test{};
#define JOINX( a, b ) a##b
#define JOIN( a, b ) JOINX( a, b )
#define STATIC_ASSERT( expr ) \
typedef impl::static_assert_test<\
sizeof( impl::STATIC_ASSERTION_FAILURE< (bool)( expr ) >)>\
        	JOIN( static_assertion_typedef_, __LINE__ )

template< class left, class right >
struct list_empty_impl
{
	typedef list_empty_impl< left, right > type;
	static const bool value = false;
};
template<>
struct list_empty_impl< null_type, null_type >
{
	typedef list_empty_impl< null_type, null_type > type;
	static const bool value = true;
};

template< bool gt8, bool gt16, bool gt24, bool gt32, bool gt48, bool gt64, bool _is_signed >
struct minimal_int_type_from_bits_impl
{
	static const bool UNDEFINED_INT_SIZE = false;
	STATIC_ASSERT( UNDEFINED_INT_SIZE && gt8 );
};

template<> struct minimal_int_type_from_bits_impl< false, false, false, false, false, false, false > { typedef uint8_t type; };
template<> struct minimal_int_type_from_bits_impl< false, false, false, false, false, false, true > { typedef int8_t type; };

template<> struct minimal_int_type_from_bits_impl< true, false, false, false, false, false, false > { typedef uint16_t type; };
template<> struct minimal_int_type_from_bits_impl< true, false, false, false, false, false, true > { typedef int16_t type; };

// Promote unspecialized types... 24 bit int
template<> struct minimal_int_type_from_bits_impl< true, true, false, false, false, false, false > { typedef uint32_t type; };
template<> struct minimal_int_type_from_bits_impl< true, true, false, false, false, false, true > { typedef int32_t type; };

template<> struct minimal_int_type_from_bits_impl< true, true, true, false, false, false, false > { typedef uint32_t type; };
template<> struct minimal_int_type_from_bits_impl< true, true, true, false, false, false, true > { typedef int32_t type; };

// Promote unspecialized types... 48 bit int
template<> struct minimal_int_type_from_bits_impl< true, true, true, true, false, false, false > { typedef uint64_t type; };
template<> struct minimal_int_type_from_bits_impl< true, true, true, true, false, false, true > { typedef int64_t type; };

template<> struct minimal_int_type_from_bits_impl< true, true, true, true, true, false, false > { typedef uint64_t type; };
template<> struct minimal_int_type_from_bits_impl< true, true, true, true, true, false, true > { typedef int64_t type; };

//
// Max Int Size Limit Overflow
//
template< bool _is_signed >
struct minimal_int_type_from_bits_impl< true, true, true, true, true, true, _is_signed >
{
	static const bool INT_SIZE_OVERFLOW = false;
	STATIC_ASSERT( INT_SIZE_OVERFLOW && _is_signed );
};

//
// Return selection
//
template< bool _return_first, class value_type, value_type _value_a, value_type _value_b >
struct return_selected
{
	typedef return_selected< _return_first, value_type, _value_a, _value_b > type;
	static const value_type value = _value_b;
};

template< class value_type, value_type _value_a, value_type _value_b >
struct return_selected< true, value_type, _value_a, _value_b >
{
	typedef return_selected< true, value_type, _value_a, _value_b > type;
	static const value_type value = _value_a;
};

//
// Type Compare Implementation
//
template< class _type_a, class _type_b >
struct type_eq
{
	typedef type_eq< _type_a, _type_b > type;
	static const bool value = false;
};

template< class _same_type >
struct type_eq< _same_type, _same_type >
{
	typedef type_eq< _same_type, _same_type > type;
	static const bool value = true;
};

//
// Calculate Absolute Value
//
template< bool _is_neg, class source_type, source_type _value, class destination_type >
struct value_abs_impl {
	typedef value_abs_impl< _is_neg, source_type, _value, destination_type > type;
	static const destination_type value = _value;
};

template< class source_type, source_type _value, class destination_type >
struct value_abs_impl < true, source_type, _value, destination_type >
{
	typedef value_abs_impl< true, source_type, _value, destination_type > type;
	static const destination_type value = static_cast< destination_type >( -1 * long( _value ) );
};

template< class source_type, source_type _value, class destination_type >
struct value_abs
{
	typedef value_abs< source_type, _value, destination_type > type;
	static const bool value_neg = _value < 0;
	static const destination_type value = value_abs_impl< value_neg, source_type, _value, destination_type >::value;
};

//
// Calculate Maximum/Minimum Values
//

template< class value_type, value_type _value_a, value_type _value_b >
struct max_value
{
	typedef max_value< value_type, _value_a, _value_b > type;
	static const bool is_a_larger = _value_a > _value_b;
	static const value_type value = return_selected< is_a_larger, value_type, _value_a, _value_b >::value;
};

template< class value_type, value_type _value_a, value_type _value_b >
struct min_value
{
	typedef min_value< value_type, _value_a, _value_b > type;
	static const bool is_a_smaller = _value_a < _value_b;
	static const value_type value = return_selected< is_a_smaller, value_type, _value_a, _value_b >::value;
};

//
// Calculate Minimum number of bits to represent a value
//
template< class value_type, value_type _value, class return_type, return_type _count, bool _done >
struct minimum_representation_bits_impl
{
	typedef minimum_representation_bits_impl< value_type, _value, return_type, _count, _done > type;
	static const value_type new_value = _value / 2;
	static const bool done = ( ( new_value / 2 ) == 0 );
	static const return_type value = minimum_representation_bits_impl< value_type, new_value, return_type, ( _count + 1 ), done >::value;
};

template< class value_type, value_type _value, class return_type, return_type _count >
struct minimum_representation_bits_impl< value_type, _value, return_type, _count, true >
{
	typedef minimum_representation_bits_impl< value_type, _value, return_type, _count, true > type;
	static const return_type value = _count;
};

//
// Calcuate Maximum Representable Value From Number of Bits
//
template< class return_type, return_type _value, uint8_t _bits >
struct maximum_representable_value_impl
{
	typedef maximum_representable_value_impl< return_type, _value, _bits > type;
	static const return_type value = maximum_representable_value_impl< return_type, ( ( _value << 1 ) | 0x01 ), ( _bits - 1 ) >::value;
};

template< class return_type, return_type _value >
struct maximum_representable_value_impl< return_type, _value, 0 >
{
	typedef maximum_representable_value_impl< return_type, _value, 0 > type;
	static const return_type value = _value;
};

template< class return_type, uint8_t _bits >
struct maximum_representable_value
{
	typedef maximum_representable_value< return_type, _bits > type;
    static constexpr return_type value = maximum_representable_value_impl< return_type, 0, _bits >::value;
};

template< class T >
struct is_signed
{
	private:
        static constexpr T zero = 0;

	public:
        static constexpr bool value = static_cast<long long>( zero - T(1) ) < 0LL; // NOTE: THE CAST HERE IS TO ENSURE A SIGNED COMPARISON DOES THIS WORK???
};

} /* namespace impl */

//
// Minimum Representation Bits
template< class value_type, value_type _value, class return_type >
struct minimum_representation_bits
{
    typedef minimum_representation_bits< value_type, _value, return_type > type;
    static const return_type base_value = impl::minimum_representation_bits_impl< value_type, _value, return_type, 0, ( _value == 0 ) >::value;
    static const value_type base_calc_value = static_cast<value_type>(0x01) << base_value;
    static const return_type value = impl::return_selected< ( _value >= base_calc_value ), return_type, ( base_value + 1 ), base_value  >::value;
};

//
// This should be overloaded if Boost support is enabled // This is where the calculated range will go - maximum unsigned type
template< class _left, class _right >
struct LIST
{
	typedef _left left;
	typedef _right right;
	typedef LIST< _left, _right > type;
	static const bool isEmpty = impl::list_empty_impl< _left, _right >::value;
};

typedef LIST< null_type, null_type > EMPTY_LIST;

//
// Minimal integer data types ( signed, unsigned )
//
template< uint8_t bits, bool _is_signed = false >
struct minimal_int_type_from_bits
{
	static const bool gt8 = bits > 8;
	static const bool gt16 = bits > 16;
	static const bool gt24 = bits > 24;
	static const bool gt32 = bits > 32;
	static const bool gt48 = bits > 48;
	static const bool gt64 = bits > 64;

	typedef typename impl::minimal_int_type_from_bits_impl< gt8, gt16, gt24, gt32, gt48, gt64, _is_signed >::type type;
};

template< long _minimum, long _maximum, bool _force_signed = false > // This should use the largest signed int type for range values
struct minimal_int_type_from_range
{
	STATIC_ASSERT( _maximum >= _minimum ); // This will only work with valid ranges, maximum greater than or equal to minimum

	static const bool is_signed = impl::return_selected< _force_signed, bool, true, ( ( _maximum < 0 ) || ( _minimum < 0 ) ) >::value;
	static const unsigned long min_abs = impl::value_abs< long, _minimum, unsigned long>::value;
	static const unsigned long max_abs = impl::value_abs< long, _maximum, unsigned long>::value;
	static const unsigned long range = impl::max_value< unsigned long, min_abs, max_abs >::value; // Range to use for bits calculation
    static const uint8_t minimum_bits = minimum_representation_bits< unsigned long, range, uint8_t >::value;
	static const unsigned long maximum_value_by_bits = impl::maximum_representable_value< unsigned long, minimum_bits >::value;
	static const bool range_is_maximum = impl::max_value< unsigned long, max_abs, min_abs >::is_a_larger;
	static const uint8_t minimum_range_bits = impl::return_selected< ( range == 0 ), uint8_t, 1, minimum_bits >::value;
	static const bool is_exact = ( range == ( static_cast<unsigned long>(1) << ( minimum_range_bits - 1 ) ) );
	static const uint8_t final_bits = impl::return_selected< ( is_signed && !is_exact ), uint8_t, ( minimum_range_bits + 1 ), minimum_range_bits >::value;
	typedef typename minimal_int_type_from_bits< final_bits, is_signed >::type type;
};

template< class _value_type, uint8_t _high_bit, uint8_t _low_bit >
struct construct_mask
{
	STATIC_ASSERT( ( _high_bit >= _low_bit ) && ( ( 8 * sizeof( _value_type ) ) > _high_bit ) );
	static const _value_type value = ( impl::maximum_representable_value< _value_type, _high_bit+1 >::value ) & ~( impl::maximum_representable_value< _value_type, _low_bit >::value );
};

template< class _type >
struct num_bits { static const uint8_t value = ( 8 * sizeof( _type ) ); };

template< class _type_a, class _type_b >
struct calc_type
{
	static const bool is_a_signed = impl::is_signed< _type_a >::value;
	static const bool is_b_signed = impl::is_signed< _type_b >::value;
	static const uint8_t bits_a = 8 * sizeof( _type_a );
	static const uint8_t bits_b = 8 * sizeof( _type_b );
	typedef typename minimal_int_type_from_bits< ( impl::max_value< uint8_t, bits_a, bits_b >::value + 1 ), ( is_a_signed || is_b_signed )>::type addition;
	typedef typename minimal_int_type_from_bits< ( impl::max_value< uint8_t, bits_a, bits_b >::value + 1 ), ( is_a_signed || is_b_signed )>::type subtraction;
	typedef typename minimal_int_type_from_bits<  ( bits_a + bits_b ), ( is_a_signed || is_b_signed )>::type multiplication;
	typedef typename minimal_int_type_from_bits<  ( bits_a + bits_b ), ( is_a_signed || is_b_signed )>::type division;
	typedef typename minimal_int_type_from_bits<  ( bits_a + bits_b ), ( is_a_signed || is_b_signed )>::type generic;
};

//
// Compile-Time Shift Selection
//
namespace impl
{
template<int32_t _value, bool _negative>
struct static_abs_impl
{
	static const uint32_t value = -_value;
};

template<int32_t _value>
struct static_abs_impl<_value, false>
{
	static const uint32_t value = _value;
};
} // namespace impl

template<int32_t _value>
struct StaticAbs
{
	static const uint32_t value = impl::static_abs_impl<_value, (_value < 0)>::value;
};

//
// Compile-Time Shift Selection
//
namespace impl
{
template<class T, uint32_t _shift, bool _left>
struct shift_impl
{
	static T exec( const T& _value ) { return _value << static_cast<uint32_t>(_shift); }
};

template<class T, uint32_t _shift>
struct shift_impl<T, _shift, false>
{
	static T exec( const T& _value ) { return _value >> static_cast<uint32_t>(_shift); }
};
} // namespace impl

template<class T, int32_t _shift>
struct Shift
{
	static T exec(const T& _value) { return impl::shift_impl<T, StaticAbs<_shift>::value, (_shift < 0)>::exec(_value); }
};

//
// Compile-Time Power of Two Detection -- TODO: DECIDE IF THIS NAMING SHOULD BE KEPT
//
template< uint64_t _value >
struct is_power_of_two
{
    private:
        static const uint64_t divided = _value / 2;
        static const uint64_t remainder = _value % 2;

    public:
        static const bool value = ( remainder != 0 ) ? false : is_power_of_two< divided >::value;
};

template<>
struct is_power_of_two< 1 >
{
    static const bool value = true;
};

template<>
struct is_power_of_two< 0 >
{
    static const bool value = true;
};

//
// Is of type
//

template< class _compare_type >
struct is_of_type
{ // need declspec or typeof to do this in a static expression... otherwise use impl::type_eq< _compare_type, T >::value
	// possible place to wrap with a macro
	template< class T > static bool check( T ){ return impl::type_eq< _compare_type, T >::value; }
};


} /*namespace meta*/
} /*namespace chandra*/

#endif /*CHANDRA_META_CORE_H*/
