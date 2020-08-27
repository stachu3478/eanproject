/*
 * newton_i.cpp
 *
 *  Created on: Aug 1, 2020
 *      Author: linux
 */

#include "newton_i.h"

using namespace std;

class RangeExceptionI {};

I* fx_helper_l(I* x, PI* p)
{
	I* y = fx_i(x, p);
	return new I(y->a, y->a);
}

I* fx_helper_r(I* x, PI* p)
{
	I* y = fx_i(x, p);
	return new I(y->b, y->b);
}

bool newton_step_i_lr(PI* polynomial, PI* poch, I* x, I* eps0, I* fx_f(I* x, PI* p))
{
	I* wx = fx_f(x, polynomial);
	I* wpx = fx_f(x, poch);
	I wpx_absolute = wpx->Absolute();
	if (strict_eq_greater_than_i(eps0, &wpx_absolute))
		return false;
	I x_ref = *x;
	x_ref -= *wx / *wpx;
	x->a = x_ref.a;
	x->b = x_ref.b;
	wx = fx_f(x, polynomial);
	I wx_absolute = wx->Absolute();
	if (strict_eq_greater_than_i(eps0, &wx_absolute))
		return false;
	p_newton_step_i(x);
	return true;
};

bool newton_step_i(PI* polynomial, PI* poch, I* x, I* eps0)
{
	I* wx = fx_i(x, polynomial);
	I* wpx = fx_i(x, poch);
	I wpx_absolute = wpx->Absolute();
	if (strict_eq_greater_than_i(eps0, &wpx_absolute))
		return false;
	I x_ref = *x;
	x_ref -= *wx / *wpx;
	x->a = x_ref.a;
	x->b = x_ref.b;
	wx = fx_i(x, polynomial);
	I wx_absolute = wx->Absolute();
	if (strict_eq_greater_than_i(eps0, &wx_absolute))
		return false;
	p_newton_step_i(x);
	return true;
};

I* restricted_newton_i(PI* polynomial, I* startX, I* eps0, int loops, RangeI* range, I* fx_f(I* x, PI* p))
{
	p_restricted_newton_i(startX);
	PI* poch = fd_i(polynomial);
	I* parg = startX;
	for (int i = loops; i > 0; i--)
	{
		bool shouldContinue = newton_step_i_lr(polynomial, poch, parg, eps0, fx_f);
		if (greater_than_i(range->min, parg) || greater_than_i(parg, range->max))
			throw new RangeExceptionI();
		if (!shouldContinue)
			return parg;
	}
	throw new RangeExceptionI();
}

I* start_x(RangeI* ab)
{
	long double x = (ab->min->b + ab->max->a) / (long double)2.;
	return new I(x, x);
}

I* non_inf_start_x(RangeI* ab, I* epsX)
{
	if (eq_i(ab->min, MIInfinity()))
	{
		I return_value = *(ab->max) - epsX->Scale(2);
		I* return_value_pointer = new I(return_value.a, return_value.b);
		return p_non_inf_start_x(return_value_pointer);
	}
	else if (eq_i(ab->max, IInfinity()))
	{
		I return_value = *(ab->min) + epsX->Scale(2);
		I* return_value_pointer = new I(return_value.a, return_value.b);
		return p_non_inf_start_x(return_value_pointer);
	}
	return p_non_inf_start_x(start_x(ab));
}

// Szuka rozwiazania na podstawie zasady roznic znakow, powtarza tak dlugo az nie znajdzie rozwiazania
I* bisect_newton_frozen(PI* polynomial, I* startX, I* eps0, I* epsX, int loops, RangeI* range, I* fx_f(I* x, PI* p))
{
	p_bisect_newton_i(startX);
	I* newStartX = startX;
	for (int i = 0; i < loops; i++)
		try
		{
			return restricted_newton_i(polynomial, newStartX, eps0, loops, range, fx_f);
		} catch (RangeExceptionI* e)
		{
			if (eq_i(range->min, MIInfinity()))
				throw new RangeExceptionI();
			if (eq_i(range->max, IInfinity()))
				throw new RangeExceptionI();
			bisection_frozen_i(polynomial, range, eps0);
			if (strict_in_range_i(range->min, range->max, epsX))
				return new I(range->min->a, range->max->b);
			newStartX = start_x(range);
		}
	throw new RangeExceptionI();
}

bool is_0_in_range(RangeI* range, PI* polynomial)
{
	return p_is_0_in_range(sign_equal_i(fx_i(range->min, polynomial), fx_i(range->max, polynomial)));
}

// Nie dzialajaca lamba wymusila stworzenie klasy
class RecNewtonRangeSearchI: public PairsI
{
public:
	RecNewtonRangeSearchI(ArrayOfI* a, PI* b, I* c, I* d, int e) { newSolutions = a; polynomial = b; eps0 = c; epsX = d; loops = e;
		offset = 0;
	};
	void call(I* a, I* b, int i)
	{
		int next_index = i - offset;
		RangeI* range = new RangeI(a, b);
		p_range_test_i(a, b, next_index);
		I* startX = non_inf_start_x(range, epsX);
		if (is_0_in_range(range, polynomial))
		{
			offset++;
			newSolutions->size--;
			return;
		}
		I* r_l = bisect_newton_frozen(polynomial, startX, eps0, epsX, loops, range, fx_helper_l);
		I* r_r = bisect_newton_frozen(polynomial, startX, eps0, epsX, loops, range, fx_helper_r);
		I* r = new I(r_l->a, r_l->b);
		if (r_r->a < r->a) r->a = r_r->a;
		if (r_r->b > r->b) r->b = r_r->b;
		newSolutions->a[next_index] = r;
	};
private:
	ArrayOfI* newSolutions;
	PI* polynomial;
	I* eps0;
	I* epsX;
	int loops;
	int offset;
};

ArrayOfI* rec_newton_i(PI* polynomial, I* eps0, I* epsX, int loops)
{
	if (is_line_i(polynomial))
	{
		I** line = line_ab_i(polynomial);
		if (is_horizontal_i(line))
		{
			if (is_0_i(line))
				throw new AllArgumentsSatisfiedExceptionI();
			return new ArrayOfI();
		}
		ArrayOfI* solution = new ArrayOfI(1);
		I* zero_line_point_x = line_zero_i(line);
		solution->a[0] = zero_line_point_x;
		return solution;
	} else
	{
		ArrayOfI* dSolutions = rec_newton_i(fd_i(polynomial), eps0, epsX, loops);
		ArrayOfI* newSolutions = new ArrayOfI(dSolutions->size + 1);
		pairs_i(dSolutions, new RecNewtonRangeSearchI(newSolutions, polynomial, eps0, epsX, loops));
		group_frozen_i(newSolutions, epsX);
		delete dSolutions;
		return newSolutions;
	}
}
