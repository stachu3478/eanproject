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

struct PI {
	int* st;
	I* mul;
	int size;
	PI(int s) { st = new int[s]; mul = new I[s]; size = s; };
	PI(int s, int* t, I* m) { st = t; mul = m; size = s; };
};
class NotEnoughInstantiatedException {};
struct RangeI {
	I* min;
	I* max;
	RangeI(I* ab) { min = new I(ab->a, ab->a); max = new I(ab->b, ab->b); };
	RangeI(I* a, I* b) { if (eq_greater_than_i(a, b)) { throw NotEnoughInstantiatedException(); } ;min = a; max = b; };
};
I* fx_i(I* x, PI* polynomial);
PI* fd_i(PI* polynomial);
void bisection_frozen_i(PI* polynomial, RangeI* range, I* eps);

#endif /* SRC_FUNCTION_I_H_ */
