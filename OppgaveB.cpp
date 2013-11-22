#include <iostream>
#include <cmath>
#include <fstream>
#include <ostream>
#include <sstream>
#include <ctime>
#include <armadillo>

using namespace std;
using namespace arma;


int main(int argc, char* argv[]) {

    clock_t start;
    double duration;

    int i, n;
    double *a = new double[n];
    double *b = new double[n];
    double *c = new double[n];

    cout << "Angi dimensjonen på den kvadratiske matrisen(nxn)  n=";
    cin >> n;

    start = clock();


    double *x = new double[n];
    double *f = new double[n];
    double *d = new double[n];
    double *y = new double[n];
    double xa=0.0, xb=1.0;
    double h = (xb-xa) / (n+1);

    for (i=0; i<n; i++) {
        x[i] = i*h;
        f[i] = 100*exp(-10*x[i]);
        d[i] = h*h*f[i];     
        y[i] = 1 - (1-exp(-10))*x[i] - exp(-10*x[i]); // Analyttisk løsning
    }
    for (i=0; i<n+1; i++) {
        a[i]=-1.0; b[i]=2.0; c[i]=-1.0;       
    }
    a[0]=0; c[n]=0;





// ForwardSubstitution then BackwardSubstitution
    double btemp;
    double *temp = new double[n];
    double *u = new double[n];

    btemp = b[1];
    for (i=2 ; i < n+1 ; i++) {
        temp[i] = c[i-1]/btemp;
        btemp = b[i] - a[i]*temp[i];
        u[i] = (d[i] - a[i]*u[i-1])/btemp;
    }
    for (i=n-1; i>0; i--) {
        u[i] -= temp[i+1]*u[i+1];
    }




// Hvor lang tid tar utregningen?
    duration = (clock() - start) / ((double)CLOCKS_PER_SEC/1000.0);
    cout << " Gausseliminasjonen tok : " << duration << " millisekunder" << endl;




// Sende data til fil
    char dat_time[80];
    time_t timer;
    struct tm * timeinfo;

    time(&timer);
    timeinfo = localtime(&timer);
    strftime(dat_time,80,"%a_%b_%d_%H_%M_%S.dat",timeinfo);

    ostringstream oss;
    oss << "data_n" << n << "_" << dat_time;
    string filename = oss.str();
    ofstream ofile;
    ofile.open(filename.c_str());

    for (i = 0; i < n;  i++) {
        ofile << x[i] << " " << u[i] << " " << y[i] << endl;
    }

    ofile.close();





// Relativ error
    double *epsilon = new double[n];

    for (i=1; i<n; i++) {
        epsilon[i] = log10(fabs((y[i]-u[i]) / u[i]));
    }

//maxRelativ error
    double max = -15;
    for (i=1; i<n; i++) {
        if (epsilon[i] > max) {
            max = epsilon[1];
        }
    }


/*

// LU dekomposisjon
    mat A = zeros(n,n);
    A(0,0) = 2;
    A(0,1) = -1;
    A(n-1,n-1) = 2;
    A(n-1,n-2) = -1;
    for (i=1; i<n-1; i++) {
        A(i,i) = 2; A(i,i-1) = -1; A(i,i+1) = -1;
    }

    mat L, U;
    vec r = zeros(n);
    vec s = zeros(n);

    lu(L,U,A);
    solve(r,L,d);
    solve(s,U,r);

    vec svar = zeros(n+2);
    svar(0) = 0;
    svar(n+1) = 0;
    for (i=1; i<n+1; i++) {
        svar(i)=s(i-1);
    }

*/

    return 0;
}
