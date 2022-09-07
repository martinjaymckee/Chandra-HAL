#ifndef CHANDRA_MATRIX_CORE_H
#define CHANDRA_MATRIX_CORE_H

#include <cstddef>
#include <initializer_list>
#include <type_traits>

namespace chandra
{
namespace math
{
namespace size_ternal
{
template<size_t Rows, size_t Columns>
struct IndexData
{
        template<typename Value>
        constexpr static const auto& value(const Value (&data)[Rows][Columns], size_t i, size_t j) {
            return data[i][j];
        }
        template<typename Value>
        constexpr static auto& value(Value (&data)[Rows][Columns], size_t i, size_t j) {
            return data[i][j];
        }
};

template<size_t Rows>
struct IndexData<Rows, 1>
{
        template<typename Value>
        constexpr static const auto& value(const Value (&data)[Rows][1], size_t i, size_t) {
            return data[i][0];
        }
        template<typename Value>
        constexpr static auto& value(Value (&data)[Rows][1], size_t i, size_t) {
            return data[i][0];
        }
};

template<size_t Columns>
struct IndexData<1, Columns>
{
        template<typename Value>
        constexpr static const auto& value(const Value (&data)[1][Columns], size_t i, size_t) {
            return data[0][i];
        }
        template<typename Value>
        constexpr static auto& value(Value (&data)[1][Columns], size_t i, size_t) {
            return data[0][i];
        }
};

template<>
struct IndexData<1, 1>
{
        template<typename Value>
        constexpr static const auto& value(const Value (&data)[1][1], size_t, size_t) {
            return data[0][0];
        }
        template<typename Value>
        constexpr static auto& value(Value (&data)[1][1], size_t, size_t) {
            return data[0][0];
        }
};
} /* namespace size_ternal */

// TODO: IMPROVE THE "RANDOM" CONSTRUCTORS TO HAVE BETTER CONTROL OF
//        THE RANDOM NUMBERS (PASS IN A RANDOM GENERATOR)
// TODO: ADD STATIC CONSTRUCTOR FROM A*A.t, L*D*L.t, AND OTHERS
// TODO: ADD DIAGONAL MATRIX TYPE(TRIDIAGONAL, ETC.)
// TODO: ADD SYMMETRIC/SKEW-SYMMETRIC MATRIX TYPE
// TODO: ADD ROW-WISE/COLUMN-WISE STORAGE TYPES TO SPEED TRANSPOSE
// TODO: ADD VIEWS (ROW, COLUMN, TRANSPOSE, ETC.)
// TODO: ADD OPTIMIZED OPERATIONS WITH SPECIAL MATRIX TYPES
//    -- SYMMETRIC MATRIX ADDITION
//    -- MATRIX MULTIPLICATION TO SYMMETRIC MATRIX
//    -- ?? EXPRESSION TEMPLATE FUNCTIONS

template<typename Value, size_t Rows, size_t Columns>
class Matrix
{

    public:
        template<typename V, size_t R, size_t C>
        friend class Matrix;

        using value_t = Value;
        using index_t = size_t; // TODO: THIS SHOULD BE CALCULATED TO BE OPTIMAL
        using matrix_t = Matrix<Value, Rows, Columns>;

        //
        // Matrix Construction
        //

        //  Default constructor does not initialize memory
    		constexpr Matrix() {};

        constexpr Matrix(value_t _val) {
          for (index_t row = 0; row < Rows; ++row) {
            for (index_t column = 0; column < Columns; ++column) {
              data_[row][column] = _val;
            }
          }
        }

