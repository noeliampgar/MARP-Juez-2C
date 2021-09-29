#include <iostream>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <math.h>
#include <climits>
#include <fstream>
#include <queue>
#include <stdio.h>
#include <string.h>
#include <list>
#include "Matriz.h"

using namespace std;

struct tMoneda {
	int valor, cantidad;
};


bool resuelveCaso() {
	int N;
	cin >> N;
	if (!std::cin)
		return false;
	vector<tMoneda> moneda(N);
	for (int i = 0; i < N; ++i) {
		cin >> moneda[i].valor;
	}
	for (int i = 0; i < N; ++i) {
		cin >> moneda[i].cantidad;
	}
	reverse(moneda.begin(), moneda.end());
	int C;
	cin >> C;
	Matriz<int> M(N + 1, C + 1);

	for (int i = 0; i < N + 1; ++i)
		M[i][0] = 0;

	for (int j = 1; j < C + 1; ++j)
		M[0][j] = INT_MAX;

	for (int i = 1; i < N + 1; ++i)
		for (int j = 1; j < C + 1; ++j) {
			int mini = INT_MAX;
			for (int k = 0; k <= moneda[i - 1].cantidad && k * moneda[i - 1].valor <= j; ++k) {
				if (M[i - 1][j - k * moneda[i - 1].valor] != INT_MAX) {
					mini = min(M[i - 1][j - k * moneda[i - 1].valor] + k, mini);
				}
			}
			M[i][j] = mini;
		}

	if (M[N][C] == INT_MAX) cout << "NO";
	else {
		vector<int> sol;
		int j = C;
		for (int i = N; i > 0; --i) {
			int mini = INT_MAX;
			int m = j;
			int p = 0;

			for (int k = 0; k <= moneda[i - 1].cantidad && k * moneda[i - 1].valor <= j; ++k) {
				if (M[i - 1][j - k * moneda[i - 1].valor] != INT_MAX) {
					if (M[i - 1][j - k * moneda[i - 1].valor] + k <= mini) {
						m = j - k * moneda[i - 1].valor;
						p = k;
					}
					mini = min(M[i - 1][j - k * moneda[i - 1].valor] + k, mini);
				}
			}
			sol.push_back(p);
			j = m;
		}
		cout << "SI ";
		int suma=0;
		for (int i = 0; i < sol.size(); ++i) {
			suma+=sol[i];
		}
		cout << suma;
	}
	cout << '\n';

	return true;
}






int main() {
#ifndef DOMJUDGE
	ifstream in("entrada.txt");
	auto cinbuf = cin.rdbuf(in.rdbuf());
#endif


	while(resuelveCaso())
		;


#ifndef DOMJUDGE
	cin.rdbuf(cinbuf);
#endif
	return 0;
}
