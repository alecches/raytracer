#pragma once
#include "../property/Color.h"
#include "Pattern.h"
#include <utility>

class Material
{
private:
	Color color_;
	Pattern* pattern_;
	double ambient_, diffuse_, specular_, shininess_, reflective_, transparency_, refractiveIndex_;
public:

	Material() :color_{ Color(1, 1, 1) }, pattern_{ nullptr }, ambient_{ 0.1 }, diffuse_{ 0.9 }, specular_{ 0.9 },
		shininess_{ 200.0 }, reflective_{ 0.0 }, refractiveIndex_{ 1.0 }, transparency_{ 0.0 } { }
	Material(const Material& m);
	Material& operator=(const Material& m);
	void swap(Material& first, Material& second);

	Color color() const { return color_; }
	void color(Color c) { color_ = std::move(c); }
	const Pattern& pattern() const { return *pattern_; }
	void pattern(const Pattern& p) { pattern_ = p.heapPattern(); }
	double ambient() const { return ambient_; }
	void ambient(double d) { ambient_ = d; } 
	double diffuse() const { return diffuse_; }
	void diffuse(double d) { diffuse_ = d; }
	double specular() const { return specular_; }
	void specular(double d) { specular_ = d; }
	double shininess() const { return shininess_; }
	void reflective(double d) { reflective_ = d; }
	double reflective() const { return reflective_; }
	void transparency(double d) { transparency_ = d; }
	double transparency() const { return transparency_; }
	void refractiveIndex(double d) { refractiveIndex_ = d; }
	double refractiveIndex() const { return refractiveIndex_; }

	bool operator==(const Material&) const;
	~Material();
	
};



