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

int palindromo(int i, int j, string const& palabra, Matriz<int>& tabla) {
	int &rdo = tabla[i][j];

	if (rdo == -1) {
		if (i >= j) rdo = 0;
		else {
			if (palabra[i] == palabra[j])
				rdo = palindromo(i + 1, j - 1, palabra, tabla);
			else
				rdo = min(palindromo(i, j - 1, palabra, tabla), palindromo(i + 1, j, palabra, tabla)) + 1;
		}
	}
	return rdo;
}


string reconstruccion(int i, int j, string const& palabra, Matriz<int> const& tabla) {
	string rdo;
	if (i == j) rdo = palabra[i];
	else if (i > j) rdo = "";
	else {
		if (palabra[i] == palabra[j]) {
			rdo.push_back(palabra[j]);
			rdo.insert(rdo.length(), reconstruccion(i + 1, j - 1, palabra, tabla));
			rdo.push_back(palabra[j]);
		}
		else if (tabla[i][j - 1] < tabla[i + 1][j]) {
			rdo.insert(0, 1, palabra[j]);
			rdo.insert(rdo.length(), reconstruccion(i, j - 1, palabra, tabla));
			rdo.insert(rdo.length(), 1, palabra[j]);
		}
		else {
			rdo.insert(0, 1, palabra[i]);
			rdo.insert(rdo.length(), reconstruccion(i + 1, j, palabra, tabla));
			rdo.insert(rdo.length(), 1, palabra[i]);
		}
	}
	return rdo;
}

bool resuelveCaso() {
	string palabra;

	cin >> palabra;
	if (!cin)
		return false;

	int n = palabra.length();
	Matriz<int> tabla(n, n, -1);

	cout << palindromo(0, n - 1, palabra, tabla) << " ";
	cout << reconstruccion(0, n - 1, palabra, tabla) << endl;
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
