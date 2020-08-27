/*
 * function.cpp
 *
 *  Created on: Jun 23, 2020
 *      Author: linux
 */

#include "function.h"
using namespace std;

long double infinity_behaviour(long double infinity, P* polynomial)
{
	int max_st = -Infinity;
	long double max_st_mul = -1.;
	for (int i = 0; i < polynomial->size; i++)
	{
		if (polynomial->st[i] > max_st)
		{
			max_st = polynomial->st[i];
			max_st_mul = polynomial->mul[i];
		}
	}
	return (sign_equal(max_st_mul, pow(infinity, max_st))) ? Infinity : -Infinity;
}

// Oblicza f(x)
long double fx(long double x, P* polynomial)
{
    long double* y = new long double[polynomial->size];
    if (abs_d(x) == Infinity)
        return p_fx(x, infinity_behaviour(x, polynomial));
    for (int i = 0; i < polynomial->size; i++)
    	y[i] = pow(x, polynomial->st[i]) * polynomial->mul[i];
    long double result = sum(y, polynomial->size);
    delete y;
    return p_fx(x, result);
};

// Oblicza pochodna wielomianu
P* fd(P* polynomial)
{
	P* wd = new P(polynomial->size);
	int new_size = 0;
	for (int i = 0; i < polynomial->size; i++)
	{
		if (polynomial->st[i] == 0) continue;
		wd->st[new_size] = polynomial->st[i] - 1;
		wd->mul[new_size] = polynomial->mul[i] * polynomial->st[i];
		new_size++;
	}
	wd->size = new_size;
	return wd;
};

// Szuka miejsca zerowego przy pomocy bisekcji
void bisection_frozen(P* polynomial, Range* range, long double eps)
{
	long double valueAtMin = fx(range->min, polynomial);
	long double valueAtMax = fx(range->max, polynomial);
	long double halfWay = (valueAtMin + valueAtMax) / 2;
	long double halfWayValue = fx(halfWay, polynomial);
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
