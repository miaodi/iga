#pragma once

#include <igaFunctionSet.h>

namespace basis
{
using namespace std;
template <typename T>
class igaFunction : public igaFunctionSet<T>
{
public:
    using Base = igaFunctionSet<T>;
    using sPtr = shared_ptr<igaFunction>;
    using uPtr = unique_ptr<igaFunction>;

    using dim_t = typename Base::dim_t;
    using Base::DomainDim;
    using Base::Support;
    using Base::TargetDim;

public:
    igaFunction() = default;
    igaFunction( const igaFunction& ) = default;
    ~igaFunction() = default;

    virtual const igaFunction& Function( const index_t patch_index ) const
    {
        return static_cast<const igaFunction&>( this->Piece( patch_index ) );
    }

    // evaluate the comp's component in targetDim at point(s) u into result
    virtual void EvalComponentInto( const igaMatrix<T>& u, const index_t comp, igaMatrix<T>& result ) const;

    // evaluate derivatives of the function at point(s) u into result, central differences with h=1e-6. Override is required for accuracy
    virtual void DerivInto( const igaMatrix<T>& u, igaMatrix<T>& result ) const;

    // evaluate jacobian at each point(s) 
    void JacobianInto( const igaMatrix<T>& u, igaMatrix<T>& result ) const;
};
} // namespace basis