#include <igaFunctionSet.h>

namespace basis
{
template <typename T>
void igaFunctionSet<T>::ActiveInto( const igaMatrix<T>&, igaMatrix<index_t>& ) const
{
    IGA_NOT_IMPLEMENTED
}

template <typename T>
void igaFunctionSet<T>::EvalInto( const igaMatrix<T>&, igaMatrix<T>& ) const
{
    IGA_NOT_IMPLEMENTED
}

template <typename T>
void igaFunctionSet<T>::DerivInto( const igaMatrix<T>&, igaMatrix<T>& ) const
{
    IGA_NOT_IMPLEMENTED
}

template <typename T>
void igaFunctionSet<T>::Deriv2Into( const igaMatrix<T>&, igaMatrix<T>& ) const
{
    IGA_NOT_IMPLEMENTED
}

template <typename T>
void igaFunctionSet<T>::EvalAllDersInto( const igaMatrix<T>& u, int p, std::vector<igaMatrix<T>>& result ) const
{
    result.resize( p + 1 );

    switch ( p )
    {
    case 0:
        EalInto( u, result[0] );
        break;
    case 1:
        EalInto( u, result[0] );
        DerivInto( u, result[1] );
        break;
    case 2:
        EalInto( u, result[0] );
        DerivInto( u, result[1] );
        Deriv2Into( u, result[2] );
        break;
    default:
        THROW_UNHANDLED_SWITCH_CASE( p )
        break;
    }
}

template <>
class igaFunctionSet<real_t>;

} // namespace basis