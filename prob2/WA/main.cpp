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
#include <iomanip>

using namespace std;
struct tCamino {
	long long int numM;
	bool marcador = false;
};
/*
vector<long long int> calcularMonedas(vector<long long int> M, vector<vector<long long int>> monedas)
{


	vector<long long int> cuantas(M.size());

	long long int i = monedas.size()-1, j = monedas[0].size()-1;

	while (j > 0) {


		if (M[i - 1] <= j && monedas[i][j] != monedas[i - 1][j]) {

			cuantas[i-1] = cuantas[i-1] + 1;
			j -= M[i - 1];
		}
		else i--;
	}
	return cuantas;
}


void devolverCambio(vector<long long int> M, long long int C)
{

	long long int n = M.size();
	vector<vector<long long int>> monedas(n + 1, vector <long long int>(C + 1));
	for (long long int i = 1; i <= C; ++i) {
		monedas[0][i] = INT_MAX;
	}
	for (long long int i = 1; i <= n; ++i) {
		for (long long int j = 1; j <= C; ++j) {
			if (M[i - 1] > j)
				monedas[i][j] = monedas[i - 1][j];
			else{
				monedas[i][j] = min(monedas[i - 1][j],
					monedas[i][j - M[i - 1]] + 1);
			}
		}
	}

	for (long long int i = 1; i <= n; ++i) {
		for (long long int j = 1; j <= C; ++j) {
			cout <<setw(4)<< monedas[i][j];
		}
		cout << endl;
	}


	long long int sol = monedas[n][C];
	if (sol != INT_MAX) {
		cout << sol << ": ";

		for (long long int i = 0; i < n; ++i)
			cout <<
			calcularMonedas(M, monedas)[i] << ' ';
		cout << endl;
	}
	else cout << "Imposible\n";

}


*/


vector<long long int> calcularMonedas(vector<long long int> M, vector<vector<tCamino>> monedas)
{


	vector<long long int> cuantas(M.size());

	long long int i = monedas.size() - 1, j = monedas[0].size() - 1;

	while (j > 0) {


		if (M[i - 1] <= j && (monedas[i][j].marcador || monedas[i][j].numM != monedas[i - 1][j].numM)) {

			cuantas[i - 1] = cuantas[i - 1] + 1;
			j -= M[i - 1];
		}
		else i--;
	}
	return cuantas;
}
/*
vector<long long int> calcularMonedas(vector<long long int> M, vector<vector<tCamino>> monedas)
{
	vector<long long int> cuantas(M.size());
	long long int i = monedas.size() - 1, j = monedas[0].size() - 1;
	while (j > 0) {
		if (M[i - 1] <= j) {
			if (monedas[i][j].marcador) {
				cuantas[i - 1] = cuantas[i - 1] + 1;
				j -= M[i - 1];
			}
			else i--;
		}
		else i--;
	}
	return cuantas;
}*/

void devolverCambio(vector<long long int> M, long long int C)
{
	long long int n = M.size();
	vector<vector<tCamino>> monedas(n + 1, vector <tCamino>(C + 1));
	for (long long int i = 1; i <= C; ++i) {
		monedas[0][i].numM = INT_MAX;
	}
	for (long long int i = 1; i <= n; ++i) {
		for (long long int j = 1; j <= C; ++j) {
			if (M[i - 1] > j)
				monedas[i][j].numM = monedas[i - 1][j].numM;
			else {
				if (monedas[i - 1][j].numM >=
					monedas[i][j - M[i - 1]].numM + 1) {
					monedas[i][j].numM = monedas[i][j - M[i - 1]].numM + 1;
					monedas[i][j].marcador = true;
				}
				else {
					monedas[i][j].numM = monedas[i - 1][j].numM;
				}
			}
		}
	}

/*	for (long long int i = 1; i <= n; ++i) {
		for (long long int j = 1; j <= C; ++j) {
			cout << setw(4) << monedas[i][j].numM;
		}
		cout << endl;
	}
	for (long long int i = 1; i <= n; ++i) {
		for (long long int j = 1; j <= C; ++j) {
			cout << setw(4) << monedas[i][j].marcador;
		}
		cout << endl;
	}
	*/

	long long int sol = monedas[n][C].numM;
	if (sol != INT_MAX) {
		cout << sol << ": ";

		for (long long int i = 0; i < n; ++i) {
			int numV = calcularMonedas(M, monedas)[i];
			if (numV) {
				for (int j = 0; j < numV; ++j)
					cout << M[i] << ' ';
			}
		}
	}
	else cout << "Imposible\n";
}

bool resuelveCaso() {
	long long int sumaBus, nSec;
	cin >> sumaBus >> nSec;
	if (!cin) return false;
	vector<long long int> vSec(nSec);
	for (long long int i = 0; i < nSec; ++i) {
		cin >> vSec[i];
	}
	devolverCambio(vSec, sumaBus);
	cout << endl;
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