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

using matriz = vector<vector<long long int>>;

matriz Floyd(matriz C) {
	long long int n = C.size();
	matriz camino(n, vector<long long int>(n, -1));
	for (long long int k = 0; k < n; ++k) {
		for (long long int i = 0; i < n; ++i) {
			for (long long int j = 0; j < n; ++j) {
				long long int temp = C[i][k] + C[k][j];
				if (temp < C[i][j]) {
					C[i][j] = temp;
					camino[i][j] = k;
				}
			}
		}
	}
	return C;
}

bool resuelveCaso() {
	long long int numP, numR;
	cin >> numP >> numR;
	if (!cin) return false;


	matriz G(numP, vector<long long int>(numP, INT_MAX));//creo la matriz de adyacencia del grafo de relaciones


	map<string, long long int > mapPeople;               //voy a crear un diccionario que asigne a cada nombre un numero del 0 a numP-1


	string name1, name2;
	long long int pos1, pos2;
	long long int i = 0;


	for (long long int j = 0; j < numR; ++j) {          //leo las numR relaciones y a la vez relleno el diccionario
		cin >> name1 >> name2;

		auto itr1 = mapPeople.find(name1);              //iterador del nombre1 en el diccionario
		if (itr1 == mapPeople.end()) {
			mapPeople.insert({ name1 ,i });
			pos1 = i;                                   //si lo encuentra la posicion1 de la relacion sería esa i
			++i;
		}
		else  
			pos1 = itr1->second;                        //si no lo encunetra sería una i que ya teníamos asignada al nombre1

		                                                //análogo para nombre2

		auto itr2 = mapPeople.find(name2);              //iterador del nombre2 en el diccionario
		if (itr2 == mapPeople.end()) {
			mapPeople.insert({ name2 ,i });
			pos2 = i;
			++i;
		}
		else  
			pos2 = itr2->second; 


		G[pos1][pos2] = 1;                              //incluyo la relacion en la matriz de adyacencia
		G[pos2][pos1] = 1;
	}


	for (long long int i = 0; i < G.size(); ++i)
		G[i][i] = 0;


	matriz sol = Floyd(G);                              //ejecuto floyd y el camino más largo entre dos personas sería la longitud de esa red
	long long int maxi = sol[0][0];
	for (long long int k = 0; k < numP; ++k) {
		for (long long int l = 1; l < numP; ++l) {
			maxi = max(maxi, sol[k][l]);
		}
	}


	if (maxi >= INT_MAX)
		cout << "DESCONECTADA";
	else cout << maxi;


	cout << endl;


	return true;
}

int main() {
#ifndef DOMJUDGE
	ifstream in("entrada.txt");
	auto cinbuf = cin.rdbuf(in.rdbuf());
#endif
	while (resuelveCaso());
#ifndef DOMJUDGE
	cin.rdbuf(cinbuf);
#endif
	return 0;
}
