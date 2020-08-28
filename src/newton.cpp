/*
 * newton.cpp
 *
 *  Created on: Jun 24, 2020
 *      Author: linux
 */
#include "newton.h"

using namespace std;

class RangeException {};

bool newton_step(P* polynomial, P* poch, long double& x, long double eps0)
{
	long double wx = fx(x, polynomial);
	long double wpx = fx(x, poch);
	if (strict_eq_greater_than(eps0, abs(wpx)))
		return false;
	long double change = wx / wpx;
	x -= change;
	wx = fx(x, polynomial);
	if (strict_eq_greater_than(eps0, abs(wx)))
		return false;
	p_newton_step(x);
	return true;
};

long double restricted_newton(P* polynomial, long double startX, long double eps0, int loops, Range* range)
{
	p_restricted_newton(startX);
	P* diff = fd(polynomial);
	long double parg = startX;
	for (int i = loops; i > 0; i--)
	{
		bool shouldContinue = newton_step(polynomial, diff, parg, eps0);
		if (greater_than(range->min, parg) || greater_than(parg, range->max))
			throw new RangeException();
		if (!shouldContinue)
			return parg;
	}
	throw new RangeException();
}

long double start_x(Range* ab)
{
	return (ab->min + ab->max) / 2.;
}

long double non_inf_start_x(Range* ab, long double epsX)
{
	if (eq(ab->min, (long double)-Infinity) && eq(ab->max, (long double)Infinity))
		return 0.;
	else if (eq(ab->min, (long double)-Infinity))
		return ab->max - epsX * 2;
	else if (eq(ab->max, (long double)Infinity))
		return ab->min + epsX * 2;
	return start_x(ab);
}

// Szuka rozwiazania na podstawie zasady roznic znakow, powtarza tak dlugo az nie znajdzie rozwiazania
long double bisect_newton_frozen(P* polynomial, long double startX, long double eps0, long double epsX, int loops, Range* range)
{
	p_bisect_newton(startX);
	long double newStartX = startX;
	for (int i = 0; i < loops; i++)
		try
		{
			return restricted_newton(polynomial, newStartX, eps0, loops, range);
		} catch (RangeException* e)
		{
			if (eq(range->min, (long double)-Infinity))
				throw new RangeException();
			if (eq(range->max, (long double)Infinity))
				throw new RangeException();
			bisection_frozen(polynomial, range, eps0);
			if (in_range(range->min, range->max, epsX))
				return range->min;
			newStartX = start_x(range);
		}
	throw new RangeException();
}

bool is_0_in_range(Range* range, P* polynomial)
{
	return sign_equal(fx(range->min, polynomial), fx(range->max, polynomial));
}

// Nie dzialajaca lamba wymusila stworzenie klasy
class RecNewtonRangeSearch: public Pairs
{
public:
	RecNewtonRangeSearch(ArrayOfDouble* a, P* b, long double c, long double d, int e) { newSolutions = a; polynomial = b; eps0 = c; epsX = d; loops = e;
		offset = 0;
	};
	void call(long double a, long double b, int i)
	{
		int next_index = i - offset;
		Range* range = new Range(a, b);
		p_range_test(a, b, next_index);
		long double startX = non_inf_start_x(range, epsX);
		if (is_0_in_range(range, polynomial))
		{
			offset++;
			newSolutions->size--;
			return;
		}
		newSolutions->a[next_index] = bisect_newton_frozen(polynomial, startX, eps0, epsX, loops, range);
	};
private:
	ArrayOfDouble* newSolutions;
	P* polynomial;
	long double eps0;
	long double epsX;
	int loops;
	int offset;
};

ArrayOfDouble* rec_newton(P* polynomial, long double eps0, long double epsX, int loops)
{
	if (is_line(polynomial))
	{
		long double* line = line_ab(polynomial);
		if (is_horizontal(line))
		{
			if (is_0(line))
				throw new AllArgumentsSatisfiedException();
			return new ArrayOfDouble();
		}
		ArrayOfDouble* solution = new ArrayOfDouble(1);
		solution->a[0] = line_zero(line);
		return solution;
	} else
	{
		ArrayOfDouble* dSolutions = rec_newton(fd(polynomial), eps0, epsX, loops);
		ArrayOfDouble* newSolutions = new ArrayOfDouble(dSolutions->size + 1);
		pairs(dSolutions, new RecNewtonRangeSearch(newSolutions, polynomial, eps0, epsX, loops));
		group_frozen(newSolutions, epsX);
		delete dSolutions;
		return newSolutions;
	}
}
