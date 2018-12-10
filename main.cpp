#include <igaVector.h>
#include <iostream>
#include <vector>

using namespace matrix;
using namespace std;

int main()
{
    igaMatrix<double, 3, 3> c = MatrixXd::Random(3, 3 );
    for ( int i = 0; i < c.rows(); ++i )
    {
        for ( int j = 0; j < c.cols(); ++j )
        {
            c( i, j ) = c.cols() * i + j;
        }
    }
    cout << c << endl << endl;

    // igaMatrix<double> subc;
    // igaMatrix<double, 10, 10>::RowAndColMinorMatrixType cc;
    // c.ColAndRowMinor( 2, 3, cc );
    // c.ColMinor( 2, subc );
    // cout << subc << endl;
    c.SortByColumn( 2 );
    cout << c << endl;
    cout << c.KhatriRao( c );
    return 0;
}