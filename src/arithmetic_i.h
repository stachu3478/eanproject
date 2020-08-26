/*
 * arithmetic_i.h
 *
 *  Created on: Jul 25, 2020
 *      Author: linux
 */

#ifndef SRC_ARITHMETIC_I_H_
#define SRC_ARITHMETIC_I_H_

#include "Interval.h"

bool strict_eq_i(I* v, I* target);
bool eq_i(I* v, I* target);
bool strict_greater_than_i(I* a, I* b);
bool greater_than_i(I* a, I* b);
bool strict_eq_greater_than_i(I* a, I* b);
bool eq_greater_than_i(I* a, I* b);
bool strict_sign_equal_i(I* a, I* b);
bool sign_equal_i(I* a, I* b);
bool strict_in_range_i(I* a, I* b, I* range);
bool in_range_i(I* a, I* b, I* range);

#endif /* SRC_ARITHMETIC_I_H_ */
