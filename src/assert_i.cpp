/*
 * assert.cpp
 *
 *  Created on: Jul 5, 2020
 *      Author: linux
 */

#include "assert_i.h"

using namespace std;

ArrayOfI* result_i;
PI* p_i;
void test_i(int* st, const char** mul, int size, long double* results, int result_count)
{
	I eps0 = I().IntRead("0.0001");
	I epsX = I().IntRead("0.0001");
	I* mul_i = new I[size];
	for (int i = 0; i < size; i++)
	{
		mul_i[i] = I().IntRead(mul[i]);
	};
	p_i = new PI(size, st, mul_i);
	result_i = rec_newton_i(p_i, &eps0, &epsX, 100);
	for (int i = 0; i < result_i->size; i++)
	{
		auto abs_i = (I(results[i], results[i]) - *result_i->a[i]).Absolute();
		if (abs_i.b > 0.0001)
		{
			cout << "Invalid result " << results[i] << " " << result_i->a[i]->a << " <-> " << result_i->a[i]->b << endl;
			throw p_i;
		}
	}
	if (result_count != result_i->size)
	{
		cout << "Invalid result length " << result_i->size << " " << result_count << endl;
		throw p_i;
	}
}


// TODO: Assertions in 6 & 7 degree from Wikipedia and 2 without solution
void asserts_i()
{
	int w1st[] = { 2, 1, 0 };
	const char* w1mul[] = { "1", "-1", "-2" };
	long double results1[] = { -1., 2. };
	int w2st[] = { 3, 2, 1, 0 };
	const char* w2mul[] = { "0.25", "0.75", "-1.5", "-2" };
	long double results2[] = { -4., -1., 2. };
	int w3st[] = { 4, 3, 2, 1, 0 };
	const char* w3mul[] = { "0.07142857142857142", "0.07142857142857142", "-0.9285714285714286", "-0.07142857142857142", "1.3571428571428572" };
	long double results3[] = { -3.93008, -1.26496, 1.33748, 2.85756};
	int w4st[] = { 5, 4, 3, 2, 1, 0 };
	const char* w4mul[] = { "0.05", "0.15", "-0.55", "-1.35", "0.5", "3.3" };
	long double results4[] = { -4.16553, 1.57435, 2.81519};
	int w5st[] = { 2, 1, 0 };
	const char* w5mul[] = { "2", "8", "3" };
	long double results5[] = { -3.58114, -0.418861 };
	int w6st[] = { 2, 1, 0 };
	const char* w6mul[] = { "1", "-1", "20" };
	long double results6[] = { };
	int w7st[] = { 3, 2, 1, 0 };
	const char* w7mul[] = { "0.25", "0.75", "1.5", "-2" };
	long double results7[] = { 0.858891 };

	test_i(w1st, w1mul, 3, results1, 2);
	test_i(w2st, w2mul, 4, results2, 3);
	test_i(w3st, w3mul, 5, results3, 4);
	test_i(w4st, w4mul, 6, results4, 3);
	test_i(w5st, w5mul, 3, results5, 2);
	test_i(w6st, w6mul, 3, results6, 0);
	test_i(w7st, w7mul, 4, results7, 1);
};


