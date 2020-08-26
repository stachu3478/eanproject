/*
 * newton_i.h
 *
 *  Created on: Aug 1, 2020
 *      Author: linux
 */

#ifndef SRC_NEWTON_I_H_
#define SRC_NEWTON_I_H_

#include <cmath>
#include "function_i.h"
#include "line_i.h"
#include "help_i.h"
#include "debug_i.h"
#include "arithmetic_i.h"

ArrayOfI* rec_newton_i(WI* wielomian, I* eps0, I* epsX, int loops);

class AllArgumentsSatisfiedExceptionI {};
class RangeExceptionI {};

#endif /* SRC_NEWTON_I_H_ */
