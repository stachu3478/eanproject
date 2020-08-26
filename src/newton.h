/*
 * newton.h
 *
 *  Created on: Jun 23, 2020
 *      Author: linux
 */

#ifndef SRC_NEWTON_H_
#define SRC_NEWTON_H_

#include <cmath>
#include "function.h"
#include "line.h"
#include "help.h"
#include "debug.h"
#include "arithmetic.h"

ArrayOfDouble* rec_newton(W* wielomian, long double eps0, long double epsX, int loops);

class AllArgumentsSatisfiedException {};
class RangeException {};

#endif /* SRC_NEWTON_H_ */
