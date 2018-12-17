#include <config.h>
#include <igaBoundary.h>
#include <igaDebug.h>
#include <igaVector.h>
#include <iostream>
#include <vector>

using namespace matrix;
using namespace std;
using namespace util;
using namespace Eigen;
int main()
{
    igaMatrix<double> c = MatrixXd::Random( 3, 6 );
    for ( int i = 0; i < c.rows(); ++i )
    {
        for ( int j = 0; j < c.cols(); ++j )
        {
            c( i, j ) = c.cols() * i + j;
        }
    }

    c.BlockTransposeInPlace( 2 );

    igaVector<double> aa = MatrixXd::Random( 5, 1 );
    cout << ( aa.Last() ) << endl;
    cout << aa << endl;
    cout << std::boolalpha << ( basis::Boundary::Side::North == basis::BoxSideFn::Index( 2 ) ) << endl;
    cout << std::boolalpha << ( basis::Boundary::Side::East == basis::BoxSideFn::Index( 2 ) ) << endl;
    cout << basis::BoxSideFn::Side( basis::Boundary::Side::West ) << endl;
    cout << basis::BoxSideFn::Side( basis::Boundary::Side::East ) << endl;
    cout << basis::BoxSideFn::Side( basis::Boundary::Side::South ) << endl;
    cout << basis::BoxSideFn::Side( basis::Boundary::Side::North ) << endl;
    // basis::BoxSideFn::Index( 5 );
    cout << ( 1 << 0 ) << endl;
    cout << ( 1 << 1 ) << endl;
    cout << ( 1 << 2 ) << endl;
    // igaVector<bool> param( 2 );
    // for ( int i = 0; i < 2; ++i )
    //     param( i ) = ( ( 4 - 1 ) >> i ) & 1;
    // cout<<param<<endl;
    return 0;
}