#pragma once

#include <igaMatrix.h>

namespace matrix
{
using namespace Eigen;
using namespace std;

template <typename T, int _Rows = Eigen::Dynamic, int _Options = 0>
class igaVector : public igaMatrix<T, _Rows, 1, _Options>
{
public:
    // The type of the coefficients of the matrix
    using Scalar_t = T;

    using igaBase = igaMatrix<T, _Rows, 1, _Options>;

    using Base = typename igaBase::Base;

    using Self = igaVector<Scalar_t, _Rows, _Options>;

    using Block = typename Eigen::Block<Base>;

    using alloc = typename Eigen::aligned_allocator<Self>;

    // shared pointer for igaVector
    using Ptr = shared_ptr<igaVector>;

    // unique pointer for igaVector
    using uPtr = unique_ptr<igaVector>;

    using Ref = typename Eigen::Ref<Base>;

    using ConstRef = const typename Eigen::Ref<const Base>;

    // Type for treating a vector as a permutation matrix
    typedef Eigen::PermutationWrapper<Base> PermutationWrap;

public:
    using iterator = T*;

    using const_iterator = const T*;

    iterator Begin()
    {
        return this->data();
    }

    const_iterator Begin() const
    {
        return this->data();
    }

    iterator End()
    {
        return this->data() + this->size();
    }

    const_iterator End() const
    {
        return this->data() + this->size();
    }

public:
    igaVector() : igaBase()
    {
    }

    igaVector( const Base& a ) : igaBase( a )
    {
    }

    igaVector( const index_t dimension ) : igaBase( dimension, 1 )
    {
    }

    /// This constructor allows constructing a gsMatrix from Eigen expressions
    template <typename OtherDerived>
    igaVector( const Eigen::EigenBase<OtherDerived>& other ) : igaBase( other )
    {
        IGA_ASSERT( other.cols() == 1 )
    }

    template <typename OtherDerived>
    igaVector( const Eigen::MatrixBase<OtherDerived>& other ) : igaBase( other )
    {
        IGA_ASSERT( other.cols() == 1 )
    }

    template <typename OtherDerived>
    igaVector( const Eigen::ReturnByValue<OtherDerived>& other ) : igaBase( other )
    {
        IGA_ASSERT( other.cols() == 1 )
    }

    template <typename OtherDerived>
    igaVector& operator=( const Eigen::MatrixBase<OtherDerived>& other )
    {
        this->Base::operator=( other );
        return *this;
    }

    inline operator Ref()
    {
        return Ref( *this );
    }

    inline operator const ConstRef()
    {
        return ConstRef( *this );
    }

    PermutationWrap AsPermutation() const
    {
        return PermutationWrap( *this );
    }

    // remove row i from the vector. After the operation the vector has size one less.
    void removeElement( const index_t i )
    {
        IGA_ASSERT( i < this->size() )
        for ( iterator c = this->data() + i + 1; c != End(); ++c )
            *( c - 1 ) = *c;
        this->conservativeResize( this->size() - 1, Eigen::NoChange );
    }

    T At( const index_t i ) const
    {
        return *( this->data() + i );
    }
    T& At( const index_t i )
    {
        return *( this->data() + i );
    }
    T Last() const
    {
        return *( this->data() + this->size() - 1 );
    }
    T& At()
    {
        return *( this->data() + this->size() - 1 );
    }
};
} // namespace matrix