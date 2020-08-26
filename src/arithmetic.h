/*
 * arithmetic.h
 *
 *  Created on: Jul 6, 2020
 *      Author: linux
 */

#ifndef SRC_ARITHMETIC_H_
#define SRC_ARITHMETIC_H_

bool strict_eq(long double v, long double target);
bool eq(long double v, long double target);
bool strict_greater_than(long double a, long double b);
bool greater_than(long double a, long double b);
bool strict_eq_greater_than(long double a, long double b);
bool eq_greater_than(long double a, long double b);
bool sign_equal(long double a, long double b);
bool in_range(long double a, long double b, long double range);

#endif /* SRC_ARITHMETIC_H_ */
