#pragma once

#include <array>
#include <igaColor.h>
#include <igaDebug.h>
#include <igaVector.h>
#include <iostream>
#include <map>
#include <tuple>

namespace util
{
using namespace std;
using namespace matrix;

template <typename T>

T Flip( const T input )
{
    return input % 2 == 0 ? 1 : -1;
}

int Factorial( const int n )
{
    int fac = 1;
    for ( int i = 1; i <= n; ++i )
    {
        fac *= i;
    }
    return fac;
}

int Binomial( const int n, const int k )
{
    auto diff = min( n - k, k );
    int res = 1;
    for ( int i = 0; i < diff; )
    {
        res *= ( n - i );
        res /= ++i;
    }
    return res;
}

// return the gramian matrix for Bernstein polynomials of degree p
template <typename T = real_t>
void GramianInto( const int p, igaMatrix<T>& res )
{
    int n = p + 1;
    res.resize( n, n );
    for ( int i = 0; i < n; i++ )
    {
        for ( int j = 0; j < n; j++ )
        {
            res( i, j ) = Binomial( p, i ) * Binomial( p, j ) / ( 2 * p + 1 ) / Binomial( 2 * p, i + j );
        }
    }
}

template <typename T = real_t>
igaMatrix<T> Gramian( const int p )
{
    igaMatrix<T> res;
    GramianInto( p, res );
    return res;
}

// return the gramian matrix's inverse for Bernstein polynomials of degree p
template <typename T = real_t>
void GramianInverseInto( const int p, igaMatrix<T>& res )
{
    int n = p + 1;
    res.resize( n, n );
    for ( int i = 0; i < n; i++ )
    {
        for ( int j = 0; j < n; j++ )
        {
            T sum = 0;
            for ( int k = 0; k <= std::min( i, j ); k++ )
            {
                sum += ( 2 * k + 1 ) * Binomial( p + k + 1, p - i ) * Binomial( p - k, p - i ) *
                       Binomial( p + k + 1, p - j ) * Binomial( p - k, p - j );
            }
            res( i, j ) = sum * pow( -1, i + j ) / Binomial( p, i ) / Binomial( p, j );
        }
    }
}

template <typename T = real_t>
igaMatrix<T> GramianInverse( const int p )
{
    igaMatrix<T> res;
    GramianInverseInto( p, res );
    return res;
}

// Algorithm 2.1 in Nurbs book
template <typename T, typename KV_type>
index_t FindSpan( const KV_type& knot_vector, const int deg, const T u )
{
    IGA_ASSERT( u >= knot_vector[0] && u <= knot_vector[knot_vector.size() - 1] )
    const index_t dof = knot_vector.size() - deg - 1;
    if ( u >= knot_vector[dof] )
        return dof - 1;
    if ( u <= knot_vector[deg] )
        return deg;

    index_t low = 0;
    index_t high = dof + 1;
    index_t mid = ( low + high ) / 2;

    while ( u < knot_vector[mid] || u >= knot_vector[mid + 1] )
    {
        if ( u < knot_vector[mid] )
            high = mid;
        else
            low = mid;
        mid = ( low + high ) / 2;
    }
    return mid;
}

template <typename T>
void AllBernsteinInto( igaMatrix<T>& evals, const index_t p, const igaMatrix<T>& u )
{
    IGA_ASSERT( u.rows() == 1 )
    evals.resize( p + 1, u.cols() );
    for ( int u_i = 0; u_i < u.cols(); ++u_i )
    {
        IGA_ASSERT( u( 0, u_i ) >= 0 && u( 0, u_i ) <= 1 )

        evals( 0, u_i ) = 1;
        T u1 = 1 - u( 0, u_i );
        T saved, temp;
        int j, k;
        for ( j = 1; j <= p; ++j )
        {
            saved = 0;
            for ( k = 0; k < j; ++k )
            {
                temp = evals( k, u_i );
                evals( k, u_i ) = saved + u1 * temp;
                saved = u( 0, u_i ) * temp;
            }
            evals( j, u_i ) = saved;
        }
    }
}
template <typename T>
igaMatrix<T> AllBernstein( const index_t p, const igaMatrix<T>& u )
{
    igaMatrix<T> eval;
    AllBernsteinInto<T>( eval, p, u );
    return eval;
}

// construct the derivative operator for Bernstein basis s.t.
//  B^p = op* B^(p-der)
template <typename T>
void BernsteinDerivOpInto( const index_t p, const index_t der, igaMatrix<T>& op )
{
    IGA_ASSERT( der <= p && der >= 0 )

    op.resize( p + 1, p + 1 - der );

    for ( int i = 0; i < p + 1; ++i )
    {
        for ( int k = max( 0, i + der - p ); k <= min( i, der ); ++k )
        {
            op( i, i - k ) = Flip( k + der ) * Binomial( der, k );
        }
    }
    T coeff = Factorial( p ) / Factorial( p - der );
    op *= coeff;
}

template <class Fn, class... Args>
chrono::duration<double> RTimer( Fn fn, Args... args )
{
    auto start = std::chrono::high_resolution_clock::now();
    fn( args... );
    auto end = std::chrono::high_resolution_clock::now();
    return end - start;
}

// print out time consumed by given lambda
template <class Fn, class... Args>
void TimerPrint( Fn fn, Args... args )
{
    auto start = std::chrono::high_resolution_clock::now();
    fn( args... );
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << cyang() << "test function took " << chrono::duration_cast<chrono::milliseconds>( end - start ).count()
              << " milliseconds\n";
}

} // namespace util