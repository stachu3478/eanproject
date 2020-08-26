/*
 * help.h
 *
 *  Created on: Jun 24, 2020
 *      Author: linux
 */

#ifndef SRC_HELP_H_
#define SRC_HELP_H_

#include <limits>
#include "debug.h"
#include "arithmetic.h"

struct ArrayOfDouble {
	long double* a;
	int size;
	ArrayOfDouble() { size = 0; a = NULL; };
	ArrayOfDouble(int s) { size = s; a = new long double[s]; };
};
const long double Infinity = std::numeric_limits<long double>::infinity();
long double abs_d(long double a);
void group_frozen(ArrayOfDouble* arr, long double eps);
void cp(long double* a, long double* b, int n);
void sort_frozen(long double* list, int length);
void sort_frozen_by(long double* list, int length, long double func(long double a));
class Pairs { public: virtual void call(long double a, long double b, int i) = 0; };
void pairs(ArrayOfDouble* list, Pairs* _);
long double sum(long double* arr, int length);

#endif /* SRC_HELP_H_ */
