#include <igaFunction.h>

namespace basis
{
template <typename T>
void igaFunction<T>::DerivInto( const igaMatrix<T>& u, igaMatrix<T>& result ) const
{
    IGA_ASSERT( u.rows() == DomainDim() );

    const index_t domain_dim = DomainDim();
    const index_t target_dim = TargetDim();
    const index_t num_pts = u.cols();
    cont T h_size( 1e-6 );
    igaVector<T> delta( domain_dim );
    igaVector<T> tmp( target_dim );

    igaMatrix<T> ev, uc( domain_dim, 4 );
    result.resize( domain_dim * target_dim, num_pts );

    for ( index_t p = 0; p < num_pts; p++ ) // for all evaluation points
    {
        for ( index_t j = 0; j < domain_dim; j++ ) // for all variables
        {
            delta.setZero();
            delta( j ) = h_size;
            uc.col( 0 ) = u.col( p ) + delta;
            uc.col( 1 ) = u.col( p ) - delta;
            delta( j ) = T( 2 ) * h_size;
            uc.col( 2 ) = u.col( p ) + delta;
            uc.col( 3 ) = u.col( p ) - delta;

            this->eval_into( uc, ev );
            tmp = ( 8 * ( ev.col( 0 ) - ev.col( 1 ) ) + ev.col( 3 ) - ev.col( 2 ) ) / ( T( 12 ) * h_size );

            for ( index_t c = 0; c < target_dim; ++c ) // for all components
                result( c * domain_dim + j, p ) = tmp( c );
        }
    }
}

template <typename T>
void igaFunction<T>::JacobianInto( const igaMatrix<T>& u, igaMatrix<T>& result ) const
{
    IGA_ASSERT( u.rows() == DomainDim() );
    // Compute component gradients as columns of result
    deriv_into( u, result );

    // Reshape the matrix to get one Jacobian block per evaluation point
    const index_t d = DomainDim();         // dimension of domain
    result.resize( d, result.size() / d ); // transposed Jacobians
    result.BlockTransposeInPlace( TargetDim() );
}

template <>
class igaFunction<real_t>;
} // namespace basis