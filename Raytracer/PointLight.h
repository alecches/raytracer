#pragma once

#include "Light.h"

class PointLight : public Light
{
private:
	Tuple position_;
	Color intensity_;
public:
	PointLight(Tuple p, Color c) :position_{ p }, intensity_{ c } {}
	PointLight(const PointLight& pl) : position_{ pl.position() }, intensity_{ pl.intensity() } {}

	Color intensity() const { return intensity_; }
	Tuple position() const { return position_; }
	bool operator==(const Light& l) { return (position_ == l.position() && intensity_ == l.intensity()); }

	Light* heapLight() const { return new PointLight(*this); }

};

