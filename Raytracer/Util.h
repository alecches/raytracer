#pragma once
#include <cmath>
#include "Matrix.h"

const double Epsilon = 0.00001;


bool doubleEqual(double a, double b) {
	if (abs(a - b) > Epsilon) return false;
	else return true;
}

