/*
 * function.cpp
 *
 *  Created on: Jun 23, 2020
 *      Author: linux
 */

#include "function.h"
using namespace std;

long double infinity_behaviour(long double infinity, W* wielomian)
{
	int max_st = -Infinity;
	long double max_st_mul = -1.;
	for (int i = 0; i < wielomian->size; i++)
	{
		if (wielomian->st[i] > max_st)
		{
			max_st = wielomian->st[i];
			max_st_mul = wielomian->mul[i];
		}
	}
	return (sign_equal(max_st_mul, pow(infinity, max_st))) ? Infinity : -Infinity;
}

// Oblicza f(x)
long double fx(long double x, W* wielomian)
{
    long double* y = new long double[wielomian->size];
    if (abs_d(x) == Infinity)
        return p_fx(x, infinity_behaviour(x, wielomian));
    for (int i = 0; i < wielomian->size; i++)
    	y[i] = pow(x, wielomian->st[i]) * wielomian->mul[i];
    long double result = sum(y, wielomian->size);
    delete y;
    return p_fx(x, result);
};

// Oblicza pochodna wielomianu
W* fd(W* wielomian)
{
	W* wd = new W(wielomian->size);
	int new_size = 0;
	for (int i = 0; i < wielomian->size; i++)
	{
		if (wielomian->st[i] == 0) continue;
		wd->st[new_size] = wielomian->st[i] - 1;
		wd->mul[new_size] = wielomian->mul[i] * wielomian->st[i];
		new_size++;
	}
	wd->size = new_size;
	return wd;
};

// Szuka miejsca zerowego przy pomocy bisekcji
void bisection_frozen(W* wielomian, Range* range, long double eps)
{
	long double valueAtMin = fx(range->min, wielomian);
	long double valueAtMax = fx(range->max, wielomian);
	long double halfWay = (valueAtMin + valueAtMax) / 2;
	long double halfWayValue = fx(halfWay, wielomian);
	// Ecplise urodzil sie w kraju w krorym nie znano operatorow przecinkowych...
	if (strict_eq_greater_than(eps, abs(valueAtMin)))
		range->max = range->min;
	else if (strict_eq_greater_than(eps, abs(valueAtMax)))
		range->min = range->max;
	else if (strict_eq_greater_than(eps, halfWayValue))
		range->min = range->max = halfWay;
	else if (signbit(halfWayValue) == signbit(range->min)) // FIXME: Nie potrafie Ci pomoc
		range->min = halfWay;
	else range->max = halfWay;
}
