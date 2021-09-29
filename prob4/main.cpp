#include <iostream>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <math.h>
#include <climits>
#include <fstream>
using namespace std;
using matriz = vector<vector<long long int>>;



long long int minIndex(vector<long long int> nums, long long int& index) {
	long long int mini = nums[index];
	long long int indice = index;
	for (long long int i = index + 1; i < nums.size(); ++i) {
		if (nums[i] < mini) {
			mini = nums[i];
			indice = i;

		}
	}
	index = indice;
	return mini;

}


pair<long long int, long long int> devPotencia(vector<long long int> pots, vector<long long int> ctes, long long int pMax, long long int pMin) {
	long long int n = pots.size();
	matriz monedas(n, vector<long long int>(pMax + 1, 0));
	for (long long int i = 1; i <= pMax; ++i)
		monedas[0][i] = INT_MAX;



	for (long long int i = 1; i < n; ++i) {
		for (long long int j = 1; j <= pMax; ++j) {
			if (pots[i] > j)
				monedas[i][j] = monedas[i - 1][j];
			else
				monedas[i][j] = min(monedas[i - 1][j], monedas[i][j - pots[i]] + ctes[i]);

		}


	}

	long long int numero = minIndex(monedas[n - 1], pMin);

	return { numero,pMin };
}









bool resuelveCaso() {
	long long int numP;
	cin >> numP;
	if (!std::cin)
		return false;
	long long int pMax, pMin;
	cin >> pMax >> pMin;
	vector<long long int> pots(numP + 1);
	vector<long long int> ctes(numP + 1);

	for (long long int i = 1; i <= numP; ++i)
		cin >> pots[i];
	for (long long int i = 1; i <= numP; ++i)
		cin >> ctes[i];


	pair<long long int, long long int> sol = devPotencia(pots, ctes, pMax, pMin);
	if (sol.first >= INT_MAX)
		cout << "IMPOSIBLE\n";
	else cout << sol.first << ' ' << sol.second << endl;

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
