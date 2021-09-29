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
	int N;
	cin >> N;
	if (N == 0)
		return false;
	char aux;
	int horas, mins, dur, ini;
	vector <pair<int, int>> pelis;

	for (int i = 0; i < N; ++i) {
		cin >> horas >> aux >> mins >> dur;
		ini = horas * 60 + mins;
		pelis.push_back({ ini, dur });
	}
	for (std::vector <pair<int, int>>::const_iterator i = pelis.begin(); i != pelis.end(); ++i)
		std::cout << (*i).first<<' '<< (*i).second << ' ';
	cout << endl << endl;
	cout << endl << endl;

	sort(pelis.begin(), pelis.end());

	for (std::vector <pair<int, int>>::const_iterator i = pelis.begin(); i != pelis.end(); ++i)
		std::cout << (*i).first << ' ' << (*i).second << ' ';
	cout << endl << endl;
	cout << endl << endl;
	cout << endl << endl;
	cout << endl << endl;
	cout << endl << endl;

	sort(pelis.begin(), pelis.end());


	// 1441 = 24*60 +1 (horas del dia)
	vector <int> vPelis(1451,0);


	for (int i = 1; i < N + 1; ++i)
		for (int j = 1450; j > 0; --j) {
			if (j >= pelis[i - 1].first + pelis[i - 1].second + 10)
				vPelis[j] = max(vPelis[j], vPelis[pelis[i - 1].first] + pelis[i - 1].second);
		}
	cout << vPelis[1450] << '\n';
	/**/
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

