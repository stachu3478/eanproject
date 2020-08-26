/*
 * function_i.cpp
 *
 *  Created on: Jul 29, 2020
 *      Author: linux
 */

#include "function_i.h"
using namespace std;

I* infinity_behaviour(I* infinity, WI* wielomian)
{
	int max_lvl = -1;
	I* max_lvl_mul;
	for (int i = 0; i < wielomian->size; i++)
	{
		if (wielomian->st[i] > max_lvl)
		{
			max_lvl = wielomian->st[i];
			max_lvl_mul = wielomian->mul + i;
		}
	}
	I infinity_given_to_power_of_maximum_polynomial_lvl = *infinity ^ max_lvl;
	return (sign_equal_i(new I((long double)max_lvl, (long double)max_lvl), &infinity_given_to_power_of_maximum_polynomial_lvl)) ? IInfinity() : MIInfinity();
}

// Oblicza f(x)
I* fx_i(I* x, WI* wielomian)
{
    I** y = new I*[wielomian->size];
    I x_abs = x->Absolute();
    if (strict_eq_i(&x_abs, IInfinity()))
        return infinity_behaviour(x, wielomian);
    if (eq_i(&x_abs, IInfinity()))
        throw NotEnoughInstantiatedException();
    for (int i = 0; i < wielomian->size; i++)
    {
    	I result = (*x ^ wielomian->st[i]) * wielomian->mul[i];
    	y[i] = new I(result.a, result.b);
    }
    I* result = sum_i(y, wielomian->size);
    delete y;
    return p_fx_i(x, result);
};

// Oblicza pochodna wielomianu
WI* fd_i(WI* wielomian)
{
	WI* wd = new WI(wielomian->size);
	int new_size = 0;
	for (int i = 0; i < wielomian->size; i++)
	{
		if (wielomian->st[i] == 0) continue;
		wd->st[new_size] = wielomian->st[i] - 1;
		wd->mul[new_size] = wielomian->mul[i].Scale(wielomian->st[i]);
		new_size++;
	}
	wd->size = new_size;
	return wd;
};

// Szuka miejsca zerowego przy pomocy bisekcji
void bisection_frozen_i(WI* wielomian, RangeI* range, I* eps)
{
	I* valueAtMin = fx_i(range->min, wielomian);
	I* valueAtMax = fx_i(range->max, wielomian);
	I halfWay = (*valueAtMin + *valueAtMax) / I(2., 2.);
	I* halfWayValue = fx_i(&halfWay, wielomian);
	I abs_min = valueAtMin->Absolute();
	I abs_max = valueAtMax->Absolute();
	if (strict_eq_greater_than_i(eps, &abs_min))
		range->max = range->min;
	else if (strict_eq_greater_than_i(eps, &abs_max))
		range->min = range->max;
	else if (strict_eq_greater_than_i(eps, halfWayValue))
		range->min = range->max = &halfWay;
	else if (strict_sign_equal_i(halfWayValue, range->min))
		range->min = &halfWay;
	else if (strict_sign_equal_i(halfWayValue, range->min))
		range->max = &halfWay;
	else throw NotEnoughInstantiatedException();
}


