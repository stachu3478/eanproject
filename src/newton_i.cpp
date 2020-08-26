/*
 * newton_i.cpp
 *
 *  Created on: Aug 1, 2020
 *      Author: linux
 */

#include "newton_i.h"

using namespace std;

bool newton_step_i(WI* wielomian, WI* poch, I* x, I* eps0)
{
	I* wx = fx_i(x, wielomian);
	I* wpx = fx_i(x, poch);
	I wpx_absolute = wpx->Absolute();
	if (strict_eq_greater_than_i(eps0, &wpx_absolute))
		return false;
	I x_ref = *x;
	x_ref -= *wx / *wpx;
	wx = fx_i(x, wielomian);
	I wx_absolute = wx->Absolute();
	if (strict_eq_greater_than_i(eps0, &wx_absolute))
		return false;
	p_newton_step_i(x);
	return true;
};

I* restricted_newton_i(WI* wielomian, I* startX, I* eps0, int loops, RangeI* range)
{
	p_restricted_newton_i(startX);
	WI* poch = fd_i(wielomian);
	I* parg = startX;
	for (int i = loops; i > 0; i--)
	{
		bool shouldContinue = newton_step_i(wielomian, poch, parg, eps0);
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
		I* return_value_pointer = &return_value;
		return p_non_inf_start_x(return_value_pointer);
	}
	else if (eq_i(ab->max, IInfinity()))
	{
		I return_value = *(ab->min) + epsX->Scale(2);
		I* return_value_pointer = &return_value;
		return p_non_inf_start_x(return_value_pointer);
	}
	return p_non_inf_start_x(start_x(ab));
}

// Szuka rozwiazania na podstawie zasady roznic znakow, powtarza tak dlugo az nie znajdzie rozwiazania
I* bisect_newton_frozen(WI* wielomian, I* startX, I* eps0, I* epsX, int loops, RangeI* range)
{
	p_bisect_newton_i(startX);
	I* newStartX = startX;
	for (int i = 0; i < loops; i++)
		try
		{
			return restricted_newton_i(wielomian, newStartX, eps0, loops, range);
		} catch (RangeExceptionI* e)
		{
			if (eq_i(range->min, MIInfinity()))
				throw new RangeExceptionI();
			if (eq_i(range->max, IInfinity()))
				throw new RangeExceptionI();
			bisection_frozen_i(wielomian, range, eps0);
			if (strict_in_range_i(range->min, range->max, epsX))
				return new I(range->min->a, range->max->b);
			newStartX = start_x(range);
		}
	throw new RangeExceptionI();
}

bool is_0_in_range(RangeI* range, WI* wielomian)
{
	return p_is_0_in_range(sign_equal_i(fx_i(range->min, wielomian), fx_i(range->max, wielomian)));
}

// Nie dzialajaca lamba wymusila stworzenie klasy
class RecNewtonRangeSearchI: public PairsI
{
public:
	RecNewtonRangeSearchI(ArrayOfI* a, WI* b, I* c, I* d, int e) { newSolutions = a; wielomian = b; eps0 = c; epsX = d; loops = e;
		offset = 0;
	};
	void call(I* a, I* b, int i)
	{
		int next_index = i - offset;
		RangeI* range = new RangeI(a, b);
		p_range_test_i(a, b, next_index);
		I* startX = non_inf_start_x(range, epsX);
		if (is_0_in_range(range, wielomian))
		{
			offset++;
			newSolutions->size--;
			return;
		}
		newSolutions->a[next_index] = bisect_newton_frozen(wielomian, startX, eps0, epsX, loops, range);
	};
private:
	ArrayOfI* newSolutions;
	WI* wielomian;
	I* eps0;
	I* epsX;
	int loops;
	int offset;
};

ArrayOfI* rec_newton_i(WI* wielomian, I* eps0, I* epsX, int loops)
{
	if (is_line_i(wielomian))
	{
		I** line = line_ab_i(wielomian);
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
		ArrayOfI* dSolutions = rec_newton_i(fd_i(wielomian), eps0, epsX, loops);
		sort_frozen_i(dSolutions->a, dSolutions->size);
		ArrayOfI* newSolutions = new ArrayOfI(dSolutions->size + 1);
		pairs_i(dSolutions, new RecNewtonRangeSearchI(newSolutions, wielomian, eps0, epsX, loops));
		group_frozen_i(newSolutions, epsX);
		delete dSolutions;
		return newSolutions;
	}
}
