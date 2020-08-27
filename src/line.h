/*
 * line.h
 *
 *  Created on: Jun 24, 2020
 *      Author: linux
 */

#ifndef SRC_LINE_H_
#define SRC_LINE_H_

#include <limits>
#include <iostream>
#include "function.h"
#include "help.h"
#include "debug.h"
#include "arithmetic.h"

bool is_line(P* polynomial);
long double* line_ab(P* polynomial);
bool is_0(long double* ab);
bool is_horizontal(long double* ab);
bool is_vertical(long double* ab);
long double line_zero(long double* ab);

#endif /* SRC_LINE_H_ */
