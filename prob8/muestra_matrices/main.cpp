#include <iostream>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <math.h>
#include <climits>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <map>

using namespace std;

using matriz = vector<vector<int>>;

pair<matriz/*C[1..n, 1..n]*/, matriz/*camino[1..n, 1..n]*/> Floyd(matriz G /*nxn*/) {
	int n = G.size();
	matriz C = G;
	
	matriz camino(n, vector<int>(n, -1));
	for (int k = 0; k < n; ++k) {
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				int temp = C[i][k]
					+ C[k][j];
				if (temp < C[i][j]) {
					//cout << i << ' ' << k << ' ' << j << ' ' << C[i][k] << ' ' << C[k][j] << endl<<endl;
					C[i][j] = temp;
					camino[i][j] = k;
				}
			}

		}

	}
	return { C,camino };

}

bool resuelveCaso() {
	int numP, numR;
	cin >> numP >> numR;

	if (!cin) return false;

	matriz G(numP, vector<int>(numP, 10000));
	map<string, int > mapPeople;
	string name1,name2;
	int pos1, pos2;
	int i = 0;
	for (int j = 0; j < numR; ++j) {
		cin >> name1>>name2;
		auto itr1 = mapPeople.find(name1);
		if ( itr1== mapPeople.end()) {
			mapPeople.insert({ name1 ,i });
			pos1 = i;
			++i;
		}
		else { pos1 = itr1->second; }

		auto itr2 = mapPeople.find(name2);
		if (itr2 == mapPeople.end()) {
			mapPeople.insert({ name2 ,i });
			pos2 = i;

			++i;
		}
		else { pos2 = itr2->second; }


		G[pos1][pos2] = 1;
		G[pos2][pos1] = 1;


	}
	for (int i = 0; i < G.size(); ++i)
		G[i][i] = 0;




	/**/for (auto itr = mapPeople.begin(); itr != mapPeople.end(); itr++) {

		cout << itr->first << '\t' << itr->second << '\n';
	}


	for(int k=0;k<numP;++k){
		for (int l = 0; l < numP; ++l) {
			cout << setw(5) << G[k][l] << ' ';
		}
		cout << endl;
	}
	cout << endl;

	pair<matriz,matriz> sol= Floyd(G);
	for (int k = 0; k < numP; ++k) {
		for (int l = 0; l < numP; ++l) {
			cout << setw(5) << sol.first[k][l] << ' ';
		}
		cout << endl;
	}
	cout << endl;
	for (int k = 0; k < numP; ++k) {
		for (int l = 0; l < numP; ++l) {
			cout << setw(2)<<sol.second[k][l] << ' ';
		}
		cout << endl;
	}
	int maxi = sol.first[0][0];

	for (int k = 0; k < numP; ++k) {
		for (int l = 1; l < numP; ++l) {
			maxi = max(maxi, sol.first[k][l]);
		}
	}
	if (maxi >= 10000)
		cout << "DESCONECTADA";
	else cout << maxi;
	cout << endl << endl;
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
