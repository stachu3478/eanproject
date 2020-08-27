/*
 * help_i.cpp
 *
 *  Created on: Jul 28, 2020
 *      Author: linux
 */

#include "help_i.h"

using namespace std;

I* IInfinity() { return new I(std::numeric_limits<long double>::infinity(), std::numeric_limits<long double>::infinity()); };
I* MIInfinity() { return new I(-std::numeric_limits<long double>::infinity(), -std::numeric_limits<long double>::infinity()); };

void cp_i(double* a, double* b, int n)
{
	for (int i = 0; i < n; i++)
		b[i] = a[i];
}

void group_frozen_i(ArrayOfI* arr, I* eps)
{
	int new_size = 0;
	for (int i = 0; i < arr->size; i++)
	{
		bool lacks = true;
		for (int j = 0; j < new_size; j++)
			if (in_range_i(arr->a[j], arr->a[i], eps))
			{
				lacks = false;
				break;
			}
		if (lacks)
		{
			arr->a[new_size] = arr->a[i];
			new_size++;
		}
	}
	arr->size = new_size;
	p_group_i(eps, arr->a, arr->size);
}

// !
void sort_frozen_by_i(I** arr, int length, long double func(I* a))
{
	p_sort_i(arr, length);
	if (length <= 1) return;
	long double p = func(arr[0]);

	int i = 0, j = length - 1;
	while (1)
	{
		while (func(arr[i]) < p) i++;
		while (func(arr[j]) > p) j--;
		if (i < j)
		{
			I* tmp = arr[i];
			arr[i++] = arr[j];
			arr[j--] = tmp;
		} else if (i > j)
		{
			int tmp = i;
			i = j + 1;
			j = tmp;
			break;
		} else
		{
			j = i + 1;
			break;
		}
	}

	if (length == 2) return;
	sort_frozen_by_i(arr, i, func);
	sort_frozen_by_i(arr + j, length - j, func);
};

void sort_frozen_i(I** arr, int length)
{
	sort_frozen_by_i(arr, length, [](I* i) { return i->b; });
}

void pairs_i(ArrayOfI* list, PairsI* _)
{
	p_pairs_i(list->a, list->size);
	if (list->size == 0) return;
	_->call(MIInfinity(), list->a[0], +0);
	int i = 0;
	while (i < list->size - 1)
	{
		_->call(list->a[i], list->a[i + 1], i + 1);
		i++;
	}
	_->call(list->a[list->size - 1], IInfinity(), list->size);
};

long double sum_sort_i(I* i) { return i->Absolute().b; };
I* sum_i(I** arr, int length)
{
	sort_frozen_by_i(arr, length, sum_sort_i);
	I s(0., 0.);
	for (int i = length - 1; i >= 0; i--)
		s += *arr[i];
	return new I(s.a, s.b);
}
