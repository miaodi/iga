#pragma once
#include <igaVector.h>
#include <memory>

namespace basis
{
using namespace std;
using namespace matrix;

template <typename T>
class igaBasis;

template <typename T>
class igaDomainIterator
{
public:
    using sPtr = shared_ptr<igaDomainIterator>;
    using uPtr = unique_ptr<igaDomainIterator>;

public:
    // constructor
    explicit igaDomainIterator( igaBasis<T>& basis )
        : mBasis{basis}, mCenter{igaVector<T>::Zero( basis.Dim() )}, mLast{true}
    {
    }

    virtual ~igaDomainIterator() = default;

    // disable copy and default constructor
    igaDomainIterator() = delete;
    igaDomainIterator( const igaDomainIterator& ) = delete;
    igaDomainIterator& operator=( const igaDomainIterator& ) = delete;

public:
    // proceed to the next element, return true if next is not the last element
    virtual bool Next() = 0;

    // proceed to the next n^th element, return true if nextn is not the last element
    virtual bool NextN( const index_t n ) = 0;

    // reset to the first element
    virtual void Reset()
    {
        IGA_NOT_IMPLEMENTED
    }

    // is the iterator pointing to the last element?
    bool Last() const
    {
        return mLast;
    }

    // dimension of parametric domain
    index_t Dim() const
    {
        return mCenter.size();
    }

    // the center of the current element
    const igaVector<T>& CenterPoint() const
    {
        return mCenter;
    }

    // the lower corner of the current element
    const igaVector<T>& LowerCornerPoint() const
    {
        IGA_NOT_IMPLEMENTED
    }

    // the upper corner of the current element
    const igaVector<T>& UpperCornerPoint() const
    {
        IGA_NOT_IMPLEMENTED
    }

protected:
    // the basis on which the domain iterator is defined
    igaBasis<T>& mBasis;
    // central point of the element in parametric domain
    igaVector<T> mCenter;
    // status of the iterator
    bool mLast;
};

} // namespace basis