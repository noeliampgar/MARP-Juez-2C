#include <iostream>
#include <algorithm>
#include <vector>
#include <iomanip>

#include <fstream>
using namespace std;
using matriz = vector<vector<int>>;

bool resuelveCaso() {
	int N;
	cin >> N;
	if (!std::cin)
		return false;
	int tam = N + 1;
	matriz  mat(tam, vector<int>(tam));




	for (int i = 1; i < tam; ++i)
		for (int j = 1; j < tam; ++j) {
			cin >> mat[i][j];
		}

	for (int j = 0; j < tam; ++j) {
		mat[0][j] = 0;
		mat[j][0] = 0;
	}

	int best,prev;
	vector <int> bestSol = mat[1];
	for (int i = 2; i < tam; ++i) {
		prev = 0;
		for (int j = 1; j < tam; ++j) {
			if (j < N) best = max(prev, max(bestSol[j], bestSol[j + 1]));
			else best = max(prev, bestSol[j]);
			prev = bestSol[j];
			bestSol[j] = best + mat[i][j];
		}
	}

	int maximo = bestSol[1];
	int pM = 1;
	for (int j = 2; j < tam; ++j) {
		if (bestSol[j] > maximo) {
			maximo = bestSol[j];
			pM = j;
		}
	}
	cout << bestSol[pM] << " " << pM << endl;
	return true;
}


int main() {
#ifndef DOMJUDGE
	std::ifstream in("entrada.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	while (resuelveCaso());

#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
#endif
	return 0;
}
