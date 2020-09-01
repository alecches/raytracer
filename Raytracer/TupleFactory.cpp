#include "TupleFactory.h"

Tuple* TupleFactory::point(double a, double b, double c) {
	return new Tuple(a, b, c, 1.0);
}

Tuple* TupleFactory::vector(double a, double b, double c) {
	return &Tuple(a, b, c, 0.0);
}


