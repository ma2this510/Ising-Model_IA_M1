#include <iostream>
#include <fstream>
#include <cmath>
#include <armadillo>

#include "ising.cpp"

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

int main_base() {
    vec T = linspace<vec>(3.0, 4.0, 40);
    int nrep = 50;
    int N = 40;
    int step = 1000;

    for (int i = 0; i < T.n_elem; i++) {
        cout << "T = " << T(i) << endl;
        save_couche(N, T(i), step, nrep);
    }
    return 0;
}

int main_grad() {
    string name_file = "../mydata/couche_O.O_4.0_1000.dat";
    ofstream fichier;
    fichier.open(name_file);
    vec T = linspace<vec>(0.0, 4.0, 1000);
    int N = 40;
    int step = 1000;
    for (int i = 0; i < T.size(); i++)
    {
        cout << "T = " << T(i) << endl;
        Ising2D ising(N);
        ising.temperature(T(i));
        ising.boucle(step);
        Mat<uint8_t> couche_result = ising.couche(0);
        couche_result.reshape(1, N * N);
        couche_result.save(fichier, raw_ascii);
    }
    fichier.close();
    cout << "File " << name_file << " saved" << endl;
    return 0;    
}

int main() {
    Ising2D ising(20);
    ising.temperature(4.0);
    ising.boucle(1000);
    Mat<uint8_t> couche_result = ising.couche(7);
    couche_result.save("couche.dat", raw_ascii);
    return 0;
}