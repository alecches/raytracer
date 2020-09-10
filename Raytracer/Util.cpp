#include "Util.h"

bool doubleEqual(double a, double b) {
	if (abs(a - b) > Epsilon) return false;
	else return true;
}