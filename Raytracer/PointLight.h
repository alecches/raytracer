#pragma once
#include "Color.h"
#include "Tuple.h"

class PointLight
{
private:
	Tuple position_;
	Color intensity_;
public:
	PointLight(Tuple p, Color c) :position_{ p }, intensity_{ c } {}
	Color intensity() const { return intensity_; }
	Tuple position() const { return position_; }
};