        //  Initializer list constructor will initialize the matrix in row major order until the
        //      end of the initializer list is reached or all matrix values are full.  If the
        //      initializer list is depleted, the remaining values in the matrix will remain
        //      uninitialized.  This initialization can be done in either row-major or
        //      column-major order.
        //  TODO: OPTIMIZE THE IMPLEMENTATION HERE TO USE THE _ROW_MAJOR PARAMETER BETTER
        constexpr Matrix(std::initializer_list<value_t> _values, const bool& _row_major=true) {
          auto vs = _values.begin();
    			if (_row_major) {
    				for (index_t row = 0; row < Rows; ++row) {
    					for (index_t column = 0; column < Columns; ++column) {
    						data_[row][column] = *(vs++);
    					}
    					if (vs == _values.end()) break;
    				}
    			} else {
            for(index_t column = 0; column < Columns; ++column){
                for(index_t row = 0; row < Rows; ++row){
                    data_[row][column] = *(vs++);
                }
                if(vs == _values.end()) break;
            }
          }
        }

      	//	Copy Constructor -- TODO: CHECK THAT THIS IS BEING CALLED CORRECTLY
      	template<typename OtherValue>
      	constexpr Matrix(const Matrix<OtherValue, Rows, Columns>& _other) {
          // TODO: THIS NEEDS TO DO A STATIC_ASSERT TO CHECK THAT OTHERVALUE IS CONVERTIBLE TO VALUE_T
      		for (index_t row = 0; row < Rows; ++row) {
      			for (index_t column = 0; column < Columns; ++column) {
      				data_[row][column] = static_cast<Value>(_other.data_[row][column]);
      			}
      		}
      	}

        //  Construct a filled matrix
        static constexpr matrix_t Filled( const value_t& _value) {
          matrix_t matrix;
            for(index_t row = 0; row < Rows; ++row){
                for(index_t column = 0; column < Columns; ++column){
                    matrix.data_[row][column] = _value;
                }
            }
          return matrix;
        }

        //  Construct a zero matrix
        static constexpr matrix_t Zeros() {
          return Filled(0);
        }

        //  Construct a ones matrix
        static constexpr matrix_t Ones() {
          return Filled(1);
        }

    		//  Construct an Identity matrix
        static constexpr matrix_t Eye() {
            matrix_t matrix;
            static_assert(Rows == Columns, "Attempting to make a non-square identity matrix!");
            for(index_t row = 0; row < Rows; ++row){
                for(index_t column = 0; column < Columns; ++column){
                    matrix.data_[row][column] = (row == column) ? value_t(1) : value_t(0);
                }
            }

            return matrix;
        }

        //  Construct a Diagonal matrix with the initializer list providing the values beginning
        //      from the upper-left.  The entire matrix will be initialized.  If there are more
        //      diagonal elements than are provided in the initializer list, the remainder will
        //      be initialized to the fill value, unless the cycle argument is specified as true
        //      in which case the initializer list will be repeated to fill the entire set of
        //      diagonal values.  All non-diagonal elements are set to the fill value.
        static constexpr matrix_t Diagonal(
                std::initializer_list<value_t> _values,
                const value_t& fill = value_t(0),
                const bool& cycle = false
                ) {
            matrix_t matrix;
            auto vs = _values.begin();
            for(index_t row = 0; row < Rows; ++row){
                for(index_t column = 0; column < Columns; ++column){
                    if(row==column) {
                        matrix.data_[row][column] = (vs == _values.end()) ? fill : *(vs++);
                    } else {
                        matrix.data_[row][column] = fill;
                    }
                }
                if(cycle && (vs == _values.end())) vs = _values.begin(); // Cycle through values
            }
            return matrix;
        }
        // TODO: Add an offset argument to the Diagonal Matrix Factory and create a TriDiagonal method with similar arguments

    		// Construct a matrix of numbers calculated from the row and colum index by a
    		//		passed in function object
        template<typename Func>
		    static constexpr matrix_t MapBuild(Func f) {
            matrix_t matrix;
            for(index_t row = 0; row < Rows; ++row){
                for(index_t column = 0; column < Columns; ++column){
					          const auto v = f(row, column);
                    matrix.data_[row][column] = v;
                }
            }
            return matrix;
        }

    		//  Construct a matrix of counting numbers (beginning at the base -- zero by default)
    		//      in either row major format (true) or column major format (false)
    		static constexpr matrix_t Count(value_t base = 0, const bool& row_major = true) {
    			return MapBuild(
    				[=](index_t row, index_t column)
    				{ return base + (row_major ? (row * Columns) + column : (column * Rows) + row); }
    			);
    		}

