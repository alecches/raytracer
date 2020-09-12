#include "TupleFactory.h"

	Tuple point(double a, double b, double c) {
		return Tuple(a, b, c, 1.0);
	}

	Tuple vec(double a, double b, double c) {
		return Tuple(a, b, c, 0.0);
	}

