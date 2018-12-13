#pragma once

#include <algorithm>
#include <string>
#include <iostream>

namespace util
{
using namespace std;

inline const char* flashred()
{
    return "\033[0;31;5m";
}
inline const char* red()
{
    return "\033[0;31m";
}
inline const char* green()
{
    return "\033[0;32m";
}
inline const char* yellow()
{
    return "\033[0;33m";
}
inline const char* blue()
{
    return "\033[0;34m";
}
inline const char* magenta()
{
    return "\033[0;35m";
}
inline const char* cyang()
{
    return "\033[0;36m";
}
inline const char* bred()
{
    return "\033[0;31;1m";
}
inline const char* bgreen()
{
    return "\033[0;32;1m";
}
inline const char* byellow()
{
    return "\033[0;33;1m";
}
inline const char* bblue()
{
    return "\033[0;34;1m";
}
inline const char* bmagenta()
{
    return "\033[0;35;1m";
}
inline const char* bcyang()
{
    return "\033[0;36;1m";
}
inline const char* purple()
{
    return "\033[38;5;91m";
}
inline const char* orange()
{
    return "\033[38;5;209m";
}
inline const char* borange()
{
    return "\033[38;5;214m";
}
inline const char* normal()
{
    return "\033[0m";
}
inline string c256f( int c )
{
    return string( "\033[38;5;" ) + to_string( c ) + "m";
}

inline ostream& resetl( ostream& o )
{
    o << normal() << endl;
    return o;
}
inline ostream& reset( ostream& o )
{
    o << normal();
    return o;
}

inline bool endsWith( const std::string& value, const std::string& ending )
{
    if ( ending.size() > value.size() )
        return false;
    return std::equal( ending.rbegin(), ending.rend(), value.rbegin() );
}

inline string toLower( const string& s )
{
    string ret;
    ret.resize( s.length() );
    std::transform( s.begin(), s.end(), ret.begin(), ::tolower );
    return ret;
}
} // namespace util