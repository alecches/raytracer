#pragma once
#include "Tuple.h"

class TupleFactory
{
private: 
	Tuple* tuple;
public:
	Tuple* point(double, double, double);
	Tuple* vector(double, double, double);
};

