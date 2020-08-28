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

I interval_short_read()
{
	string mul;
	cout << "Podaj wspolczynnik kolejnego składnika" << endl;
	cin >> mul;
	return I().IntRead(mul);
}

I interval_wide_read()
{
	I interval;
	string mul_left;
	cout << "Podaj dolny kraniec przedzialu wspolczynnika kolejnego składnika" << endl;
	cin >> mul_left;
	interval.a = interval.LeftRead(mul_left);
	string mul_right;
	cout << "Podaj gorny kraniec przedzialu wspolczynnika kolejnego składnika" << endl;
	cin >> mul_right;
	interval.b = interval.RightRead(mul_right);
	return interval;
}

PI* read_puzzle_i(bool read_wide)
{
	int size = 0;
	cout << "Podaj liczbę niezerowych składników wielomianu" << endl;
	cin >> size;
	cout << endl;
	PI* polynomial = new PI(size);
	for (int i = 0; i < polynomial->size; i++)
	{
		if (read_wide)
			polynomial->mul[i] = interval_wide_read();
		else
			polynomial->mul[i] = interval_short_read();
		cout << " " << polynomial->mul[i].a << " <-> " << polynomial->mul[i].b << endl;
		cout << "Podaj stopień tego składnika" << endl;
		cin >> polynomial->st[i];
		cout << endl;
	};
	return polynomial;
}

void solve_i()
{
	bool read_wide;
	cout << "Wcisnij 0, aby definiowac waskie przedzialy lub 1, aby definiowac szerokie przedzialy" << endl;
	cin >> read_wide;

	try
	{
		I eps0 = I().IntRead("0.0001");
		I epsX = I().IntRead("0.0001");
		I* eps0Pointer = &eps0;
		I* epsXPointer = &epsX;
		ArrayOfI* result = rec_newton_i(read_puzzle_i(read_wide), eps0Pointer, epsXPointer, MAX_LOOPS);
		if (result->size == 0)
		{
			cout << "Brak rozwiazan" << endl;
			return;
		}
		p_is_i("A oto miejsca zerowe: ", result->a, result->size, true);
		return;
	} catch (AllArgumentsSatisfiedExceptionI* e)
	{
		cout << "Rozwiazanie jest przed Toba" << endl;
	}
}

