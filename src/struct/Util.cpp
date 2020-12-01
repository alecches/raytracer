#include "../struct/Util.h"

bool doubleEqual(double a, double b) {
	if (abs(a - b) > Epsilon) return false;
	else return true;
}

double doubleMax(double a, double b, double c) {
	double max = a;
	if (b > max) max = b;
	if (c > max) max = c;
	return max;
}

double doubleMin(double a, double b, double c) {
	double min = a;
	if (b < min) min = b;
	if (c < min) min = c;
	return min;
}

double doubleMax(double a, double b) {
	if (a > b) return a;
	else return b;
}

double doubleMin(double a, double b) {
	if (a < b) return a;
	else return b;
}