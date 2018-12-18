#pragma once

#include <accessory_func.h>
#include <config.h>
#include <igaDebug.h>
#include <iomanip>
#include <iostream>
#include <memory>

namespace matrix
{
using namespace Eigen;
using namespace std;
using namespace accessory;

template <typename T>
struct removeNoise_helper
{
    removeNoise_helper( const T& tol ) : mTol( tol )
    {
    }

    T mTol;
    T operator()( const T& val ) const
    {
        return abs( val ) > mTol ? val : 0;
    }
};

// default colmajor
template <class T, int _Rows = Eigen::Dynamic, int _Cols = Eigen::Dynamic, int _Options = 0 | ( ( _Rows == 1 && _Cols != 1 ) ? 0x1 : 0 )>
class igaMatrix : public Matrix<T, _Rows, _Cols, _Options>
{
public:
    // parent type
    using Base = Eigen::Matrix<T, _Rows, _Cols, _Options>;
    // self type
    using Self = igaMatrix<T, _Rows, _Cols, _Options>;
    // scalar type
    using Scalar_t = T;
    // alloc type
    using alloc = typename Eigen::aligned_allocator<Self>;

    // block type
    using Block = Eigen::Block<Base>;
    // const block type
    using constBlock = Eigen::Block<const Base>;

    // type of a row of the matrix
    using Row = Eigen::Block<Base, 1, _Cols, _Options == 0 ? false : true>;
    // type of a column of the matrix
    using Column = Eigen::Block<Base, _Rows, 1, _Options == 1 ? false : true>;

    using constRow = Eigen::Block<const Base, 1, _Cols, _Options == 0 ? false : true>;

    using constColumn = Eigen::Block<const Base, _Rows, 1, _Options == 1 ? false : true>;

    using Ref = Eigen::Ref<Base>;

    using constRef = Eigen::Ref<const Base>;

    using uPtr = unique_ptr<Base>;

    using sPtr = shared_ptr<Base>;

    // type of row and col minor matrix: rows and cols reduced by one
    using RowAndColMinorMatrixType = igaMatrix<T, ChangeDim<_Rows, -1>::value, ChangeDim<_Cols, -1>::value>;

    // type of row minor matrix: rows reduced by one
    using RowMinorMatrixType = igaMatrix<T, ChangeDim<_Rows, -1>::value, _Cols>;

    // type of col minor matrix: cols reduced by one
    using ColMinorMatrixType = igaMatrix<T, _Rows, ChangeDim<_Cols, -1>::value>;

public:
    igaMatrix() : Base()
    {
    }

    igaMatrix( const Base& a ) : Base( a )
    {
    }

    igaMatrix( int rows, int cols ) : Base( rows, cols )
    {
    }

    template <typename OtherDerived>
    igaMatrix& operator=( const Eigen::MatrixBase<OtherDerived>& other )
    {
        this->Base::operator=( other );
        return *this;
    }

    /// This constructor allows constructing a gsMatrix from Eigen expressions
    template <typename OtherDerived>
    igaMatrix( const Eigen::EigenBase<OtherDerived>& other ) : Base( other )
    {
    }

    /// This constructor allows constructing a gsMatrix from Eigen expressions
    template <typename OtherDerived>
    igaMatrix( const Eigen::MatrixBase<OtherDerived>& other ) : Base( other )
    {
    }

    /// This constructor allows constructing a gsMatrix from Eigen expressions
    template <typename OtherDerived>
    igaMatrix( const Eigen::ReturnByValue<OtherDerived>& other ) : Base( other )
    {
    }

    std::pair<index_t, index_t> Dim() const
    {
        return std::make_pair( this->rows(), this->cols() );
    }

    /// returns the i-th element of the vectorization of the matrix
    T At( index_t i ) const
    {
        return *( this->data() + i );
    }

    /// returns the i-th element of the vectorization of the matrix
    T& At( index_t i )
    {
        return *( this->data() + i );
    }

    // create submatrix from index container. !! now can be done by operator() directly
    template <typename IndexContainer>
    void Submatrix( const IndexContainer& rowInd, const IndexContainer& colInd, igaMatrix<T>& result ) const
    {
        const index_t nr = rowInd.size();
        const index_t nc = colInd.size();
        result.resize( nr, nc );
        for ( index_t i = 0; i != nr; ++i )
            for ( index_t j = 0; j != nc; ++j )
                result( i, j ) = this->coeff( rowInd[i], colInd[j] );
    }

