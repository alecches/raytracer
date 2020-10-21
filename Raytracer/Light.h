#pragma once
#include "Material.h"
#include "Color.h"
#include "Tuple.h"

class Light {
public:

	virtual Tuple position() const = 0;
	virtual Color intensity() const = 0;

	virtual bool operator==(const Light&) const = 0;

	virtual Light* heapLight() const = 0;
	virtual ~Light() {}

};

Color lighting(const Material&, const Object&, const Light&, const Tuple&, const Tuple&, const Tuple&, bool);

