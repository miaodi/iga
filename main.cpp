#include <igaDebug.h>
#include <igaVector.h>
#include <iostream>
#include <vector>
#include <config.h>
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

    c.blockTransposeInPlace( 2 );
    cout << c << endl;
    return 0;
}