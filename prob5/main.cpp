#include <iostream>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <math.h>
#include <climits>
#include <fstream>
using namespace std;
using matriz = vector<vector<long long int>>;



pair<long long int, long long int> cofres(vector<long long int> profs, vector<long long int> valores, long long int numS, vector<bool>& cuales) {
	long long int n = profs.size();


	matriz cofres(n, vector<long long int>(numS / 3 + 1, 0));

	for (long long int i = 1; i < n; ++i) {
		for (long long int j = 1; j <= numS / 3; ++j) {
			if (profs[i] > j)
				cofres[i][j] = cofres[i - 1][j];
			else
				cofres[i][j] = max(cofres[i - 1][j], cofres[i - 1][j - profs[i]] + valores[i]);
		}
	}
	long long int cont = 0;
	long long int valor = cofres[n - 1][numS / 3];
	long long int resto = numS / 3;
	for (long long int i = n - 1; i >= 1; --i) {
		if (cofres[i][resto] == cofres[i - 1][resto])
			cuales[i] = 0;
		else
		{
			cuales[i] = 1;
			cont++;
			resto = resto - profs[i];
		}
	}
	return { valor,cont };

}


bool resuelveCaso() {
	long long int numS;
	cin >> numS;
	if (!std::cin)
		return false;
	long long int numC;
	cin >> numC;
	vector<long long int> profs(numC + 1);
	vector<long long int> valores(numC + 1);
	for (long long int i = 1; i <= numC; ++i) {

		cin >> profs[i] >> valores[i];


	}
	vector<bool> cuales(numC + 1, 0);

	pair <long long int, long long int> sol = cofres(profs, valores, numS, cuales);
	cout << sol.first << endl << sol.second << endl;
	for (long long int i = 1; i <= numC; ++i) {
		if (cuales[i])
			cout << profs[i] << ' ' << valores[i] << endl;

	}
	cout << "---" << endl;

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
