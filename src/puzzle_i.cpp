/*
 * puzzle_i.cpp
 *
 *  Created on: Jul 25, 2020
 *      Author: linux
 */
#include "Interval.h"
#include "puzzle_i.h"

using namespace std;

const int MAX_LOOPS = 100;

WI* read_puzzle_i()
{
	int size = 0;
	cout << "Podaj liczbę niezerowych składników wielomianu" << endl;
	cin >> size;
	cout << endl;
	WI* wielomian = new WI(size);
	for (int i = 0; i < wielomian->size; i++)
	{
		string mul;
		cout << "Podaj mnożnik kolejnego składnika" << endl;
		cin >> mul;
		wielomian->mul[i] = wielomian->mul[i].IntRead(mul);
		cout << " " << wielomian->mul[i].a << " <-> " << wielomian->mul[i].b << endl;
		cout << "Podaj stopień tego składnika" << endl;
		cin >> wielomian->st[i];
		cout << endl;
	};
	return wielomian;
}

void solve_i()
{
	try
	{
		I eps0 = I().IntRead("0.0001");
		I epsX = I().IntRead("0.0001");
		I* eps0Pointer = &eps0;
		I* epsXPointer = &epsX;
		ArrayOfI* result = rec_newton_i(read_puzzle_i(), eps0Pointer, epsXPointer, MAX_LOOPS);
		if (result->size == 0)
		{
			cout << "Brak rozwiazan" << endl;
			return;
		}
		p_is_i("A oto miejsca zerowe: ", result->a, result->size);
		return;
	} catch (AllArgumentsSatisfiedExceptionI* e)
	{
		cout << "Rozwiazanie jest przed Toba" << endl;
	}
}

