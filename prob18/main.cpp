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
#include "Matriz.h"


using namespace std;



struct nodo {
    int k;
    int tiempo;
    int tiempo_opt;
    vector<bool> asignado;
};

bool operator<(nodo  a, nodo  b) {
    return a.tiempo_opt > b.tiempo_opt;
}

void calculo_estimaciones(int N, Matriz<int>  T, vector<int>& opt, vector<int>& pes) {
    vector<int> rapido(N + 1), lento(N + 1);
    for (int i = 1; i <= N; ++i) {
        rapido[i] = T[i][1];
        lento[i] = T[i][1];
        for (int j = 2; j <= N; ++j) {
            rapido[i] = min(rapido[i], T[i][j]);
            lento[i] = max(lento[i], T[i][j]);
        }
    }

    opt[N] = 0;
    pes[N] = 0;
    for (int i = N - 1; i >= 0; --i) {
        opt[i] = opt[i + 1] + rapido[i + 1];
        pes[i] = pes[i + 1] + lento[i + 1];
    }
}

int funcionarios(int N, Matriz<int>  T) {
    vector<int> opt(N + 1), pes(N + 1);
    calculo_estimaciones(N, T, opt, pes);

    nodo X, Y;
    Y.k = 0;
    Y.tiempo = 0;
    Y.tiempo_opt = opt[0];
    Y.asignado = vector<bool>(N + 1, false);

    priority_queue<nodo> pq;
    pq.push(Y);

    int tiempo_mejor = pes[0];

    while (!pq.empty() && pq.top().tiempo_opt <= tiempo_mejor) {
        Y = pq.top(); pq.pop();
        X.k = Y.k + 1;
        X.asignado = Y.asignado;

        for (int i = 1; i <= N; ++i) {
            if (!X.asignado[i]) {
                X.asignado[i] = true;
                X.tiempo = Y.tiempo + T[X.k][i];
                X.tiempo_opt = X.tiempo + opt[X.k];
                if (X.tiempo_opt <= tiempo_mejor) {
                    if (X.k == N) tiempo_mejor = X.tiempo;
                    else {
                        pq.push(X);
                        tiempo_mejor = min(tiempo_mejor, X.tiempo + pes[X.k]);
                    }
                }
                X.asignado[i] = false;
            }
        }
    }

    return tiempo_mejor;
}

bool resuelveCaso() {
    int N;
    cin >> N;

    if (N == 0) return false;

    Matriz<int> T(N + 1, N + 1);
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
            cin >> T[i][j];
        }
    }

    cout << funcionarios(N, T) << '\n';

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
