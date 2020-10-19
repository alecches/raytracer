#pragma once
#include "Color.h"
#include "Pattern.h"
#include <utility>

// to be removed in the future

class Material
{
private:
	Color color_;
	Pattern* pattern_;
	double ambient_, diffuse_, specular_, shininess_;
public:

	Material() :color_{ Color(1, 1, 1) }, pattern_{nullptr}, ambient_{ 0.1 }, diffuse_{ 0.9 }, specular_{ 0.9 }, shininess_{ 200.0 } { }
	Material(const Material& m);
	Material& operator=(Material& m);
	void swap(Material& first, Material& second);

	Color color() const { return color_; }
	void color(Color c) { color_ = std::move(c); }
	const Pattern& pattern() const { return *pattern_; }
	void pattern(const Pattern& p) {pattern_ = p.heapPattern(); }//.heapPattern(); }//pattern_ = p.heapPattern();
	double ambient() const { return ambient_; }
	void ambient(double d) { ambient_ = d; } // std::move might be excessive for a type double
	double diffuse() const { return diffuse_; }
	void diffuse(double d) { diffuse_ = d; }
	double specular() const { return specular_; }
	void specular(double d) { specular_ = d; }
	double shininess() const { return shininess_; }

	bool operator==(const Material&);
	//~Material() { if(pattern_ != nullptr) delete pattern_; } // when is this being called??  IntersectInfo..?
	~Material();
	
};

// to be moved to generic Light class when needed.. or member of material?


