/*
 * puzzle.cpp
 *
 *  Created on: Jul 25, 2020
 *      Author: linux
 */
#include "puzzle.h"

using namespace std;

const long double EXPSILON0 = 0.0001, EPSILONX = 0.0001;
const int MAX_LOOPS = 100;

P* read_puzzle()
{
	int size = 0;
	cout << "Podaj liczbę niezerowych składników wielomianu" << endl;
	cin >> size;
	cout << endl;
	P* polynomial = new P(size);
	for (int i = 0; i < polynomial->size; i++)
	{
		cout << "Podaj mnożnik kolejnego składnika" << endl;
		cin >> polynomial->mul[i];
		cout << endl;
		cout << "Podaj stopień tego składnika" << endl;
		cin >> polynomial->st[i];
		cout << endl;
	};
	return polynomial;
}

void solve()
{
	try
	{
		ArrayOfDouble* result = rec_newton(read_puzzle(), EXPSILON0, EPSILONX, MAX_LOOPS);
		if (result->size == 0)
		{
			cout << "Brak rozwiazan" << endl;
			return;
		}
		cout << "A oto miejsca zerowe: " << endl;
		for (int i = 0; i < result->size; i++)
			cout << result->a[i] << endl;
		return;
	} catch (AllArgumentsSatisfiedException* e)
	{
		cout << "Rozwiazanie jest przed Toba" << endl;
	}
}
