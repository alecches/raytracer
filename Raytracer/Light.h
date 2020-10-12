#pragma once

// forward decls
#include "Material.h"
#include "Color.h"
#include "Tuple.h"


// interface for Lights (abstract class)
class Light {
public:

	virtual Tuple position() const = 0;
	virtual Color intensity() const = 0;

	virtual bool operator==(const Light&) = 0;

	virtual Light* heapLight() const = 0;
	virtual ~Light() {}

};

Color lighting(const Material&, const Light&, const Tuple&, const Tuple&, const Tuple&, bool);

