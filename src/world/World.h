#pragma once
#include <list>
#include <memory>
#include "../object/Object.h"
#include "../light/Light.h"
#include "../world/Ray.h"

class World
{
private:
	std::list<Object*> objs_; // why not a list of std::unique_ptr? for now, i want to test my ability to use simple pointers
	std::list<Light*> lights_;
public:

	World() :objs_{std::list<Object*>()}, lights_{std::list<Light*>()} {}
	World(const World& w);
	World& operator=(const World&);
	void swap(World&, World&);

	const std::list<Object*>& objects() const { return objs_; } // why pass around a whole list? maybe just provide access function instead // No... just pass a ref to the list
	const std::list<Light*>& lights() const { return lights_; }

	void addObject(Object& o) { objs_.push_back(o.heapObject()); }
	void addLight(Light& l) {lights_.push_back(l.heapLight()); }

	~World();

};

World defaultWorld();
World defaultWorld(Light& l);
bool inShadow(const World&, const Tuple&);
void intersect(const Ray& r, const World& w, std::vector<Intersection>&);
Color shadeHit(const World&, const IntersectInfo&, int remainingDepth = 5);
Color colorAt(const World&, const Ray&, int remainingDepth = 5);
Color reflectedColor(const World&, const IntersectInfo&, int remainingDepth = 5);
Color refractedColor(const World&, const IntersectInfo&, int remainingDepth = 5);

