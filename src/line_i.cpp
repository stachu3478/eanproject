/*
 * line_i.cpp
 *
 *  Created on: Aug 1, 2020
 *      Author: linux
 */
#include "line_i.h"

bool is_line_i(WI* wielomian)
{
	bool result = true;
	for (int i = 0; i < wielomian->size; i++)
		if (wielomian->st[i] > 1)
		{
			result = false;
			break;
		}
	return p_is_line_i(result);
}

I** line_ab_i(WI* wielomian)
{
	I** ab = new I*[2];
	ab[0] = new I(0., 0.);
	ab[1] = new I(0., 0.);
	for (int i = 0; i < wielomian->size; i++)
		if (wielomian->st[i] < 2) ab[1 - wielomian->st[i]] = &wielomian->mul[i];
	return p_line_ab_i(ab);
}

bool is_0_i(I** ab)
{
	return p_is_0_i(eq_i(ab[0], new I(0, 0)) && eq_i(ab[1], new I(0, 0)));
}

bool is_horizontal_i(I** ab)
{
	return p_is_horizontal_i(eq_i(ab[0], new I(0., 0.)));
}

bool is_vertical_i(I** ab)
{
	I x_mul_abs = ab[0]->Absolute();
	return p_is_vertical_i(eq_i(&x_mul_abs, IInfinity()));
}

I* line_zero_i(I** ab)
{
	I zero_x = ab[1]->Opposite() / *ab[0];
	return p_line_zero_i(&zero_x);
}
