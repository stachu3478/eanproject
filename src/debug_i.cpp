/*
 * debug_i.cpp
 *
 *  Created on: Jul 28, 2020
 *      Author: linux
 */
#include "debug_i.h"

using namespace std;

const bool debug_mode = true;
const bool sort_v = false;

bool p_bool_i(const char* t, bool v)
{
	if (debug_mode) cout << t << " " << v << endl;
	return v;
}

I* p_i(const char* t, I* v)
{
	if (debug_mode) cout << t << " " << v->a << " <-> " << v->b << endl;
	return v;
}

I** p_is_i(const char* t, I** v, int l, bool debug = debug_mode)
{
	if (!debug) return v;
	cout << t << " [";
	for (int i = 0; i < l; i++)
		cout << v[i]->a << " <-> " << v[i]->b << ", ";
	cout << "]" << endl;
	return v;
}

bool p_is_line_i(bool v) { return p_bool_i("Is line?", v); };
I** p_line_ab_i(I** ab) { return p_is_i("Line ab: ", ab, 2); };
bool p_is_0_i(bool v) { return p_bool_i("Is 0?", v); };
bool p_is_horizontal_i(bool v) { return p_bool_i("Is horizontal?", v); };
bool p_is_vertical_i(bool v) { return p_bool_i("Is vertical?", v); };
I* p_line_zero_i(I* v) { return p_i("Line zero: ", v); };

I* p_fx_i(I* x, I* y)
{
	if (debug_mode) cout << "f(" << x->a << " <-> " << x->b << ") = " << y->a << " <-> " << y->b << endl;
	return y;
}

bool p_is_0_in_range(bool v) { return p_bool_i("Is 0 in range I?", v); };
I* p_non_inf_start_x(I* parg) { return p_i("Non-infinity start I x =", parg); };
void p_newton_step_i(I* parg) { p_i("Newton step I x =", parg); };
void p_bisect_newton_i(I* sx) { p_i("Bisect newton I x =", sx); };
void p_restricted_newton_i(I* sx) { p_i("Restricted newton I x =", sx); };
void p_range_test_i(I* a, I* b, int i)
{
	if (debug_mode) cout << "Test in range big (" << a->a << ", " << b->b << ") " << i << endl;
	if (debug_mode) cout << "Test in range low (" << a->b << ", " << b->a << ") " << i << endl;
}

void p_sort_i(I** arr, int l) { if (sort_v) p_is_i("Sort ", arr, l); };
void p_pairs_i(I** arr, int l) { p_is_i("Pairs I", arr, l); };
void p_group_i(I* eps, I** a1, int l1)
{
	p_i("Group I eps = ", eps);
	p_is_i("To:", a1, l1);
}