    // create a allocate a unique pointer and swap this matrix with it
    uPtr MoveToPtr()
    {
        uPtr u_ptr( new igaMatrix );
        u_ptr->swap( *this );
        return u_ptr;
    }

    void clear()
    {
        this->resize( 0, 0 );
    }

    // returns a submatrix consisting of the columns indexed by the vector container colInd
    template <class IndexContainer>
    void SubmatrixCols( const IndexContainer& colInd, igaMatrix<T>& result ) const
    {
        const index_t nc = colInd.size();
        result.resize( this->rows(), nc );
        for ( index_t i = 0; i != nc; ++i )
            result.col( i ) = this->col( colInd[i] );
    }

    // returns a submatrix consisting of the rows indexed by the vector container rowInd
    template <class IndexContainer>
    void SubmatrixRows( const IndexContainer& rowInd, igaMatrix<T>& result ) const
    {
        const index_t nr = rowInd.size();
        result.resize( nr, this->cols() );
        for ( index_t i = 0; i != nr; ++i )
            result.row( i ) = this->row( rowInd[i] );
    }

    // returns a (m-1)*(n-1) matrix with i th row and j th col removed
    void ColAndRowMinor( index_t i, index_t j, RowAndColMinorMatrixType& result ) const
    {
        const index_t mrows = this->rows() - 1, mcols = this->cols() - 1;
        // GISMO_ASSERT( i <= mrows, "Invalid row." );
        // GISMO_ASSERT( j <= mcols, "Invalid column." );
        // result.resize( mrows, mcols );
        result.block( 0, 0, i, j ) = this->block( 0, 0, i, j );
        result.block( i, 0, mrows - i, j ) = this->block( i + 1, 0, mrows - i, j );
        result.block( 0, j, i, mcols - j ) = this->block( 0, j + 1, i, mcols - j );
        result.block( i, j, mrows - i, mcols - j ) = this->block( i + 1, j + 1, mrows - i, mcols - j );
    }

    template <typename DynamicMatrixType>
    void ColAndRowMinor( index_t i, index_t j, DynamicMatrixType& result ) const
    {
        const index_t mrows = this->rows() - 1, mcols = this->cols() - 1;
        // GISMO_ASSERT( i <= mrows, "Invalid row." );
        // GISMO_ASSERT( j <= mcols, "Invalid column." );
        result.resize( mrows, mcols );
        result.block( 0, 0, i, j ) = this->block( 0, 0, i, j );
        result.block( i, 0, mrows - i, j ) = this->block( i + 1, 0, mrows - i, j );
        result.block( 0, j, i, mcols - j ) = this->block( 0, j + 1, i, mcols - j );
        result.block( i, j, mrows - i, mcols - j ) = this->block( i + 1, j + 1, mrows - i, mcols - j );
    }

    //  return a (m-1)*n matrix with the i th row removed
    void RowMinor( index_t i, RowMinorMatrixType& result ) const
    {
        const index_t mrows = this->rows() - 1;
        // GISMO_ASSERT( i <= mrows, "Invalid row." );
        // result.resize( mrows, this->cols() );
        result.topRows( i ) = this->topRows( i );
        result.bottomRows( mrows - i ) = this->bottomRows( mrows - i );
    }

    template <typename DynamicMatrixType>
    void RowMinor( index_t i, DynamicMatrixType& result ) const
    {
        const index_t mrows = this->rows() - 1;
        // GISMO_ASSERT( i <= mrows, "Invalid row." );
        result.resize( mrows, this->cols() );
        result.topRows( i ) = this->topRows( i );
        result.bottomRows( mrows - i ) = this->bottomRows( mrows - i );
    }

    //  return a m*(n-1) matrix with the j th col removed
    void ColMinor( index_t j, ColMinorMatrixType& result ) const
    {
        const index_t mcols = this->cols() - 1;
        // GISMO_ASSERT( j <= mcols, "Invalid column." );
        // result.resize( this->rows(), mcols );
        result.leftCols( j ) = this->leftCols( j );
        result.rightCols( mcols - j ) = this->rightCols( mcols - j );
    }

    template <typename DynamicMatrixType>
    void ColMinor( index_t j, DynamicMatrixType& result ) const
    {
        const index_t mcols = this->cols() - 1;
        // GISMO_ASSERT( j <= mcols, "Invalid column." );
        result.resize( this->rows(), mcols );
        result.leftCols( j ) = this->leftCols( j );
        result.rightCols( mcols - j ) = this->rightCols( mcols - j );
    }

