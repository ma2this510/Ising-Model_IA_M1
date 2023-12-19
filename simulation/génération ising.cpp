#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <thread>
#include <mutex>
#include <fstream>
#include <string>

using namespace std;

mutex mtx;

vector<int> uniform_entier(mt19937& gen, int size, int N) {
    uniform_int_distribution<int> dis(1, size);
    vector<int> result;
    result.reserve(2 * size * size * N);

    for (int i = 0; i < 2 * size * size * N; ++i) {
        result.push_back(dis(gen));
    }

    return result;
}

vector<double> uniform_continue(mt19937& gen, int size, int N) {
    uniform_real_distribution<double> dis(0.0, 1.0);
    vector<double> result;
    result.reserve(size * size * N);

    for (int i = 0; i < size * size * N; ++i) {
        result.push_back(dis(gen));
    }

    return result;
}

vector<vector<int>> create_matrix_with_ratio(mt19937& gen, int size, double ratio) {
    uniform_real_distribution<double> dis(0.0, 1.0);
    vector<vector<int>> matrix(size + 2, vector<int>(size + 2, 0));

    for (int i = 0; i < size + 2; ++i) {
        for (int j = 0; j < size + 2; ++j) {
            if (dis(gen) < ratio) {
                matrix[i][j] = 1;
            }
        }
    }

    return matrix;
}

int print_tab(const vector<vector<int>>& tab, int size) {
    for (int i = 1; i < size + 1; i++) {
        for (int j = 1; j < size + 1; j++) {
            cout << tab[i][j];
        }
        cout << endl;
    }

    return 0;
}

int calcul_DE(const vector<vector<int>>& tab, int x, int y, int size) {
    if ((x >= 1 && x < size + 1) && (y >= 1 && y < size + 1)) {
        int centre = tab[x][y] * 2 - 1;
        int aleft = tab[x][y - 1] * 2 - 1;
        int aup = tab[x - 1][y] * 2 - 1;
        int aright = tab[x][y + 1] * 2 - 1;
        int abottom = tab[x + 1][y] * 2 - 1;
        return 2 * centre * (aup + aleft + abottom + aright);
    }
    else {
        return 1111111;
    }
    return 2222222;
}

vector<double> precalculated_DE(double T) {
    double exp4 = exp(-4.0 / T);
    double exp8 = exp(-8.0 / T);
    return { exp4, exp8 };
}

int test(int DE, const vector<double>& precalculated_values, double x) {
    if (DE == 0 || DE == -4 || DE == -8) {
        return 1;
    }
    if (DE == 4 || DE == 8) {
        return x < precalculated_values[(int)DE / 4 - 1];
    }
    else {
        cout << DE << endl;
        cout << "error test" << endl;
        return 100;
    }
}

double M(const vector<vector<int>>& tab, int size) {
    double somme = 0;
    for (int i = 1; i < size + 1; i++) {
        for (int j = 1; j < size + 1; j++)
            somme += tab[i][j];
    }
    cout << somme << endl;
    return abs(-1 * (size * size - somme) + somme) / (size * size);
}

void parallel_work(vector<vector<int>>& tab, const vector<int>& vector_entier, const vector<double>& x,
    const vector<double>& expo, int size, int start, int end) {
    for (int i = start; i < end; ++i) {
        int DE = calcul_DE(tab, vector_entier[i * 2], vector_entier[i * 2 + 1], size);

        if (test(DE, expo, x[i]) == 1) {
            if (tab[vector_entier[i * 2]][vector_entier[2 * i + 1]] == 1) {
                tab[vector_entier[i * 2]][vector_entier[2 * i + 1]] = 0;
            }
            else {
                tab[vector_entier[i * 2]][vector_entier[2 * i + 1]] = 1;
            }
        }
    }
}

// Fonction pour sauvegarder une matrice dans un fichier DAT
void save_matrix_as_dat(const vector<int>& matrix, const string& filename, int size) {
    ofstream file(filename, ios::binary);
    if (!file.is_open()) {
        cerr << "Unable to open file: " << filename << endl;
        return;
    }

    file.write(reinterpret_cast<const char*>(matrix.data()), size * size * sizeof(int));

    file.close();
    cout << "Matrix written to file: " << filename << endl;
}

// Fonction pour sauvegarder un vecteur dans un fichier DAT
void save_vector_as_dat(const vector<vector<int>>& matrices, const string& filename, int size) {
    ofstream file(filename, ios::binary);
    if (!file.is_open()) {
        cerr << "Unable to open file: " << filename << endl;
        return;
    }

    for (const auto& matrix : matrices) {
        file.write(reinterpret_cast<const char*>(matrix.data()), size * size * sizeof(int));
    }

    file.close();
    cout << "Total elements written to file: " << matrices.size() * size * size << endl;
}

vector<vector<int>> save_without_borders(const vector<vector<int>>& tab) {
    // Créer une nouvelle matrice sans les bords
    vector<vector<int>> result(tab.size()-2, vector<int>(tab.size() - 2, 0));

    // Copier les éléments nécessaires
    for (int i = 0; i < tab.size() - 2; ++i) {
        for (int j = 0; j < tab.size() - 2; ++j) {
            result[i][j] = tab[i+1][j+1];
        }
    }

    return result;
}

int main() {
    int size = 40;
    double T = 0.1;
    double ratio = 0.35;
    int N_pas = 1000;

    random_device rd;
    mt19937 gen(rd());

    vector<double> x = uniform_continue(gen, size, N_pas);
    vector<int> vector_entier = uniform_entier(gen, size, N_pas);
    vector<double> expo = precalculated_DE(T);

    int num_threads = thread::hardware_concurrency();
    int chunk_size = size * size * N_pas / num_threads;

    // Déclaration du vecteur global
    vector<vector<int>> all_matrices;

    for (int j = 0; j < 100; j++) {
        vector<vector<int>> tab = create_matrix_with_ratio(gen, size, ratio);
        //print_tab(tab, size);

        vector<thread> threads;

        for (int i = 0; i < num_threads; ++i) {
            int start = i * chunk_size;
            int end = (i == num_threads - 1) ? size * size * N_pas : (i + 1) * chunk_size;
            threads.emplace_back(parallel_work, ref(tab), ref(vector_entier), ref(x), ref(expo), size, start, end);
        }

        for (auto& t : threads) {
            t.join();
        }
        vector<int> flattened_matrix;

        // Aplatir uniquement les lignes de 1 à size (inclus)
        for (int i = 0; i < size; ++i) {
            flattened_matrix.insert(flattened_matrix.end(), tabo[i].begin(), tabo[i].end());
        }

        // Ajoutez la matrice au vecteur global
        all_matrices.push_back(flattened_matrix);
    }

    // Enregistrez toutes les matrices dans un seul fichier DAT
    save_vector_as_dat(all_matrices, "output_all.dat", size);

    return 0;
}
