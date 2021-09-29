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


void verA(Matriz<bool>& A, Matriz<bool>& B, Matriz<bool>& C, int i, int j, int k)
{	A[i][j] = false;
	while (!A[i][j] && k < j) {
		A[i][j] = (A[i][k] && C[k + 1][j]) || (B[i][k] && C[k + 1][j]) || (C[i][k] && A[k + 1][j]);
		if (!A[i][j])
			k++;
	}
}

void verB(Matriz<bool>& A, Matriz<bool>& B, Matriz<bool>& C, int i, int j, int k)
{
	B[i][j] = false;
	while (!B[i][j] && k < j) {
		B[i][j] = (A[i][k] && A[k + 1][j]) || (A[i][k] && B[k + 1][j]) || (B[i][k] && B[k + 1][j]);
		if (!B[i][j])
			k++;
	}
}

void verC(Matriz<bool>& A, Matriz<bool>& B, Matriz<bool>& C, int i, int j, int k)
{
	C[i][j] = false;
	while (!C[i][j] && k < j)
	{
		C[i][j] = (B[i][k] && A[k + 1][j]) || (C[i][k] && B[k + 1][j]) || (C[i][k] && C[k + 1][j]);
		if (!C[i][j])
			k++;
	}
}

bool esPosible(vector<char> letras, int n)
{	Matriz<bool> A(n, n, false);
	Matriz<bool> B(n, n, false);
	Matriz<bool> C(n, n, false);
	for (int i = 0; i < n; i++)
	{
		A[i][i] = (letras[i] == 'a');
		B[i][i] = (letras[i] == 'b');
		C[i][i] = (letras[i] == 'c');
	}

	for (int d = 1; d < n; d++)
	{
		for (int i = 0; i < n - d; i++)
		{
			int j = i + d;
			int k = i;
			verA(A, B, C, i, j, k);
			verB(A, B, C, i, j, k);
			verC(A, B, C, i, j, k);
		}
	}
	return A[0][n - 1];
}

bool resuelveCaso()
{
	string secuencia;
	cin >> secuencia;
	if (!cin)
		return false;
	vector<char> letras(secuencia.length());
	for (int i = 0; i < secuencia.length(); i++) {
		letras[i] = secuencia[i];
	}
	if (esPosible(letras, letras.size())) {
		cout << "SI\n";
	}
	else {
		cout << "NO\n";
	}
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