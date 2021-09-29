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
struct tSol {
	int numSols;
	int numDardos;
	vector<int> resultado;
};

tSol resolver(int C, int n, vector<int> M) {
	vector<vector<tSol>> tabla(n + 1, vector<tSol>(C + 1));

	for (int i = 1; i <= C; i++) {
		tabla[0][i].numDardos = INT_MAX;
	}

	for (int i = 0; i <= n; i++) {
		tabla[i][0].numSols = 1;
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= C; j++) {

			if (M[i - 1] > j)
				tabla[i][j] = tabla[i - 1][j];
			else {
				int aux1 = tabla[i - 1][j].numSols;
				int aux2 = tabla[i][j - M[i - 1]].numSols;
				tabla[i][j].numSols = aux1 + aux2;

				if (aux1 != 0 && aux2 != 0) {
					int minimo = min(tabla[i - 1][j].numDardos, tabla[i][j - M[i - 1]].numDardos + 1);
					tabla[i][j].numDardos = minimo;
					if (minimo == tabla[i][j - M[i - 1]].numDardos + 1) {
						tabla[i][j].resultado = tabla[i][j - M[i - 1]].resultado;
						tabla[i][j].resultado.insert(tabla[i][j].resultado.begin(), M[i - 1]);
					}
					else tabla[i][j].resultado = tabla[i - 1][j].resultado;
				}
				else if (aux2 != 0) {
					tabla[i][j].numDardos = tabla[i][j - M[i - 1]].numDardos + 1;
					tabla[i][j].resultado = tabla[i][j - M[i - 1]].resultado;
					tabla[i][j].resultado.insert(tabla[i][j].resultado.begin(), M[i - 1]);
				}
				else if (aux1 != 0) {
					tabla[i][j].numDardos = tabla[i - 1][j].numDardos;
					tabla[i][j].resultado = tabla[i - 1][j].resultado;
				}
			}
		}
	}
	return tabla[n][C];
}

bool resuelveCaso() {
	int C; 
	int n; 

	cin >> C >> n;

	if (!cin) return false;
	vector <int> vSec(n);

	for (int i = 0; i < n; i++) cin >> vSec[i];

	tSol sol = resolver(C, n, vSec);
	if (sol.numSols) {
		cout << sol.numDardos << ": ";
		for (int i : sol.resultado) cout << i << " ";
		cout << endl;
	}
	else cout << "Imposible\n";

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