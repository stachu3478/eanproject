/*
 * function_i.cpp
 *
 *  Created on: Jul 29, 2020
 *      Author: linux
 */

#include "function_i.h"
using namespace std;

I* infinity_behaviour(I* infinity, PI* polynomial)
{
	int max_lvl = -1;
	I* max_lvl_mul;
	for (int i = 0; i < polynomial->size; i++)
	{
		if (polynomial->st[i] > max_lvl)
		{
			max_lvl = polynomial->st[i];
			max_lvl_mul = polynomial->mul + i;
		}
	}
	I infinity_given_to_power_of_maximum_polynomial_lvl = *infinity ^ max_lvl;
	return (sign_equal_i(new I((long double)max_lvl, (long double)max_lvl), &infinity_given_to_power_of_maximum_polynomial_lvl)) ? IInfinity() : MIInfinity();
}

// Oblicza f(x)
I* fx_i(I* x, PI* polynomial)
{
    I** y = new I*[polynomial->size];
    I x_abs = x->Absolute();
    if (strict_eq_i(&x_abs, IInfinity()))
        return infinity_behaviour(x, polynomial);
    if (eq_i(&x_abs, IInfinity()))
        throw NotEnoughInstantiatedException();
    for (int i = 0; i < polynomial->size; i++)
    {
    	I result = (*x ^ polynomial->st[i]) * polynomial->mul[i];
    	y[i] = new I(result.a, result.b);
    }
    I* result = sum_i(y, polynomial->size);
    delete y;
    return p_fx_i(x, result);
};

// Oblicza pochodna wielomianu
PI* fd_i(PI* polynomial)
{
	PI* pd = new PI(polynomial->size);
	int new_size = 0;
	for (int i = 0; i < polynomial->size; i++)
	{
		if (polynomial->st[i] == 0) continue;
		pd->st[new_size] = polynomial->st[i] - 1;
		pd->mul[new_size] = polynomial->mul[i].Scale(polynomial->st[i]);
		new_size++;
	}
	pd->size = new_size;
	return pd;
};

// Szuka miejsca zerowego przy pomocy bisekcji
void bisection_frozen_i(PI* polynomial, RangeI* range, I* eps)
{
	I* valueAtMin = fx_i(range->min, polynomial);
	I* valueAtMax = fx_i(range->max, polynomial);
	I halfWay = (*valueAtMin + *valueAtMax) / I(2., 2.);
	I* halfWayValue = fx_i(&halfWay, polynomial);
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


