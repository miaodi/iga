#pragma once

#include <igaFunctionSet.h>
#include <igaVector.h>

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

    using scalar_t = T;

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

    virtual void ActiveInto( const igaMatrix<T>& u, igaMatrix<index_t>& indices_of_each_point ) const override
    {
        indices_of_each_point.setConstant( 1, u.cols(), 0 );
    }

    // evaluate the comp's component in targetDim at point(s) u into result
    virtual void EvalComponentInto( const igaMatrix<T>& u, const index_t comp, igaMatrix<T>& result ) const;

    virtual void EvalInto( const igaMatrix<T>& u, igaMatrix<T>& result ) const override;

    // evaluate derivatives of the function at point(s) u into result, central differences with h=1e-6. Override is required for accuracy
    virtual void DerivInto( const igaMatrix<T>& u, igaMatrix<T>& result ) const override;

    virtual void Deriv2Into( const igaMatrix<T>& u, igaMatrix<T>& result ) const override;

    // evaluate jacobian at each point(s)
    void JacobianInto( const igaMatrix<T>& u, igaMatrix<T>& result ) const;

    igaMatrix<T> Jacobian( const igaMatrix<T>& u ) const;

    virtual T L2Distance( const igaFunction<T>& ) const
    {
        IGA_NOT_IMPLEMENTED
    }

    bool NewtonRaphson( const igaVector<T>& value,
                        igaVector<T>& arg,
                        bool has_support = true,
                        const T tol = 1e-6,
                        int max_loop = 100,
                        T damping_factor = 1 ) const;
};
} // namespace basis