/*
 * debug.cpp
 *
 *  Created on: Jul 7, 2020
 *      Author: linux
 */
#include "debug.h"

using namespace std;

const bool debug_mode = false;
const bool sort_v = false;

bool p_bool(const char* t, bool v)
{
	if (debug_mode) cout << t << " " << v << endl;
	return v;
}

long double p_double(const char* t, long double v)
{
	if (debug_mode) cout << t << " " << v << endl;
	return v;
}

long double* p_doubles(const char* t, long double* v, int l)
{
	if (!debug_mode) return v;
	cout << t << " [";
	for (int i = 0; i < l; i++)
		cout << v[i] << ", ";
	cout << "]" << endl;
	return v;
}

bool p_is_line(bool v) { return p_bool("Is line?", v); };
long double* p_line_ab(long double* ab) { return p_doubles("Line ab: ", ab, 2); };
bool p_is_0(bool v) { return p_bool("Is 0?", v); };
bool p_is_horizontal(bool v) { return p_bool("Is horizontal?", v); };
bool p_is_vertical(bool v) { return p_bool("Is vertical?", v); };
long double p_line_zero(long double v) { return p_double("Line zero: ", v); };

long double p_fx(long double x, long double y)
{
	if (debug_mode) cout << "f(" << x << ") = " << y << endl;
	return y;
}

void p_newton_step(long double parg) { p_double("Newton step x =", parg); };
void p_bisect_newton(long double sx) { p_double("Bisect newton x =", sx); };
void p_restricted_newton(long double sx) { p_double("Restricted newton x =", sx); };
void p_range_test(long double a, long double b, int i)
{
	if (debug_mode) cout << "Test in range (" << a << ", " << b << ") " << i << endl;
}

void p_sort(long double* arr, int l) { if (sort_v) p_doubles("Sort ", arr, l); };
void p_pairs(long double* arr, int l) { p_doubles("Pairs ", arr, l); };
void p_group(long double eps, long double* a1, int l1)
{
	p_double("Group eps =", eps);
	p_doubles("To:", a1, l1);
}

