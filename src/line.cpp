/*
 * line.cpp
 *
 *  Created on: Jun 24, 2020
 *      Author: linux
 */

#include "line.h"

bool is_line(W* wielomian)
{
	bool result = true;
	for (int i = 0; i < wielomian->size; i++)
		if (wielomian->st[i] > 1) result = false;
	return p_is_line(result);
}

long double* line_ab(W* wielomian)
{
	long double* ab = new long double[2];
	ab[0] = 0;
	ab[1] = 0;
	for (int i = 0; i < wielomian->size; i++)
		if (wielomian->st[i] < 2) ab[1 - wielomian->st[i]] = wielomian->mul[i];
	return p_line_ab(ab);
}

bool is_0(long double* ab)
{
	return p_is_0(eq(ab[0], 0.) && eq(ab[1], 0.));
}

bool is_horizontal(long double* ab)
{
	return p_is_horizontal(eq(ab[0], 0.));
}

bool is_vertical(long double* ab)
{
	return p_is_vertical(eq(abs(ab[0]), (long double)Infinity));
}

long double line_zero(long double* ab)
{
	return p_line_zero(-ab[1] / ab[0]);
}
