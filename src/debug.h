/*
 * debug.h
 *
 *  Created on: Jul 7, 2020
 *      Author: linux
 */

#ifndef SRC_DEBUG_H_
#define SRC_DEBUG_H_

#include <iostream>

bool p_is_line(bool v);
long double* p_line_ab(long double* ab);
bool p_is_0(bool v);
bool p_is_horizontal(bool v);
bool p_is_vertical(bool v);
long double p_line_zero(long double v);

long double p_fx(long double x, long double y);

void p_newton_step(long double parg);
void p_bisect_newton(long double sx);
void p_restricted_newton(long double sx);
void p_range_test(long double a, long double b, int i);

void p_sort(long double* arr, int l);
void p_pairs(long double* arr, int l);
void p_group(long double eps, long double* a1, int l1);

#endif /* SRC_DEBUG_H_ */
