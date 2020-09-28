#pragma once

// forward decls
class Tuple;
class Color;

// interface for Lights (abstract class)
class Light {
public:

	virtual Tuple position() const = 0;
	virtual Color intensity() const = 0;

	virtual bool operator==(const Light&) = 0;

	virtual Light* heapLight() const = 0;
	virtual ~Light() {}

};