#ifndef SRC_FUNCTION_H_
#define SRC_FUNCTION_H_

#include <cmath>
#include <math.h>
#include <iostream>
#include "help.h"
#include "arithmetic.h"
#include "debug.h"

struct W {
	int* st;
	long double* mul;
	int size;
	W(int s) { st = new int[s]; mul = new long double[s]; size = s; };
	W(int s, int* t, long double* m) { st = t; mul = m; size = s; };
};
struct Range {
	long double min;
	long double max;
	Range(long double ab) { min = max = ab; };
	Range(long double a, long double b) { min = a; max = b; };
};
long double fx(long double x, W* wielomian);
W* fd(W* wielomian);
void bisection_frozen(W* wielomian, Range* range, long double eps);

#endif
