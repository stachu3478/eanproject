#include <iostream>
#include "Interval.h"
#include "puzzle.h"
#include "puzzle_i.h"
#include "assert.h"

using namespace std;
using namespace interval_arithmetic;

int main()
{
	// test
	asserts();

	bool do_interval_calculations;
	cout << "Wcisnij 0, aby liczyc w arytmetyce punktowej lub 1, aby liczyc w arytmetyce przedzialowej" << endl;
	cin >> do_interval_calculations;

	if (do_interval_calculations)
		solve_i();
	else
		solve();
};
