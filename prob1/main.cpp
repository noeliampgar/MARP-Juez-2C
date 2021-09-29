//Noelia Pérez García-Consuegra
#include <iostream>
#include <string>
#include <math.h>
#include <algorithm>
#include <fstream>  
#include <limits.h>
#include <limits>
#include <vector>
#include <fstream>
#include <climits>

using namespace std;


struct tCuerda {
	long long int longitud, coste;
};

bool posible(vector<tCuerda> const& C, long long int maxL) {
	vector<bool> cuerdas(maxL + 1, false);
	cuerdas[0] = true; // caso base
	for (long long int i = 0; i < C.size(); ++i) {
		for (long long int j = maxL; j >= C[i].longitud; j--) {
			cuerdas[j] = cuerdas[j] || cuerdas[j - C[i].longitud];
		}
	}
	return cuerdas[maxL];
}

long long int numPos(vector<tCuerda> const& C, long long int maxL) {
	vector<long long int> cuerdas(maxL + 1, 0);
	cuerdas[0] = 1; // caso base
	for (long long int i = 0; i < C.size(); ++i) {
		for (long long int j = maxL; j >= C[i].longitud; --j) {
			cuerdas[j] = cuerdas[j] + cuerdas[j - C[i].longitud];
		}
	}
	return cuerdas[maxL];
}

long long int minCuerdas(vector<tCuerda> const& C, long long int maxL, long long int numMax) {
	vector<long long int> cuerdas(maxL + 1, numMax);
	cuerdas[0] = 0;
	for (long long int i = 1; i <= C.size(); ++i) {
		for (long long int j = maxL; j >= C[i - 1].longitud; j--) {
			cuerdas[j] = min(cuerdas[j], cuerdas[j - C[i - 1].longitud] + 1);
		}
	}
	return cuerdas[maxL];
}

long long int minCte(vector<tCuerda> const& C, long long int maxL, long long int cteMax) {
	vector<long long int> cuerdas(maxL + 1, cteMax);

	cuerdas[0] = 0;
	for (long long int i = 1; i <= C.size(); ++i) {
		for (long long int j = maxL; j >= C[i - 1].longitud; j--) {
			cuerdas[j] = min(cuerdas[j], cuerdas[j - C[i - 1].longitud] + C[i - 1].coste);
		}
	}
	return cuerdas[maxL];
}

bool resuelveCaso() {
	long long int numC, maxL;
	cin >> numC >> maxL;
	long long int numMax = numC, longMax = 0, cteMax = 0;
	if (!cin) return false;

	vector<tCuerda> C(numC);
	for (long long int i = 0; i < numC; ++i) {
		cin >> C[i].longitud >> C[i].coste;
		cteMax += C[i].coste;

	}



	bool pos = posible(C, maxL);
	if (pos) {
		cout << "SI " << numPos(C, maxL) << " " << minCuerdas(C, maxL, numMax) << " " << minCte(C, maxL, cteMax) << '\n';
	}
	else cout << "NO\n";

	return true;
}



int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	ifstream in("entrada.txt");
	auto cinbuf = cin.rdbuf(in.rdbuf());
#endif/**/

	while (resuelveCaso());
	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	cin.rdbuf(cinbuf);
	system("PAUSE");
#endif/**/
	return 0;
}