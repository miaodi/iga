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

    // using Ref = Eigen::Ref<Base> Ref;

    // using ConstRef = const Eigen::Ref<const Base>;
};
} // namespace matrix