#pragma once

#include <igaColor.h>
#include <iostream>
#include <sstream>

namespace util
{
using namespace std;

class IGXException
{
public:
    IGXException( string str ) : mDesc( str )
    {
    }
    string mDesc;
};

inline ostream& operator<<( ostream& out, const IGXException& ex )
{
    out << ex.mDesc;
    return out;
}

/// print mesg and exit
inline void exit_message( const string mesg = "No Exit Message Given" )
{
    cout << mesg << endl;
    exit( 1 );
}
inline void exit_message( const char* mesg = "No Exit Message Given" )
{
    cout << mesg << endl;
    exit( 1 );
}

/// print mesg and exit if a is true
inline void exit_if( bool a, const char* mesg = "exit_if has exited" )
{
    if ( a )
    {
        exit_message( mesg );
    }
}

/// print mesg and exit if a is false
inline void exit_unless( bool a, const char* mesg = "exit_unless has exited" )
{
    if ( !a )
    {
        exit_message( mesg );
    }
}
#define COUT_THROW_EXCEPTION( E, A )                \
    do                                              \
    {                                               \
        std::stringstream sstream;                  \
        sstream << util::bred() << A;               \
        std::cout << sstream.str() << util::resetl; \
        throw E( sstream.str() );                   \
    } while ( 0 );

#define COUT_THROW_EXCEPTION_AT( E, A )                                                                                         \
    do                                                                                                                          \
    {                                                                                                                           \
        std::stringstream sstream;                                                                                              \
        sstream << util::bred() << A << " at " << __PRETTY_FUNCTION__ << " in " << __FILE__ << ":" << __LINE__ << util::resetl; \
        std::cout << sstream.str();                                                                                             \
        throw E( sstream.str() );                                                                                               \
    } while ( 0 );

#define COUT_THROW_IGXEXCEPTION( A )                                                                                            \
    do                                                                                                                          \
    {                                                                                                                           \
        std::stringstream sstream;                                                                                              \
        sstream << util::bred() << A << " at " << __PRETTY_FUNCTION__ << " in " << __FILE__ << ":" << __LINE__ << util::resetl; \
        std::cout << sstream.str();                                                                                             \
        throw util::IGXException( sstream.str() );                                                                              \
    } while ( 0 );

#define LOG_EXCEPTION_AT( F, A )                                                                          \
    do                                                                                                    \
    {                                                                                                     \
        F << A << " at " << __PRETTY_FUNCTION__ << " in " << __FILE__ << ":" << __LINE__ << util::resetl; \
    } while ( 0 );

#define IGA_NOT_IMPLEMENTED                                                                                       \
    do                                                                                                            \
    {                                                                                                             \
        COUT_THROW_EXCEPTION( util::IGXException, "NOT IMPLEMENTED " << __PRETTY_FUNCTION__ << " in " << __FILE__ \
                                                                     << ":" << __LINE__ << util::resetl );        \
    } while ( 0 );

#define THROW_NOT_IMPLEMENTED IGX_NOT_IMPLEMENTED
#define IGX_NOT_IMPLEMENTED_WARN                                                                           \
    do                                                                                                     \
    {                                                                                                      \
        stringstream sstream;                                                                              \
        sstream << bred() << "NOT IMPLEMENTED"                                                             \
                << " at " << __PRETTY_FUNCTION__ << " in " << __FILE__ << ":" << __LINE__ << util::resetl; \
        cout << sstream.str();                                                                             \
    } while ( 0 );

#define THROW_UNHANDLED_SWITCH_CASE( case )                                                                                     \
    do                                                                                                                          \
    {                                                                                                                           \
        COUT_THROW_EXCEPTION( util::IGXException, "SWITCH CASE NON HANDLED " << case << " in " << __PRETTY_FUNCTION__ << " in " \
                                                                             << __FILE__ << ":" << __LINE__ << util::resetl );  \
    } while ( 0 );

#ifndef NDEBUG
#define IGA_ASSERT( EXPR )                                                                                         \
    do                                                                                                             \
    {                                                                                                              \
        if ( not( EXPR ) )                                                                                         \
        {                                                                                                          \
            COUT_THROW_EXCEPTION( util::IGXException, #EXPR << " assert failed "                                   \
                                                            << " in " << __PRETTY_FUNCTION__ << " in " << __FILE__ \
                                                            << ":" << __LINE__ << util::resetl );                  \
        }                                                                                                          \
    } while ( 0 );
#else
#define IGA_ASSERT( EXPR )
#endif

#define IGA_REQUIRE( EXPR )                                                                                        \
    do                                                                                                             \
    {                                                                                                              \
        if ( not( EXPR ) )                                                                                         \
        {                                                                                                          \
            COUT_THROW_EXCEPTION( util::IGXException, #EXPR << " requirement failed "                              \
                                                            << " in " << __PRETTY_FUNCTION__ << " in " << __FILE__ \
                                                            << ":" << __LINE__ << util::resetl );                  \
        }                                                                                                          \
    } while ( 0 );

#define IGA_UNUSED_PARAMETER( expr ) do { (void)(expr); } while (0);

} // namespace util