#include <random>
#include <iostream>
#include<vector>
#include <chrono>
#include <cmath>
//#include <omp.h>
using namespace std;


int uniform_entier(int size) {
	int currentTime_un = chrono::duration_cast<chrono::nanoseconds>(
		chrono::system_clock::now().time_since_epoch()
		).count();
	unsigned int amorce = currentTime_un;

	mt19937 gen(amorce);
	uniform_real_distribution< double > dis(0.0, size);
	double Nx = dis(gen);
	int x = (int)Nx;


	return (x);
}
double uniform_continue(int size) {
	int currentTime_un = chrono::duration_cast<chrono::nanoseconds>(
		chrono::system_clock::now().time_since_epoch()
		).count();
	unsigned int amorce = currentTime_un;

	mt19937 gen(amorce);
	uniform_real_distribution< double > dis(0.0, size);
	double x = dis(gen);

	return (x);
}
vector <vector <int>>  matrice(int size) {

	vector <vector <int>> tab(size, vector<int>(size));

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++)
		{
			tab[i][j] = 0;

		};
	}
	return(tab);
}
int print_tab(vector <vector <int>> tab, int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++)
		{
			cout << tab[i][j];
		};
		cout << endl;
	}
	return(0);
}
int calcul_DE(vector <vector <int>> tab, int x, int y, int size) {
	int centre = tab[x][y] * 2 - 1;
	if ((x == 0) && (y == 0)) {
		//cout << "1"<<endl;
		int aleft = tab[0][size - 1] * 2 - 1;
		int aup = tab[size - 1][0] * 2 - 1;
		int aright = tab[0][1] * 2 - 1;
		int abottom = tab[1][0] * 2 - 1;
		return(2 * centre * (aup + aleft + abottom + aright));
	}
	if ((x == size - 1) && (y == 0)) {
		//cout << "2"<<endl;
		int aleft = tab[size-1][size-1] * 2 - 1;
		int aup = tab[size - 2][0] * 2 - 1;
		int aright = tab[size - 1][1] * 2 - 1;
		int abottom = tab[0][0] * 2 - 1;
		return(2 * centre * (aup + aleft + abottom + aright));
	}
	if ((x == 0) && (y == size - 1)) {
		//cout << "3" << endl;
		int aleft = tab[0][size - 2] * 2 - 1;
		int aup = tab[size-1][size - 1] * 2 - 1;
		int aright = tab[0][0] * 2 - 1;
		int abottom = tab[1][size-1] * 2 - 1;
		return(2 * centre * (aup + aleft + abottom + aright));
	}
	if ((x == size - 1) && (y == size - 1)) {
		//cout << "4" << endl;
		int aleft = tab[size - 1][size - 2] * 2 - 1;
		int aup = tab[size -2][size - 1] * 2 - 1;
		int aright = tab[size-1][0] * 2 - 1;
		int abottom = tab[0][size-1] * 2 - 1;
		return(2 * centre * (aup + aleft + abottom + aright));
	}
	if (x == 0) {
		//cout << "5" << endl;
		int aleft = tab[x][y-1] * 2 - 1;
		int aup = tab[size-1][y] * 2 - 1;
		int aright = tab[x][y+1] * 2 - 1;
		int abottom = tab[1][y] * 2 - 1;
		return(2 * centre * (aup + aleft + abottom + aright));
	}
	if (x == size - 1) {
		//cout << "6" << endl;
		int aleft = tab[x][y - 1] * 2 - 1;
		int aup = tab[size-2][y] * 2 - 1;
		int aright = tab[x][y + 1] * 2 - 1;
		int abottom = tab[0][y] * 2 - 1;
		return(2 * centre * (aup + aleft + abottom + aright));
	}
	if (y == 0) {
		//cout << "7" << endl;
		int aleft = tab[x][size-1] * 2 - 1;
		int aup = tab[x-1][y] * 2 - 1;
		int aright = tab[x][y+1] * 2 - 1;
		int abottom = tab[x+1][y] * 2 - 1;
		return(2 * centre * (aup + aleft + abottom + aright));
	}
	if (y == size - 1) {
		//cout << "8" << endl;
		int aleft = tab[x][size - 2] * 2 - 1;
		int aup = tab[x - 1][y] * 2 - 1;
		int aright = tab[x][0] * 2 - 1;
		int abottom = tab[x + 1][y] * 2 - 1;
		return(2 * centre * (aup + aleft + abottom + aright));
	}
	if ((x >= 1 && x <= size - 2) && (y >= 1 && y <= size - 2)) {
		//cout << "9" << endl;
		int aleft = tab[x][y-1] * 2 - 1;
		int aup = tab[x-1][y] * 2 - 1;
		int aright = tab[x][y+1] * 2 - 1;
		int abottom = tab[x+1][y] * 2 - 1;
		return(2 * centre * (aup + aleft + abottom + aright));
	}
	return(314);
}
int proba(float T, int DE) {
	double x = uniform_continue(1.0);

	if (x < exp(-DE / T)) {
		return(1);
	}
	else {
		return(0); 
	}

}
int test(int T, int DE){
	if (DE < 0.1) {
		return(1);
	}
	if (DE > 0.1) {
		return(proba(T,DE));
	}
	else {
		cout << "error test" << endl;
		return(100);
	}
}
float M(vector <vector <int>> tab,int size) {
	double somme = 0;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++)
			somme += tab[i][j];
	}
	cout << somme << endl;
	return(abs(-1*(size * size - somme) + somme) / (size * size));
}
vector <vector <int>> new_point(vector <vector <int>> tab, int size, float T) {
	int Nx = uniform_entier(size);
	int Ny = uniform_entier(size);
	//cout << Nx << "  " << Ny << endl;
	int DE = calcul_DE(tab, Nx, Ny, size);
	if (test(T, DE) == 1) {
		int val = tab[Nx][Ny];
		tab[Nx][Ny] = !val;
	}
	return(tab);
}

vector <vector <int>> creation_tableau(float ratio_goal, int size) {
	vector <vector <int>> tab = matrice(size);
	float tot = 0.0;
	float ratio = 0.0;

	while (ratio < ratio_goal) {
		int Nx = uniform_entier(size);
		int Ny = uniform_entier(size);
		if (tab[Nx][Ny] == 0) {
			tab[Nx][Ny] = 1;
			tot += 1.0;
		}
		ratio = tot / (size * size);
	}
	cout << "ratio : " << tot / (size * size) << endl;
	return(tab);

}
int main() {
	int size = 20;
	float T = 2;
	vector <vector <int>> tab = creation_tableau(0.5, size);

	print_tab(tab, size);
	//#pragma omp parallel for shared(tab)

	for (int i = 0; i < size * size * 100; i++) {
		tab = new_point(tab, size, T);
		//print_tab(tab, size);
		//system("cls");
	}
	cout << endl;
	print_tab(tab, size);
	cout << "T: " << T << endl;
	cout << "M : " << M(tab, size) << endl;
}