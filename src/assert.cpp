/*
 * assert.cpp
 *
 *  Created on: Jul 5, 2020
 *      Author: linux
 */

#include "assert.h"

using namespace std;

ArrayOfDouble* result;
P* p;
void test(int* st, long double* mul, int size, long double* results, int result_count)
{
	p = new P(size, st, mul);
	result = rec_newton(p, 0.0001, 0.0001, 100);
	for (int i = 0; i < result->size; i++)
	{
		if (abs_d(results[i] - result->a[i]) > 0.0001)
		{
			cout << "Invalid result " << results[i] << " " << result->a[i] << endl;
			throw p;
		}
	}
	if (result_count != result->size)
	{
		cout << "Invalid result length " << result->size << " " << result_count << endl;
		throw p;
	}
}


// TODO: Assertions in 6 & 7 degree from Wikipedia
void asserts()
{
	int w1st[] = { 2, 1, 0 };
	long double w1mul[] = { 1., -1., -2. };
	long double results1[] = { -1., 2. };
	int w2st[] = { 3, 2, 1, 0 };
	long double w2mul[] = { 1/4., 3/4., -3/2., -2. };
	long double results2[] = { -4., -1., 2. };
	int w3st[] = { 4, 3, 2, 1, 0 };
	long double w3mul[] = { 1/14., 1/14., -13/14., -1/14., 19/14. };
	long double results3[] = { -3.93008, -1.26496, 1.33748, 2.85756};
	int w4st[] = { 5, 4, 3, 2, 1, 0 };
	long double w4mul[] = { 1/20., 3/20., -11/20., -27/20., 10/20., 66/20. };
	long double results4[] = { -4.16553, 1.57435, 2.81519};
	int w5st[] = { 2, 1, 0 };
	long double w5mul[] = { 2., 8., 3. };
	long double results5[] = { -3.58114, -0.418861 };
	int w6st[] = { 2, 1, 0 };
	long double w6mul[] = { 1., -1., 20. };
	long double results6[] = { };
	int w7st[] = { 3, 2, 1, 0 };
	long double w7mul[] = { 0.25, 0.75, 1.5, -2. };
	long double results7[] = { 0.858891 };

	test(w1st, w1mul, 3, results1, 2);
	test(w2st, w2mul, 4, results2, 3);
	test(w3st, w3mul, 5, results3, 4);
	test(w4st, w4mul, 6, results4, 3);
	test(w5st, w5mul, 3, results5, 2);
	test(w6st, w6mul, 3, results6, 0);
	test(w7st, w7mul, 4, results7, 1);
};


