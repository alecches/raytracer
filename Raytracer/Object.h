#pragma once
/*
#include "Tuple.h"
#include "Matrix.h"
#include "Material.h"
*/

// forward decls
class Tuple;
class Matrix;
class Material;

// interface for objs (abstract class)
class Object {
public:

	virtual Object* heapObject() const = 0;

	virtual Tuple position() const = 0;
	virtual Matrix transform() const = 0;
	virtual Material material() const = 0;

	virtual ~Object() {}
};
