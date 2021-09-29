#include <iostream>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <math.h>
#include <climits>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include "Matriz.h"

using namespace std;

bool resuelveCaso() {
	int lMad, numCtes;
	cin >> lMad >> numCtes;
	if (lMad == 0 && numCtes == 0)
		return false;
	vector <int> vCortes;
	vCortes.push_back(0);

	int valor;
	for (int i = 0; i < numCtes; ++i) {
		cin >> valor;
		vCortes.push_back(valor);
	}
	vCortes.push_back(lMad);
	Matriz<int> M(numCtes + 2, numCtes + 2, 0); 
	for (int d = 2; d < numCtes + 2; ++d) 
		for (int i = 0; i < numCtes + 2 - d; ++i) {
			int j = d + i;
			int mejor = INT_MAX;
			for (int m = i + 1; m < j; ++m) {
				mejor = min(mejor, M[i][m] + M[m][j]);
			}
			M[i][j] = mejor + 2 * (vCortes[j] - vCortes[i]);
		}

	cout << M[0][numCtes + 1] << '\n';
	return true;
}

int main() {
#ifndef DOMJUDGE
	ifstream in("entrada.txt");
	auto cinbuf = cin.rdbuf(in.rdbuf());
#endif

	while (resuelveCaso());
	//string a = "hola";
	//a.insert(a.begin(), 'd');

	//cout << a << endl;

#ifndef DOMJUDGE
	cin.rdbuf(cinbuf);
#endif
	return 0;
}
