#pragma once
#include <igaDomainIterator.hpp>
#include <igaFunctionSet.h>

namespace basis
{
using namespace std;

template <typename T>
class igaBasisFn
{
public:
    static void LinearCombinationInto( const igaMatrix<T>& coefs,
                                       const igaMatrix<index_t>& active_indices,
                                       const igaMatrix<T>& basis_values,
                                       igaMatrix<T>& reults );
};

template <typename T>
class igaBasis : public igaFunctionSet<T>
{
public:
    using Base = igaFunctionSet<T>;
    using sPtr = shared_ptr<igaBasis>;
    using uPtr = unique_ptr<igaBasis>;
    using scalar_t = T;
    using domainIter = unique_ptr<igaDomainIterator<T>>;

public:
    igaBasis() = default;

    igaBasis( const igaBasis& other ) : Base( other )
    {
    }

    virtual ~igaBasis() = default;

public:
    index_t Dim() const;

    const igaBasis<T>& Piece( const index_t patch_index ) const
    {
        IGA_REQUIRE( patch_index == 0 )
        return *this;
    }

    // evaluate a single basis function i at point(s) u
    virtual void EvalSingleInto( const index_t i, const igaMatrix<T>& u, igaMatrix<T>& result ) const;

    igaMatrix<T> EvalSingle( const index_t i, const igaMatrix<T>& u ) const
    {
        igaMatrix<T> result;
        this->EvalSingleInto( i, u, result );
        return result;
    }

    virtual domainIter MakeDomainIterator() const;
};
} // namespace basis