#include <iostream>
#include <fstream>
#include <cmath>
#include <armadillo>
#include "ising.h"

using namespace std;

int main_moment() {
    vec T = linspace<vec>(0.0, 4.0, 100);
    int nrep = 15;
    mat m = zeros<mat>(T.n_elem, 3);

    cout << "Start..." << endl;
    for (int i = 0; i < T.n_elem; i++) {
        cout << "T = " << T(i) << endl;
        vec mtemp = zeros<vec>(nrep);
        m(i, 0) = T(i);
        for (int j = 0; j < nrep; j++) {
            Ising2D ising(40);
            ising.temperature(T(i));
            ising.boucle(1000);
            mtemp(j) = ising.moment();
        }
        m(i, 1) = mean(mtemp);
        m(i, 2) = stddev(mtemp);
    }
    cout << "Done." << endl;
    cout << "Saving..." << endl;
    ofstream file("moment.dat");
    file << "# T M" << endl;
    file << m << endl;
    file.close();
    cout << "Saved at moment.dat" << endl;
    return 0;
}

int main() {
    vec T = linspace<vec>(3.0, 4.0, 40);
    int nrep = 50;
    int N = 40;
    int step = 1000;

    for (int i = 0; i < T.n_elem; i++) {
        cout << "T = " << T(i) << endl;
        save_couche(N, T(i), step, nrep);
    }
}