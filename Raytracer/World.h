#pragma once
#include <list>
#include <memory>
#include "Object.h"
#include "Light.h"

class World
{
private:
	std::list<Object*> objs_; // why not a list of std::unique_ptr? for now, i want to test my ability to use simple pointers
	std::list<Light*> lights_;
public:

	World() :objs_{std::list<Object*>()}, lights_{std::list<Light*>()} {}

	std::list<Object*> objects() const { return objs_; } // why pass around a whole list? maybe just provide access function instead
	std::list<Light*> lights() const {return lights_; }
	void addObject(Object& o) { objs_.push_back(o.heapObject()); }
	void addLight(Light& l) {lights_.push_back(l.heapLight()); } // for now, only one light allowed

	~World();

};

World defaultWorld();
World defaultWorld(Light& l);
bool inShadow(const World&, const Tuple&);

