#pragma once

// forward decls
class Tuple;
class Color;

// interface for Lights (abstract class)
class Light {
public:

	virtual Tuple position() = 0;
	virtual Color intensity() = 0;

	virtual ~Light() {}

};