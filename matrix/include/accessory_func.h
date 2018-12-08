#pragma once

namespace accessory
{
template <int Dim, int Change>
struct ChangeDim
{
    static const int value = Change + Dim < 0 ? 0 : Dim + Change;
};

template <int Change>
struct ChangeDim<-1, Change>
{
    static const int value = -1;
};

} // namespace accessory