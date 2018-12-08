#include <igaMatrix.h>
#include <iostream>
#include <vector>

using namespace matrix;
using namespace std;

int main()
{
    igaMatrix<double, 10, 10> c;
    for ( int i = 0; i < 10; ++i )
    {
        for ( int j = 0; j < 10; ++j )
        {
            c( i, j ) = 10 * i + j;
        }
    }
    cout << c << endl;
    igaMatrix<double> subc;
    vector<int> a{1, 2, 5};
    c.submatrixRows( a, subc );
    cout << subc << endl;
    auto ptr = c.moveToPtr();
    cout << *ptr << endl;
    return 0;
}