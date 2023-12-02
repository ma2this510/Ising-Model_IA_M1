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
    Ising2D(int N) : N(N), Ns(N * N), spin(N, N), nspin(Ns * nbint), dev(), gen(dev()), dist_d(0, N - 1),
                     dist_c(0.0, 1.0), dist_s(0, pow(2, nbint) - 1) {
    };

    void temperature(double T) {
        double beta = 1.0 / T;
        double p0 = exp(-8.0 * beta);
        double p1 = (exp(-4.0 * beta) - p0) / (1.0 - p0);
        deuxp0 = 2.0 * p0;
        deuxp1 = 2.0 * p1;
    };

    int voisin(int i, int j) {
        int ii = i;
        if (ii < 0) {
            ii = N - 1;
        }
        else if (ii > N - 1) {
            ii = 0;
        }
        int jj = j;
        if (jj < 0) {
            jj = N - 1;
        }
        else if (jj > N - 1) {
            jj = 0;
        }
        return spin(ii, jj);
    };

    void metropolis() {
        int i = dist_d(gen);
        int j = dist_d(gen);
        int s = spin(j, i);
        int a1 = s ^ voisin(i - 1, j);
        int a2 = s ^ voisin(i + 1, j);
        int a3 = s ^ voisin(i, j - 1);
        int a4 = s ^ voisin(i, j + 1);
        int R1 = a1 | a2 | a3 | a4;
        int R2 = ((a1 | a2) & (a3 | a4)) | ((a1 & a2) | (a3 & a4));
        int r0, r1;
        if (dist_c(gen) < deuxp0) {
            r0 = dist_s(gen);
        }
        else {
            r0 = 0;
        }
        if (dist_c(gen) < deuxp1) {
            r1 = dist_s(gen);
        }
        else {
            r1 = 0;
        }
        spin(j, i) = s ^ (R2 | (R1 & r1) | r0);
    };

    double moment() {
        double m = 0.0;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                int s = spin(j, i);
                for (int b = 0; b < nbint; b++) {
                    m += 2 * (s & 1) - 1;
                    s = s >> 1;
                }
            }
        }
        return -m * 1.0 / nspin;
    };

    arma::Col<double> boucle(int n) {
        Col<double> m(n);
        for (int k = 0; k < n; k++) {
            for (int l = 0; l < Ns; l++) {
                metropolis();
            }
            m(k) = moment();
        }
        return m;
    };

    Mat<int> couche(int b) {
        Mat<int> mask(N, N, fill::ones);
        mask.for_each([&](int&element) { element *= pow(2, b); });

        Mat<int> couche_result = arma::conv_to<Mat<int>>::from(spin && mask);
        return couche_result;
    };
};

int save_moment(int N, double T, int n) {
    Ising2D ising(N);
    ising.temperature(T);
    Col<double> m = ising.boucle(n);

    ofstream fichier;
    ostringstream streamObj;
    streamObj << fixed;
    streamObj << setprecision(2);
    streamObj << T;
    string name_file = "../mydata/mag_" + to_string(N) + "_" + streamObj.str() + ".txt";
    fichier.open(name_file);
    fichier << m << endl;
    fichier.close();
    cout << "File " << name_file << " saved" << endl;

    return 0;
}

int save_couche(int N, double T, int step, int nrep) {
    ofstream fichier;
    ostringstream streamObj;
    streamObj << fixed;
    streamObj << setprecision(2);
    streamObj << T;
    string name_file = "../mydata/couche_" + to_string(N) + "_" + streamObj.str() + ".txt";
    fichier.open(name_file);

    for (int i = 0; i < nrep; i++) {
        cout << "Rep " << i << endl;
        Ising2D ising(N);
        ising.temperature(T);
        Col<double> m = ising.boucle(step);
        for (int j = 0; j < 8; j++) {
            Mat<int> couche_result = ising.couche(0);
            couche_result.reshape(1, N * N);
            couche_result.save(fichier, raw_ascii);
        }
    };

    fichier.close();
    cout << "File " << name_file << " saved" << endl;

    return 0;
}


int main_test(int argc, char** argv) {
    if (argc != 5) {
        cout << "Usage: N T step nrep" << endl;
        return 1;
    }

    int N = atoi(argv[1]);
    double T = atof(argv[2]);
    int step = atoi(argv[3]);
    int nrep = atoi(argv[4]);

    save_couche(N, T, step, nrep);

    return 0;
}
