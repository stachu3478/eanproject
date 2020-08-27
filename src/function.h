#ifndef SRC_FUNCTION_H_
#define SRC_FUNCTION_H_

#include <cmath>
#include <math.h>
#include <iostream>
#include "help.h"
#include "arithmetic.h"
#include "debug.h"

struct P {
	int* st;
	long double* mul;
	int size;
	P(int s) { st = new int[s]; mul = new long double[s]; size = s; };
	P(int s, int* t, long double* m) { st = t; mul = m; size = s; };
};
struct Range {
	long double min;
	long double max;
	Range(long double ab) { min = max = ab; };
	Range(long double a, long double b) { min = a; max = b; };
};
long double fx(long double x, P* polynomial);
P* fd(P* polynomial);
void bisection_frozen(P* polynomial, Range* range, long double eps);

#endif
