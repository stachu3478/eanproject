/*
 * debug_i.h
 *
 *  Created on: Jul 28, 2020
 *      Author: linux
 */

#ifndef SRC_DEBUG_I_H_
#define SRC_DEBUG_I_H_

#include <iostream>
#include "Interval.h"

I** p_is_i(const char* t, I** v, int l, bool debug);

bool p_is_line_i(bool v);
I** p_line_ab_i(I** ab);
bool p_is_0_i(bool v);
bool p_is_horizontal_i(bool v);
bool p_is_vertical_i(bool v);
I* p_line_zero_i(I* v);

I* p_fx_i(I* x, I* y);

I* p_non_inf_start_x(I* parg);
bool p_is_0_in_range(bool v);
void p_newton_step_i(I* parg);
void p_bisect_newton_i(I* sx);
void p_restricted_newton_i(I* sx);
void p_range_test_i(I* a, I* b, int i);

void p_sort_i(I** arr, int l);
void p_pairs_i(I** arr, int l);
void p_group_i(I* eps, I** a1, int l1);

#endif /* SRC_DEBUG_I_H_ */