    void duplicateRow( index_t k )
    {
        IGA_UNUSED_PARAMETER( k )
        IGA_NOT_IMPLEMENTED
    }

    // remove entries close to zero
    void RemoveNoise( const T& tol )
    {
        this->noalias() = this->unaryExpr( removeNoise_helper<T>( tol ) );
    }

    // sorts rows of matrix w.r.t. values in col j.
    void SortByColumn( const index_t j )
    {
        // GISMO_ASSERT( j < this->cols(), "Invalid column." );

        index_t lastSwapDone = this->rows() - 1;
        index_t lastCheckIdx = lastSwapDone;

        bool didSwap;
        igaMatrix<T> tmp( 1, this->cols() );
        do
        { // caution! A stable sort algorithm is needed here for lexSortColumns function below
            didSwap = false;
            lastCheckIdx = lastSwapDone;

            for ( index_t i = 0; i < lastCheckIdx; i++ )
                if ( this->coeff( i, j ) > this->coeff( i + 1, j ) )
                {
                    tmp.row( 0 ) = this->row( i );
                    this->row( i ) = this->row( i + 1 );
                    this->row( i + 1 ) = tmp.row( 0 );

                    didSwap = true;
                    lastSwapDone = i;
                }
        } while ( didSwap );
    }

    // void BlockTransposeInPlace( const index_t colBlock )
    // {
    //     const index_t nc = this->cols();
    //     const index_t nr = this->rows();

    //     IGA_ASSERT( !( nc % colBlock ) );

    //     if ( nr == 1 || colBlock == 1 )
    //     {
    //         this->resize( colBlock, this->size() / colBlock );
    //     }
    //     else if ( nr == colBlock )
    //     {
    //         for ( index_t j = 0; j != nc; j += colBlock )
    //             this->middleCols( j, colBlock )
    //                 .template triangularView<Eigen::StrictlyUpper>()
    //                 .swap( this->middleCols( j, colBlock ).transpose() );
    //     }
    //     else
    //     {
    //         Eigen::Map<Base> m( this->data(), nr, nc );
    //         this->resize( colBlock, this->size() / colBlock );
    //         std::cout << m << std::endl;
    //         std::cout << m.middleCols( 2, colBlock ) << std::endl;
    //         index_t i = 0;
    //         for ( index_t j = 0; j != nc; j += colBlock, i += nr )
    //             this->middleCols( i, nr ) = m.middleCols( j, colBlock ).transpose().eval();
    //     }
    // }

    string PrintSparsity() const
    {
        ostringstream os;
        os << ", sparsity: " << std::fixed << setprecision( 2 ) << "nnz: " << this->size()
           << (double)100 * ( this->array() != 0 ).count() / this->size() << '%' << "\n";
        for ( index_t i = 0; i != this->rows(); ++i )
        {
            for ( index_t j = 0; j != this->cols(); ++j )
                os << ( 0 == this->coeff( i, j ) ? "\u00B7" : "x" );
            os << "  " << ( this->row( i ).array() != 0 ).count() << "\n";
        }
        return os.str();
    }

    // return the Kronecker product of this with other
    template <typename OtherDerived>
    igaMatrix<T, -1, -1, _Options> Kronecker( const Eigen::MatrixBase<OtherDerived>& other ) const
    {
        const index_t r = this->rows(), c = this->cols();
        const index_t ro = other.rows(), co = other.cols();
        igaMatrix<T, -1, -1, _Options> result( r * ro, c * co );
        for ( index_t i = 0; i != r; ++i )
            for ( index_t j = 0; j != c; ++j )
                result.block( i * ro, j * ro, ro, co ) = this->coeff( i, j ) * other;
        return result;
    }
    // returns the Khatri-Rao product of this with other
    template <typename OtherDerived>
    igaMatrix<T, -1, -1, _Options> KhatriRao( const Eigen::MatrixBase<OtherDerived>& other ) const
    {
        const index_t r = this->rows(), c = this->cols();
        const index_t ro = other.rows();
        // GISMO_ASSERT( c == other.cols(), "Column sizes do not match." );
        igaMatrix<T, -1, -1, _Options> result( r * ro, c );
        for ( index_t j = 0; j != c; ++j )      // for all cols
            for ( index_t i = 0; i != ro; ++i ) // for all rows
                result.block( i * r, j, r, 1 ) = this->coeff( i, j ) * other.col( j );
        return result;
    }
};

} // namespace matrix