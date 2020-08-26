/*
 * help_i.h
 *
 *  Created on: Jul 28, 2020
 *      Author: linux
 */

#ifndef SRC_HELP_I_H_
#define SRC_HELP_I_H_

#include <limits>
#include "debug_i.h"
#include "arithmetic_i.h"

struct ArrayOfI {
	I** a;
	int size;
	ArrayOfI() { size = 0; a = NULL; };
	ArrayOfI(int s) { size = s; a = new I*[s]; };
};
I* IInfinity();
I* MIInfinity();
void group_frozen_i(ArrayOfI* arr, I* eps);
void cp_i(I* a, I* b, int n);
void sort_frozen_i(I** list, int length);
void sort_frozen_by_i(I** list, int length, I* func(double a));
class PairsI { public: virtual void call(I* a, I* b, int i) = 0; };
void pairs_i(ArrayOfI* list, PairsI* _);
I* sum_i(I** arr, int length);

#endif /* SRC_HELP_I_H_ */