        // TODO: THIS IS A HACK, AT THE MOMENT.  IT'S NOT GIVING GOOD RANDOM NUMBERS NOR IS IT
        //      AT ALL FLEXIBLE AS TO TYPE (I.E. NO FRACTIONAL NUMBERS)
        static constexpr matrix_t Random(const size_t& seed = 12345, const size_t& mod=100) {
            usize_t64_t state = seed;
            matrix_t matrix;
            for(index_t row = 0; row < Rows; ++row){
                for(index_t column = 0; column < Columns; ++column){
                    state = 987656789 * state + 1357911;
                    matrix.data_[row][column] = static_cast<Value>((state >> 32) % mod);
                }
            }
            return matrix;
        }

        static constexpr matrix_t RandomDiag(const size_t& seed = 12345, const size_t& mod=100) {
            usize_t64_t state = seed;
            matrix_t matrix;
            for(index_t row = 0; row < Rows; ++row){
                for(index_t column = 0; column < Columns; ++column){
                    state = 987656789 * state + 1357911;
                    if(row == column) {
                      matrix.data_[row][column] = static_cast<Value>((state >> 32) % mod);
                    } else {
                      matrix.data_[row][column] = Value(0);
                    }
                }
            }
            return matrix;
        }

        static constexpr matrix_t RandomL(const size_t& seed = 12345, const size_t& mod=100) {
            usize_t64_t state = seed;
            matrix_t matrix;
            for(index_t row = 0; row < Rows; ++row){
                for(index_t column = 0; column < Columns; ++column){
                    state = 987656789 * state + 1357911;
                    if(row <= column) {
                      matrix.data_[row][column] = static_cast<Value>((state >> 32) % mod);
                    } else {
                      matrix.data_[row][column] = Value(0);
                    }
                }
            }
            return matrix;
        }

        // TODO: THIS IS SUFFERING FROM ALL THE SAME PROBLEMS THAT THE OTHER RANDOM
        //  CONSTRUCTORS ARE.
        static constexpr matrix_t RandomSPD(const size_t& seed = 12345, const size_t& mod=100) {
          auto L = matrix_t::RandomL(seed, mod);
          for(index_t i = 0; i < Rows; ++i) L(i, i) = Value(1);
          const auto D = matrix_t::RandomDiag(2*seed + mod, mod);
          return (L * D) * L.T();
        }

        //
        // Data Access Operations
        //

        //  Assignment Operator
        template<typename OtherValue>
        constexpr matrix_t& operator = (const Matrix<OtherValue, Rows, Columns>& _other) {
            for(index_t row = 0; row < Rows; ++row){
                for(index_t column = 0; column < Columns; ++column){
                    data_[row][column] = _other.data_[row][column];
                }
            }
            return *this;
        }

        //  Equality Operator
        template<typename OtherValue>
        constexpr bool operator == (const Matrix<OtherValue, Rows, Columns>& _other) const {
          for(index_t row = 0; row < Rows; ++row){
              for(index_t column = 0; column < Columns; ++column){
                  if(data_[row][column] != _other.data_[row][column]) {
                    return false;
                  }
              }
          }
          return true;
        }

        template<typename OtherValue>
        constexpr bool operator != (const Matrix<OtherValue, Rows, Columns>& _other) const {
          for(index_t row = 0; row < Rows; ++row){
              for(index_t column = 0; column < Columns; ++column){
                  if(data_[row][column] == _other.data_[row][column]) {
                    return false;
                  }
              }
          }
          return true;
        }

        //  Shape data accessors
        static constexpr index_t rows = Rows;
        static constexpr index_t columns = Columns;
        static constexpr bool is_column_vector = (Rows > 1) && (Columns == 1);
        static constexpr bool is_row_vector = (Rows == 1) && (Columns > 1);

