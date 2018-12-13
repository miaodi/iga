#pragma once
#include <config.h>
#include <igaMatrix.h>
#include <iostream>
#include <memory>

namespace basis
{
using namespace std;
using namespace matrix;

template <typename T>
class igaFunction;

template <typename T>
class igaFunctionSet
{
public:
    using sPtr = shared_ptr<igaFunctionSet>;
    using uPtr = unique_ptr<igaFunctionSet>;
    using dim_t = pair<index_t, index_t>;

public:
    igaFunctionSet();

    igaFunctionSet( const igaFunctionSet& );

    virtual ~igaFunctionSet();

    // returns function set on given patch
    virtual const igaFunctionSet& Piece( const index_t patch_index )
    {
        return *this;
    }

    // // returns function on given patch
    // virtual const igaFunction<T>& Function( const index_t patch_index );

    // returns the support of the function(s), result is given as a dx2 matrix, containing the two diagonally extreme corners of a hypercube.
    virtual igaMatrix<T> Support() const;

    // returns indices of active function(s) for n points. Input u is of dimension dxn. Each columns of output is sorted in ascending order.
    virtual void ActiveInto( const igaMatrix<T>& u, igaMatrix<index_t>& indices_of_each_point ) const;

    igaMatrix<index_t> Active( const igaMatrix<T>& u ) const
    {
        igaMatrix<index_t> ioep;
        this->ActiveInto( u, ioep );
        return ioep;
    }

    // evaluates the function(s) at each points.
    virtual void EvalInto( const igaMatrix<T>& u, igaMatrix<T>& evaluations_of_each_point ) const;

    igaMatrix<T> Eval( const igaMatrix<T>& u ) const
    {
        igaMatrix<T> eoep;
        this->EvalInto( u, eoep );
        return eoep;
    }

    // evaluates the function(s)'s first order derivatives at each points.
    virtual void DerivInto( const igaMatrix<T>& u, igaMatrix<T>& evaluations_of_each_point ) const;

    igaMatrix<T> Deriv( const igaMatrix<T>& u ) const
    {
        igaMatrix<T> eoep;
        this->DerivInto( u, eoep );
        return eoep;
    }

    // evaluates the function(s)'s second order derivatives at each points.
    virtual void DerivInto2( const igaMatrix<T>& u, igaMatrix<T>& evaluations_of_each_point ) const;

    igaMatrix<T> Deriv2( const igaMatrix<T>& u ) const
    {
        igaMatrix<T> eoep;
        this->DerivInto( u, eoep );
        return eoep;
    }

    // evaluate the nonzero functions and their derivatives up to order p
    virtual void EvalAllDersInto( const igaMatrix<T>& u, int p, std::vector<igaMatrix<T>>& result ) const;

    // dimension of the (source) domain
    virtual int DomainDim() const = 0;

    // dimension of the (target) domain
    virtual int TargetDim() const
    {
        return 1;
    }

    // pair of source domain dim and target domain dim
    dim_t Dimensions() const
    {
        return make_pair( DomainDim(), TargetDim() );
    }

    // number of functions
    virtual index_t Size() const = 0;

    // number of pieces
    virtual index_t NumPieces() const
    {
        return 1;
    }

    // prints the object as a string.
    virtual std::ostream& print( std::ostream& os ) const // = 0;
    {
        os << "gsFunctionSet\n";
        return os;
    }
};

// print (as string) operator to be used by all derived classes
template <class T>
std::ostream& operator<<( std::ostream& os, const igaFunctionSet<T>& b )
{
    return b.print( os );
}

} // namespace basis