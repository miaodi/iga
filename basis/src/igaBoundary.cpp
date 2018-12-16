#include <igaBoundary.h>

template <typename E>
constexpr typename std::underlying_type<E>::type to_underlying( E e ) noexcept
{
    return static_cast<typename std::underlying_type<E>::type>( e );
}

namespace basis
{
Boundary::Side BoxSideFn::Index( const index_t ind )
{
    switch ( ind )
    {
    case 1:
    {
        return Boundary::Side::West;
    }
    case 2:
    {
        return Boundary::Side::East;
    }
    case 3:
    {
        return Boundary::Side::South;
    }
    case 4:
    {
        return Boundary::Side::North;
    }
    default:
        THROW_UNHANDLED_SWITCH_CASE( ind )
    }
}

index_t BoxSideFn::Side( const Boundary::Side side )
{
    return to_underlying( side );
}

Boundary::Side BoxSideFn::GetFirstBoundarySide( const index_t dim )
{
    IGA_UNUSED_PARAMETER( dim )
    return Index( 1 );
}

Boundary::Side BoxSideFn::GetLastBoundarySide( const index_t dim )
{
    return Index( 2 * dim );
}

BoxSide BoxSideFn::GetFirstBoxSide( const index_t dim )
{
    IGA_UNUSED_PARAMETER( dim )
    return BoxSide( 1 );
}

BoxSide BoxSideFn::GetLastBoxSide( const index_t dim )
{
    return BoxSide( 2 * dim );
}

bool operator==( const BoxSide& lhs, const BoxSide& rhs )
{
    return lhs.mSide == rhs.mSide;
}

/// Print (as string) a box side
std::ostream& operator<<( std::ostream& os, const BoxSide& o )
{
    switch ( o.Index() )
    {
    case 0:
        os << "None ";
        break;
    case 1:
        os << "West ";
        break;
    case 2:
        os << "East ";
        break;
    case 3:
        os << "South";
        break;
    case 4:
        os << "North";
        break;
    // case 5:
    //     os << "front";
    //     break;
    // case 6:
    //     os << "back ";
    //     break;
    default:
        os << "side ";
        break;
    };
    os << "(" << o.Index() << ")";
    return os;
}

Boundary::Corner BoxCornerFn::Index( const index_t ind )
{
    switch ( ind )
    {
    case 1:
    {
        return Boundary::Corner::SouthWest;
    }
    case 2:
    {
        return Boundary::Corner::SouthEast;
    }
    case 3:
    {
        return Boundary::Corner::NorthWest;
    }
    case 4:
    {
        return Boundary::Corner::NorthEast;
    }
    default:
        THROW_UNHANDLED_SWITCH_CASE( ind )
    }
}

bool BoxCornerFn::East( const Boundary::Corner corner )
{
    if ( corner == Boundary::Corner::SouthEast || corner == Boundary::Corner::NorthEast )
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool BoxCornerFn::North( const Boundary::Corner corner )
{
    if ( corner == Boundary::Corner::NorthEast || corner == Boundary::Corner::NorthWest )
    {
        return true;
    }
    else
    {
        return false;
    }
}
} // namespace basis