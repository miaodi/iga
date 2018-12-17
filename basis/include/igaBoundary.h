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
    static index_t DirAndPar( const index_t, const bool );
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

    BoxSide( const index_t dir, const index_t par ) : mSide{BoxSideFn::Index( BoxSideFn::DirAndPar( dir, par ) )}
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

class BoxCorner;

class BoxCornerFn
{
public:
    static Boundary::Corner Index( const index_t );
    static index_t Corner( const Boundary::Corner );
    static bool East( const Boundary::Corner );
    static bool North( const Boundary::Corner );

    // static Boundary::Side GetFirstBoundarySide( const index_t dim = 1 );
    // static Boundary::Side GetLastBoundarySide( const index_t dim );

    static BoxCorner GetFirstBoxCorner( const index_t dim = 1 );
    static BoxCorner GetLastBoxCorner( const index_t dim );
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
    // return a dim dimensional vector of either corner at begin or end of each direction
    void ParametersInto( const index_t dim, igaVector<bool>& p ) const
    {
        IGA_ASSERT( dim == 2 )
        p.resize( dim );
        BoxCornerFn::East( mCorner ) ? p( 0 ) = true : p( 0 ) = false;
        BoxCornerFn::North( mCorner ) ? p( 1 ) = true : p( 1 ) = false;
    }
    igaVector<bool> Parameters( const index_t dim ) const
    {
        igaVector<bool> res;
        ParametersInto( dim, res );
        return res;
    }

    // return all BoxSide that intersection with this corner
    void GetContainingSides( const index_t dim, std::vector<BoxSide>& sides ) const
    {
        IGA_ASSERT( dim == 2 )
        sides.resize( dim );
        igaVector<bool> par;
        ParametersInto( dim, par );
        for ( int i = 0; i < dim; ++i )
        {
            sides[i] = BoxSide( i, par( i ) );
        }
    }

    // Increment & Decrement
    BoxCorner& operator++()
    {
        mCorner = BoxCornerFn::Index( BoxCornerFn::Corner( mCorner ) + 1 );
        return *this;
    }

    BoxCorner& operator--()
    {
        mCorner = BoxCornerFn::Index( BoxCornerFn::Corner( mCorner ) - 1 );
        return *this;
    }

    
    friend bool operator==( const BoxCorner& lhs, const BoxCorner& rhs );

protected:
    Boundary::Corner mCorner;
};
} // namespace basis