        // TODO: ONLY VECTORS SHOULD HAVE A SINGLE ARGUMENT.  TWO DIMENSIONAL MATRICIES SHOULD HAVE
        //  AN OVERLOAD WHICH TAKES TWO INDICIES
        constexpr const value_t& operator () (size_t i, const size_t& j = -1) const {
            return size_ternal::IndexData<Rows, Columns>::value(data_, i, j);
        }
        constexpr value_t& operator () (size_t i, const size_t& j = -1) {
            return size_ternal::IndexData<Rows, Columns>::value(data_, i, j);
        }
        //  TODO: ADD ROW[] AND COLUMN[] PROXIES

        //
        // Basic Arithmetic
        //
        //  Unary Negation
        constexpr matrix_t operator - () const {
            matrix_t matrix;
            for(index_t row = 0; row < Rows; ++row){
                for(index_t column = 0; column < Columns; ++column){
                    matrix.data_[row][column] = -(data_[row][column]);
                }
            }
            return matrix;
        }

        //  Matrix Addition
        template<typename OtherValue>
        constexpr matrix_t& operator += (const Matrix<OtherValue, Rows, Columns>& _other) {
            for(index_t row = 0; row < Rows; ++row){
                for(index_t column = 0; column < Columns; ++column){
                    data_[row][column] += _other.data_[row][column];
                }
            }
            return *this;
        }

        //  Scalar Addition
        template<typename ScalarValue>
        constexpr matrix_t& operator += (const ScalarValue& v) {
			//TD<ScalarValue> a;
			//TD<value_t> b;

            static_assert(std::is_convertible<ScalarValue, value_t>::value,
                          "Unable to convert type to matrix value type in scalar addition.");
            for(index_t row = 0; row < Rows; ++row){
                for(index_t column = 0; column < Columns; ++column){
                    data_[row][column] += v;
                }
            }
            return *this;
        }

        //  Matrix Subtraction
        template<typename OtherValue>
        constexpr matrix_t& operator -= (const Matrix<OtherValue, Rows, Columns>& _other) {
            for(index_t row = 0; row < Rows; ++row){
                for(index_t column = 0; column < Columns; ++column){
                    data_[row][column] -= _other.data_[row][column];
                }
            }
            return *this;
        }

        //  Scalar Subtraction
        template<typename ScalarValue>
        constexpr matrix_t& operator -= (const ScalarValue& v) {
            static_assert(std::is_convertible<ScalarValue, value_t>::value,
                          "Unable to convert type to matrix value type in scalar subtraction.");
            for(index_t row = 0; row < Rows; ++row){
                for(index_t column = 0; column < Columns; ++column){
                    data_[row][column] -= v;
                }
            }
            return *this;
        }

        //  Scalar Multiplication
        template<typename ScalarValue>
        constexpr matrix_t& operator *= (const ScalarValue& v) {
          static_assert(std::is_convertible<ScalarValue, value_t>::value,
                        "Unable to convert type to matrix value type in scalar multiplication.");
            for(index_t row = 0; row < Rows; ++row){
                for(index_t column = 0; column < Columns; ++column){
                    data_[row][column] *= v;
                }
            }
            return *this;
        }

        //  Scalar Division
        template<typename ScalarValue>
        constexpr matrix_t& operator /= (const ScalarValue& v) {
          static_assert(std::is_convertible<ScalarValue, value_t>::value,
                        "Unable to convert type to matrix value type in scalar division.");
            for(index_t row = 0; row < Rows; ++row){
                for(index_t column = 0; column < Columns; ++column){
                    data_[row][column] /= v;
                }
            }
            return *this;
        }

        //
        // Matrix Operations
        //
        //  Transpose
        constexpr auto T() const {
            Matrix<value_t, Columns, Rows> M;
            for(index_t row = 0; row < Rows; ++row){
                for(index_t column = 0; column < Columns; ++column){
                    M.data_[column][row] = data_[row][column];
                }
            }
            return M;
        }

    protected:
        static constexpr index_t idx(const index_t& row, const index_t& column) {
            return (row*Columns) + column;
        }

        value_t data_[Rows][Columns];
};

} /*namespace math*/
} /*namespace chandra*/

#endif /*CHANDRA_MATRIX_CORE_H*/
