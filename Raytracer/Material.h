#pragma once
#include "Color.h"
#include "PointLight.h"
#include <utility>

// to be removed in the future
#include "World.h"
#include "Intersection.h"

class Material
{
private:
	Color color_;
	double ambient_, diffuse_, specular_, shininess_;
public:

	Material() :color_{ Color(1, 1, 1) }, ambient_{ 0.1 }, diffuse_{ 0.9 }, specular_{ 0.9 }, shininess_{ 200.0 } { }
	Material(const Material& m) : color_{ Color(m.color()) }, ambient_{ m.ambient() }, diffuse_{ m.diffuse() }, specular_{ m.specular() }, shininess_{ m.shininess() } {}
	Color color() const { return color_; }
	void color(Color c) { color_ = std::move(c); }
	double ambient() const { return ambient_; }
	void ambient(double d) { ambient_ = d; } // std::move might be excessive for a type double
	double diffuse() const { return diffuse_; }
	void diffuse(double d) { diffuse_ = d; }
	double specular() const { return specular_; }
	void specular(double d) { specular_ = d; }
	double shininess() const { return shininess_; }

	bool operator==(const Material&);
	
};

// to be moved to generic Light class when needed.. or member of material?
Color lighting(const Material&, const Light&, const Tuple&, const Tuple&, const Tuple&);
Color shadeHit(const World&, const IntersectInfo&);
Color colorAt(const World&, const Ray&);
