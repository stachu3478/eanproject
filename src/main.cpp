#include <iostream>
#include "Interval.h"
#include "puzzle.h"
#include "puzzle_i.h"
#include "assert.h"

using namespace std;
using namespace interval_arithmetic;

// TODO: Write interval arithmetic
int main()
{
	// test
	asserts();
	Interval<int>* interval = new Interval<int>(5, 9);
	int a = (*interval * *interval).a;
	int b = (*interval * *interval).b;
	std::cout << "Lewy: " << a << " " << "Prawy: " << b << endl;
	// koniec testu

	bool do_interval_calculations;
	cout << "Wcisnij 0, aby liczyc w arytmetyce punktowej lub 1, aby liczyc w arytmetyce przedzialowej" << endl;
	cin >> do_interval_calculations;

	if (do_interval_calculations)
		solve_i();
	else
		solve();
};
