#ifndef CHANDRA_MATRIX_H
#define CHANDRA_MATRIX_H

#include <initializer_list>
#include <iostream>
#include <type_traits>
#include <random>

namespace chandra
{
namespace math
{
namespace internal
{
template<int Rows, int Columns>
struct IndexData
{
        constexpr static const auto& value(const auto (&data)[Rows][Columns], int i, int j) {
            return data[i][j];
        }
        constexpr static auto& value(auto (&data)[Rows][Columns], int i, int j) {
            return data[i][j];
        }
};

template<int Rows>
struct IndexData<Rows, 1>
{
        constexpr static const auto& value(const auto (&data)[Rows][1], int i, int) {
            return data[i][0];
        }
        constexpr static auto& value(auto (&data)[Rows][1], int i, int) {
            return data[i][0];
        }
};

template<int Columns>
struct IndexData<1, Columns>
{
        constexpr static const auto& value(const auto (&data)[1][Columns], int i, int) {
            return data[0][i];
        }
        constexpr static auto& value(auto (&data)[1][Columns], int i, int) {
            return data[0][i];
        }
};

//
// Forward Declaration of the VectorWrapper Class
//
template<typename Value, size_t Rows, size_t Columns>
class VectorWrapper;
} /*namespace internal*/

template<typename Value, size_t Rows, size_t Columns>
class Matrix
{

    public:
        template<typename V, size_t R, size_t C>
        friend class Matrix;

        //template<typename V1, typename V2, size_t M, size_t N1, size_t N2, size_t O>
        //friend constexpr auto operator * (const Matrix<V1, M, N1>& a, const Matrix<V2, N2, O>& b);

        using value_t = Value;
        using index_t = size_t; // TODO: THIS SHOULD BE CALCULATED TO BE OPTIMAL
        using matrix_t = Matrix<Value, Rows, Columns>;

        //
        // Matrix Construction
        //

        //  Default constructor does not initialize memory
        Matrix() {}

        //  Single argument constructor initializes memory to the passed value
        constexpr Matrix(const value_t& v) {
            for(index_t row = 0; row < Rows; ++row){
                for(index_t column = 0; column < Columns; ++column){
                    data_[row][column] = v;
                }
            }
        }

        //  Initializer list constructor will initialize the matrix in row major order until the
        //      end of the initializer list is reached or all matrix values are full.  If the
        //      initializer list is depleted, the remaining values in the matrix will remain
        //      uninitialized.
        constexpr Matrix(std::initializer_list<value_t> _values) {
            auto vs = _values.begin();
            for(index_t row = 0; row < Rows; ++row){
                for(index_t column = 0; column < Columns; ++column){
                    data_[row][column] = *(vs++);
                }
                if(vs == _values.end()) break;
            }
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

        //  Construct a matrix of counting numbers (beginning at zero, at the moment) in either
        //      row major format (true) or column major format (false)
        static constexpr matrix_t Count(const bool& row_major = true) {
            matrix_t matrix;
            for(index_t row = 0; row < Rows; ++row){
                for(index_t column = 0; column < Columns; ++column){
                    const auto v = row_major ? (row * Columns) + column : (column * Rows) + row;
                    matrix.data_[row][column] = v;
                }
            }
            return matrix;
        }
        // TODO: This could be easily generalized to provide more complicated functions with
        //      a base and step size.  OR, JUST MAKE A FACTORY THAT TAKES A LAMBDA AS AN ARGUMENT!

        // TODO: THIS IS A HACK, AT THE MOMENT.  IT'S NOT GIVING GOOD RANDOM NUMBERS NOR IS IT
        //      AT ALL FLEXIBLE AS TO TYPE (I.E. NO FRACTIONAL NUMBERS)
        static constexpr matrix_t Random(const size_t& seed = 12345, const size_t& mod=100) {
            uint64_t state = seed;
            matrix_t matrix;
            for(index_t row = 0; row < Rows; ++row){
                for(index_t column = 0; column < Columns; ++column){
                    state = 987656789 * state + 1357911;
                    matrix.data_[row][column] = (state >> 32) % mod;
                }
            }
            return matrix;
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

        //  Shape data accessors
        constexpr static index_t rows = Rows;
        constexpr static index_t columns = Columns;

        // TODO: ONLY VECTORS SHOULD HAVE A SINGLE ARGUMENT.  TWO DIMENSIONAL MATRICIES SHOULD HAVE
        //  AN OVERLOAD TAKES TWO INDICIES
        constexpr const value_t& operator () (int i, const int& j = -1) const {
            return internal::IndexData<Rows, Columns>::value(data_, i, j);
        }
        constexpr value_t& operator () (int i, const int& j = -1) {
            return internal::IndexData<Rows, Columns>::value(data_, i, j);
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
        constexpr matrix_t& operator += (const auto& v) {
            static_assert(std::is_convertible<decltype(v), value_t>::value,
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
        constexpr matrix_t& operator -= (const auto& v) {
            static_assert(std::is_convertible<decltype(v), value_t>::value,
                          "Unable to convert type to matrix value type in scalar subtraction.");
            for(index_t row = 0; row < Rows; ++row){
                for(index_t column = 0; column < Columns; ++column){
                    data_[row][column] -= v;
                }
            }
            return *this;
        }

        //  Scalar Multiplication
        constexpr matrix_t& operator *= (const auto& v) {
            for(index_t row = 0; row < Rows; ++row){
                for(index_t column = 0; column < Columns; ++column){
                    data_[row][column] *= v;
                }
            }
            return *this;
        }

        //  Scalar Division
        constexpr matrix_t& operator /= (const auto& v) {
            for(index_t row = 0; row < Rows; ++row){
                for(index_t column = 0; column < Columns; ++column){
                    data_[row][column] /= v;
                }
            }
            return *this;
        }

    private:
        static constexpr index_t idx(const index_t& row, const index_t& column) {
            return (row*Columns) + column;
        }

        value_t data_[Rows][Columns];
};

} /*namespace math*/
} /*namespace chandra*/

#endif /*CHANDRA_MATRIX_H*/

