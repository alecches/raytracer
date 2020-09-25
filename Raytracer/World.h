#pragma once
#include <list>
#include "Object.h"
#include "Light.h"

class World
{
private:
	std::list<Object> objs_;
	std::list<Light> lights_;
public:
	std::list<Object> objects() const { return objs_; }
	std::list<Light> lights() const {return lights_; }

};

