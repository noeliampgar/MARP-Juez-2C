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


struct cancion {
    double dur;
    double punt;
};

struct nodo {
    int k;
    double punt;
    double punt_opt;
    double A;
    double B;
};

bool operator<(nodo const& a, nodo const& b) {
    return a.punt_opt < b.punt_opt;
}

bool operator>(cancion const& a, cancion const& b) {
    return (a.punt / a.dur) > (b.punt / b.dur);
}

double calculo_opt(int N, double T,vector<cancion> const& canciones, nodo const& X) {
    double optimista = X.punt;
    double hueco = 2 * T - (X.A + X.B);

    int i = X.k + 1;
    while (i <= N && canciones[i].dur <= hueco) {
        hueco -= canciones[i].dur;
        optimista += canciones[i].punt;
        i++;
    }
    if (i <= N) optimista += canciones[i].punt * hueco / canciones[i].dur;

    return optimista;
}

double calculo_pes(int N, double T,vector<cancion> const& canciones, nodo const& X) {
    int pesimista = X.punt;
    double A = X.A;
    double B = X.B;

    int i = X.k + 1;
    while (i <= N && (A <= T || B <= T)) {
        if (canciones[i].dur <= T - A) {
            A += canciones[i].dur;
            pesimista += canciones[i].punt;
        }
        else if (B + canciones[i].dur <= T) {
            B += canciones[i].dur;
            pesimista += canciones[i].punt;
        }
        i++;
    }

    return pesimista;
}

double cinta(int N, double T,vector<cancion> const& canciones) {
    nodo X, Y;
    Y.k = -1;
    Y.punt = 0;
    Y.A = 0;
    Y.B = 0;
    Y.punt_opt = calculo_opt(N, T, canciones, Y);

   priority_queue<nodo> pq;
    pq.push(Y);

    double mejor_punt = calculo_pes(N, T, canciones, Y);

    while (!pq.empty() && pq.top().punt_opt >= mejor_punt) {
        Y = pq.top(); pq.pop();
        X.k = Y.k + 1;

        if (canciones[X.k].dur <= T - Y.A) {
            X.punt = Y.punt + canciones[X.k].punt;
            X.A = Y.A + canciones[X.k].dur;
            X.B = Y.B;
            X.punt_opt = Y.punt_opt;
            if (X.k == N)
                mejor_punt = X.punt;
            else {
                pq.push(X);
            }
        }
        if (canciones[X.k].dur <= T - Y.B && Y.A != Y.B) {
            X.punt = Y.punt + canciones[X.k].punt;
            X.A = Y.A;
            X.B = Y.B + canciones[X.k].dur;
            X.punt_opt = Y.punt_opt;
            if (X.k == N)
                mejor_punt = X.punt;
            else {
                pq.push(X);
                mejor_punt =max(mejor_punt, calculo_pes(N, T, canciones, X));
            }
        }
        X.A = Y.A;
        X.B = Y.B;
        X.punt = Y.punt;
        X.punt_opt = calculo_opt(N, T, canciones, X);
        if (X.punt_opt >= mejor_punt) {
            if (X.k == N)
                mejor_punt = X.punt;
            else {
                pq.push(X);
                mejor_punt =max(mejor_punt, calculo_pes(N, T, canciones, X));
            }
        }
    }

    return mejor_punt;
}

bool resuelveCaso() {
    int N;
   cin >> N;

    if (N == 0) return false;

    double T;
   cin >> T;
   vector<cancion> canciones(N + 1);
    for (int i = 1; i <= N; ++i) {
       cin >> canciones[i].dur >> canciones[i].punt;
    }

   sort(canciones.begin() + 1, canciones.end(),greater<cancion>());

   cout << cinta(N, T, canciones) << '\n';

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
