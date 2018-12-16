#pragma once
#include <config.h>
#include <igaDebug.h>
#include <igaVector.h>

// currently, I only consider 2D parametric domain
namespace basis
{
using namespace matrix;
// boundary enumerators
namespace Boundary
{
enum class Side
{
    None = 0,
    West,
    East,
    South,
    North
};

enum class Corner
{
    SouthWest = 1,
    SouthEast,
    NorthWest,
    NorthEast
};
} // namespace Boundary

class BoxSide;
class BoxSideFn
{
public:
    static Boundary::Side Index( const index_t );
    static index_t Side( const Boundary::Side );
    static Boundary::Side GetFirstBoundarySide( const index_t dim = 1 );
    static Boundary::Side GetLastBoundarySide( const index_t dim );
    static BoxSide GetFirstBoxSide( const index_t dim = 1 );
    static BoxSide GetLastBoxSide( const index_t dim );
};

class BoxSide
{
public:
    BoxSide() : mSide{Boundary::Side::South}
    {
    }

    BoxSide( const index_t ind ) : mSide{BoxSideFn::Index( ind )}
    {
    }

    BoxSide( Boundary::Side side ) : mSide{side}
    {
    }

public:
    // return the parametric direction that is orthogonal to the boxside.
    // which is also the direction that is fixed to obtain this boundary
    index_t Direction() const
    {
        return ( Index() - 1 ) / 2;
    }

    // return false if the fixed direction is at begin
    // return true if the fixed direction is at end
    bool Parameter() const
    {
        return ( Index() - 1 ) % 2;
    }

    BoxSide Opposite() const
    {
        switch ( mSide )
        {
        case Boundary::Side::East:
        {
            return BoxSide( Boundary::Side::West );
        }
        case Boundary::Side::West:
        {
            return BoxSide( Boundary::Side::East );
        }
        case Boundary::Side::South:
        {
            return BoxSide( Boundary::Side::North );
        }
        case Boundary::Side::North:
        {
            return BoxSide( Boundary::Side::South );
        }
        default:
            COUT_THROW_IGA_EXCEPTION( "wierd things happen\n" )
        }
    }

    index_t Index() const
    {
        return BoxSideFn::Side( mSide );
    }

    // Increment & Decrement
    BoxSide& operator++()
    {
        mSide = BoxSideFn::Index( BoxSideFn::Side( mSide ) + 1 );
        return *this;
    }
    BoxSide& operator--()
    {
        mSide = BoxSideFn::Index( BoxSideFn::Side( mSide ) - 1 );
        return *this;
    }

    friend bool operator==( const BoxSide& lhs, const BoxSide& rhs );

protected:
    Boundary::Side mSide;
};
// print BoxSide object
std::ostream& operator<<( std::ostream& os, const BoxSide& o );

class BoxCornerFn
{
public:
    static Boundary::Corner Index( const index_t );
    static index_t Corner( const Boundary::Side );
    static bool East( const Boundary::Corner );
    static bool North( const Boundary::Corner );

    // static Boundary::Side GetFirstBoundarySide( const index_t dim = 1 );
    // static Boundary::Side GetLastBoundarySide( const index_t dim );
    // static BoxSide GetFirstBoxSide( const index_t dim = 1 );
    // static BoxSide GetLastBoxSide( const index_t dim );
};

class BoxCorner
{
public:
    BoxCorner() : mCorner{Boundary::Corner::SouthWest}
    {
    }
    BoxCorner( Boundary::Corner corner ) : mCorner{corner}
    {
    }
    BoxCorner( const index_t ind ) : mCorner{BoxCornerFn::Index( ind )}
    {
    }

public:
    void ParametersInto( index_t dim, igaVector<bool>& p ) const
    {
        IGA_ASSERT( dim == 2 )
        p.resize( dim );
        BoxCornerFn::East( mCorner ) ? p( 0 ) = true : p( 0 ) = false;
        BoxCornerFn::North( mCorner ) ? p( 1 ) = true : p( 1 ) = false;
    }

protected:
    Boundary::Corner mCorner;
};
} // namespace basis