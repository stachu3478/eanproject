/*
 * line_i.h
 *
 *  Created on: Aug 1, 2020
 *      Author: linux
 */

#ifndef SRC_LINE_I_H_
#define SRC_LINE_I_H_

#include <iostream>
#include "function_i.h"
#include "help_i.h"
#include "debug_i.h"
#include "arithmetic_i.h"

bool is_line_i(PI* polynomial);
I** line_ab_i(PI* polynomial);
bool is_0_i(I** ab);
bool is_horizontal_i(I** ab);
bool is_vertical_i(I** ab);
I* line_zero_i(I** ab);

#endif /* SRC_LINE_I_H_ */
