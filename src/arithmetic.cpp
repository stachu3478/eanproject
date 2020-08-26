/*
 * arithmetic.cpp
 *
 *  Created on: Jul 6, 2020
 *      Author: linux
 */
#include "arithmetic.h"

bool strict_eq(long double v, long double target) { return v == target; };
bool eq(long double v, long double target) { return strict_eq(v, target); };
bool strict_greater_than(long double a, long double b) { return a > b; };
bool greater_than(long double a, long double b) { return strict_greater_than(a, b); };
bool strict_eq_greater_than(long double a, long double b) { return strict_greater_than(a, b) || strict_eq(a, b); };
bool eq_greater_than(long double a, long double b) { return greater_than(a, b) || eq(a, b); };

bool sign_equal(long double a, long double b)
{
	return strict_greater_than(a, +0) == strict_greater_than(b, +0);
}

bool in_range(long double a, long double b, long double range)
{
	return strict_eq_greater_than(range, a - b) && strict_eq_greater_than(range, b - a);
}
