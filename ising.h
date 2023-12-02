#ifndef ISING_H
#define ISING_H

#include <iostream>
#include <cmath>
#include <random>
#include <armadillo>
#include <fstream>
#include <iomanip>

using namespace std;
using namespace arma;

class Ising2D {
    int N;
    int Ns;
    Mat<int> spin;
    int nbint = 8;
    int nspin;
    double deuxp0, deuxp1;
    random_device dev;
    mt19937 gen;
    uniform_int_distribution<int> dist_d;
    uniform_real_distribution<double> dist_c;
    uniform_int_distribution<int> dist_s;

public:
    Ising2D(int N);

    void temperature(double T);

    int voisin(int i, int j);

    void metropolis();

    double moment();

    arma::Col<double> boucle(int n);

    Mat<int> couche(int b);
};

int save_moment(int N, double T, int n);

int save_couche(int N, double T, int step, int nrep);

int main_test(int argc, char** argv);

#endif //ISING_H
