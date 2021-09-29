#include <iostream>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <math.h>
#include <climits>
#include <fstream>
#include <stdio.h>
#include <string>
#include "Matriz.h"
using namespace std;




int vaca1(vector <int> const& cubos, Matriz<int>& tabla, int i, int j);

int devoradora(vector <int> const& cubos, Matriz<int>& tabla, int i, int j) {
    int& res = tabla[i][j];

    if (res == -1) {
        if (cubos[i] > cubos[j]) 
            res = vaca1(cubos, tabla, i + 1, j);

        else res = vaca1(cubos, tabla, i, j - 1);
    }
    return res;
}

int vaca1(vector <int> const& cubos, Matriz<int> & tabla, int i, int j) {
    int& res = tabla[i][j];

    if (res == -1) {
        if (i == j)
            res = cubos[i];
        else if (i + 1 == j)
            res = max(cubos[i], cubos[j]);
        else 
            res = max(devoradora(cubos, tabla, i + 1, j) + cubos[i],
            devoradora(cubos, tabla, i, j - 1) + cubos[j]);
    }
    return res;
}


bool resuelveCaso() {
    int n;

    std::cin >> n;

    if (n == 0)
        return false;

    vector<int>cubos(n);

    for (int i = 0; i < n; i++) {
        std::cin >> cubos[i];
    }

    Matriz<int> tabla(n, n, -1);
    int sol = vaca1(cubos, tabla, 0, n - 1);

    std::cout << sol << std::endl;

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