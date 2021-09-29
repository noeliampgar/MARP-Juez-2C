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


int cuadracity(int N,int M){
vector<vector<int>> vCuadracity(N, vector<int>(M, 0));

char aux;

vCuadracity[0][0] = 1;
cin >> aux;
for (int j = 1; j < M; ++j) {
	cin >> aux;
	if (aux == 'P')
		vCuadracity[0][j] = 0;
	else
		vCuadracity[0][j] = vCuadracity[0][j - 1];
}

for (int i = 1; i < N; ++i) {
	cin >> aux;
	if (aux == 'P')
		vCuadracity[i][0] = 0;
	else
		vCuadracity[i][0] = vCuadracity[i - 1][0];

	for (int j = 1; j < M; ++j) {
		cin >> aux;
		if (aux == '.') {
			vCuadracity[i][j] = vCuadracity[i - 1][j] + vCuadracity[i][j - 1];
		}
		else if (aux == 'P')
			vCuadracity[i][j] = 0;
	}
}
return vCuadracity[N - 1][M - 1];
}

bool resuelveCaso() {
	int N, M;
	cin >> N >> M;
	if (!cin)
		return false;



	cout << cuadracity(N, M)<< '\n';

	return true;

}












int main() {
#ifndef DOMJUDGE
	ifstream in("entrada.txt");
	auto cinbuf = cin.rdbuf(in.rdbuf());
#endif


	while (resuelveCaso())
		;


#ifndef DOMJUDGE
	cin.rdbuf(cinbuf);
#endif
	return 0;
}
