/*
 * arithmetic_i.cpp
 *
 *  Created on: Jul 26, 2020
 *      Author: linux
 */

#include "arithmetic_i.h"

bool strict_eq_i(I* v1, I* v2) { return v1->a == v2->a && v1->b == v2->b; };
bool eq_i(I* v1, I* v2)
{
	return (v1->a >= v2->a && v1->a <= v2->b)
		|| (v1->b >= v2->a && v1->b <= v2->b);
};
bool strict_greater_than_i(I* v1, I* v2) { return v1->a > v2->b; };
bool greater_than_i(I* v1, I* v2) { return v1->b > v2->a; };
bool strict_eq_greater_than_i(I* v1, I* v2) { return v1->a >= v2->b; };
bool eq_greater_than_i(I* v1, I* v2) { return v1->b >= v2->a; };
bool strict_sign_equal_i(I* v1, I* v2)
{
	return (v1->a >= 0) == (v1->b >= 0)
		&& (v2->a >= 0) == (v2->b >= 0)
		&& (v1->a >= 0) == (v2->a >= 0);
};
bool sign_equal_i(I* v1, I* v2)
{
	return (v1->a >= 0) != (v1->b >= 0)
		|| (v2->a >= 0) != (v2->b >= 0)
		|| (v1->a >= 0) == (v2->a >= 0);
};
bool strict_in_range_i(I* v1, I* v2, I* range)
{
	return (v1->b - v2->a <= range->a) && (v2->b - v1->a <= range->a);
}
bool in_range_i(I* v1, I* v2, I* range)
{
	return (v1->a + range->b >= v2->a && v1->a <= v2->b + range->b)
		|| (v1->b + range->b >= v2->a && v1->b <= v2->b + range->b);
}
