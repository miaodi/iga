#pragma once

#include <Eigen/Dense>
#include <accessory_func.h>
#include <config.h>
#include <memory>
namespace matrix
{
using namespace Eigen;
using namespace std;
using namespace accessory;

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

    // create submatrix from index container. !! now can be done by operator() directly
    template <typename IndexContainer>
    void submatrix( const IndexContainer& rowInd, const IndexContainer& colInd, igaMatrix<T>& result ) const
    {
        const index_t nr = rowInd.size();
        const index_t nc = colInd.size();
        result.resize( nr, nc );
        for ( index_t i = 0; i != nr; ++i )
            for ( index_t j = 0; j != nc; ++j )
                result( i, j ) = this->coeff( rowInd[i], colInd[j] );
    }

    // create a allocate a unique pointer and swap this matrix with it
    uPtr moveToPtr()
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
    void submatrixCols( const IndexContainer& colInd, igaMatrix<T>& result ) const
    {
        const index_t nc = colInd.size();
        result.resize( this->rows(), nc );
        for ( index_t i = 0; i != nc; ++i )
            result.col( i ) = this->col( colInd[i] );
    }

    // returns a submatrix consisting of the rows indexed by the vector container rowInd
    template <class IndexContainer>
    void submatrixRows( const IndexContainer& rowInd, igaMatrix<T>& result ) const
    {
        const index_t nr = rowInd.size();
        result.resize( nr, this->cols() );
        for ( index_t i = 0; i != nr; ++i )
            result.row( i ) = this->row( rowInd[i] );
    }

    
};

} // namespace matrix