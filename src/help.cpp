/*
 * help.cpp
 *
 *  Created on: Jun 24, 2020
 *      Author: linux
 */
#include "help.h"

using namespace std;

long double abs_d(long double a)
{
	return a > 0 ? a : -a;
}

void cp(long double* a, long double* b, int n)
{
	for (int i = 0; i < n; i++)
		b[i] = a[i];
}

void group_frozen(ArrayOfDouble* arr, long double eps)
{
	return;
	int new_size = 0;
	for (int i = 0; i < arr->size; i++)
	{
		bool lacks = true;
		for (int j = 0; j < new_size; j++)
			if (in_range(arr->a[j], arr->a[i], eps))
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
	p_group(eps, arr->a, arr->size);
}

// !
void sort_frozen_by(long double* arr, int length, long double func(long double a))
{
	p_sort(arr, length);
	if (length <= 1) return;
	long double p = func(arr[0]);

	int i = 0, j = length - 1;
	while (1)
	{
		while (func(arr[i]) < p) i++;
		while (func(arr[j]) > p) j--;
		if (i < j)
		{
			long double tmp = arr[i];
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
	sort_frozen_by(arr, i, func);
	sort_frozen_by(arr + j, length - j, func);
};

void sort_frozen(long double* arr, int length)
{
	sort_frozen_by(arr, length, [](long double a) { return a; });
}

void pairs(ArrayOfDouble* list, Pairs* _)
{
	p_pairs(list->a, list->size);
	if (list->size == 0)
	{
		_->call(-Infinity, Infinity, +0);
		return;
	};
	_->call(-Infinity, list->a[0], +0);
	int i = 0;
	while (i < list->size - 1)
	{
		_->call(list->a[i], list->a[i + 1], i + 1);
		i++;
	}
	_->call(list->a[list->size - 1], Infinity, list->size);
};

long double sum_sort(long double a) { return abs(a); };
long double sum(long double* arr, int length)
{
	sort_frozen_by(arr, length, sum_sort);
	long double s = 0.;
	for (int i = length - 1; i >= 0; i--)
		s += arr[i];
	return s;
}
