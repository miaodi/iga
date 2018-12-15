#include <igaBasis.h>

namespace basis
{
template <typename T>
void igaBasisFn<T>::LinearCombinationInto( const igaMatrix<T>& coefs,
                                           const igaMatrix<index_t>& active_indices,
                                           const igaMatrix<T>& basis_values,
                                           igaMatrix<T>& results )
{
    const index_t num_pts = basis_values.cols();
    const index_t target_dim = coefs.cols();
    const index_t stride_of_values = basis_values.rows() / active_indices.rows();

    IGA_ASSERT( basis_values.rows() % active_indices.rows() == 0 )

    results.resize( stride_of_values * target_dim, num_pts );
    results.setZero();

    // for each evaluation point
    for ( index_t pt = 0; pt < num_pts; ++pt )
    {   
        // for each activated basis function
        for ( index_t active = 0; active < active_indices.rows(); ++active )
        {
            // for each direction
            for ( index_t dir = 0; dir < target_dim; ++dir )
            {
                results.block( dir * stride_of_values, pt, stride_of_values, 1 ).noalias() +=
                    basis_values.block( stride_of_values * active, pt, stride_of_values, 1 ) *
                    coefs( active_indices( active, pt ), dir );
            }
        }
    }
}

template <typename T>
void igaBasis<T>::EvalSingleInto( const index_t, const igaMatrix<T>&, igaMatrix<T>& ) const
{
    IGA_NOT_IMPLEMENTED
}

template <>
class igaBasis<real_t>;
} // namespace basis