/*
 * function_i.h
 *
 *  Created on: Jul 28, 2020
 *      Author: linux
 */

#ifndef SRC_FUNCTION_I_H_
#define SRC_FUNCTION_I_H_

#include <cmath>
#include <math.h>
#include <iostream>
#include "help_i.h"
#include "arithmetic_i.h"
#include "debug_i.h"

struct WI {
	int* st;
	I* mul;
	int size;
	WI(int s) { st = new int[s]; mul = new I[s]; size = s; };
	WI(int s, int* t, I* m) { st = t; mul = m; size = s; };
};
class NotEnoughInstantiatedException {};
struct RangeI {
	I* min;
	I* max;
	RangeI(I* v) { min = new I(v->a, v->a); max = new I(v->b, v->b); };
	RangeI(I* a, I* b) { if (!strict_eq_greater_than_i(b, a)) { throw NotEnoughInstantiatedException(); } ;min = a; max = b; };
};
I* fx_i(I* x, WI* wielomian);
WI* fd_i(WI* wielomian);
void bisection_frozen_i(WI* wielomian, RangeI* range, I* eps);

#endif /* SRC_FUNCTION_I_H_ */
