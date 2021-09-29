#include <iostream>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <math.h>
#include <climits>
#include <fstream>
#include <stdio.h>
#include <string.h>
using namespace std;



string subS(string const& x, string const& y) {
	vector<vector<int>> tabla(x.size() + 1, vector<int>(y.size() + 1));
	for (int i = 0; i < x.size() + 1; ++i) tabla[i][0] = 0;
	for (int j = 0; j < y.size() + 1; ++j) tabla[0][j] = 0;


	for (int i = 1; i < x.size() + 1; ++i) {
		for (int j = 1; j < y.size() + 1; ++j) {
			tabla[i][j] = tabla[i - 1][j];
			if (tabla[i][j] < tabla[i][j - 1])
				tabla[i][j] = tabla[i][j - 1];
			if (x[i - 1] == y[j - 1] && tabla[i - 1][j - 1] + 1 > tabla[i][j])
				tabla[i][j] = tabla[i - 1][j - 1] + 1;
		}
	}

	string subSec = "";
	int i = tabla.size() - 1, j = tabla[0].size() - 1;
	while (i >= 1 && j >= 1) {

		if (tabla[i][j] == tabla[i][j - 1])
			--j;
		else if (tabla[i][j] == tabla[i - 1][j])
			--i;
		else {
			subSec.insert(subSec.begin(), y[j - 1]);
			--i;

		}
	}


	return subSec;

}

bool resuelveCaso() {
	string x, y;
	cin >> x >> y;

	if (!cin) return false;

	cout << subS(x, y) << '\n';

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
