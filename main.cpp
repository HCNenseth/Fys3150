#include <iostream>
#include "lib.h"

using namespace std;

int main(int argc, char* argv[])
{
    int i, j, n=5;
 // double a, b ,c;
    double ** matrA = new double*[n];

// cin

    for (i=0; i < n; i++) {
        for (j=0; j < n; j++)
            matrA[i][j] = 0;
        }

    matrA[0][0] = 2.0;
    matrA[0][1] = -1.0;
    for (i=1 ; i <= n-1 ; i++) {
        matrA[i][i-1] = -1.0;
        matrA[i][i] = 2.0;
        matrA[i][i+1] = -1.0;
        }


    // Then write out the matrix
    cout << " Content of matrix matr:" << endl;
    for (i = 0; i = n; i++){
        for (j = 0; j < n ; j++){
            cout << matrA[i][j] << endl;
            }
        }

// ForwardSubstitution
/*
    btemp = b[1];
    u[1] = f[1]/btemp;
    for (i=2 ; i <= n ; i++) {
        temp[i] = c[i-1]/btemp;
        btemp = b[i] - a[i]*temp[i];
        u[i] = (f[i] - a[i]*u[i-1])/btemp;
        }


// BackwardSubstitution

    for (i=n; i>=1; i++) {
        u[i] -= temp[i+1]*u[i+1];
    }

*/
    return 0;
}
