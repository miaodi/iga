#pragma once
#include <igasFunctionSet.h>

namespace basis
{
using namespace std;
template <typename T>
class igaBasis : public igaFunctionSet<T>
{
public:
    using Base = igaFunctionSet<T>;
    using sPtr = shared_ptr<igaBasis>;
    using uPtr = unique_ptr<igaBasis>;
    using scalar_t = T;
};
} // namespace basis