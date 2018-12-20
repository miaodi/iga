#pragma once
#include <array>
#include <igaBasis.h>

namespace basis
{
using namespace std;
template <index_t dim, typename T>
class igaTensorBasis : public igaBasis<T>
{
public:
    using sPtr = shared_ptr<gsTensorBasis>;
    using uPtr = unique_ptr<gsTensorBasis>;

    using Self_t = gsTensorBasis<d, T>;

    using Basis_t = gsBasis<T>;

    typedef Basis_t CoordinateBasis;

    /// Coefficient type
    using Scalar_t = T;

public:

    
protected:
    array<Basis_t, dim> mBasis;
};
} // namespace basis