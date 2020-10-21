#include "Material.h"

bool Material::operator==(const Material& mat) const {
	if (!(color_ == mat.color())) return false;
	if (pattern_ != &mat.pattern()) return false;
	if (ambient_ != mat.ambient()) return false;
	if (diffuse_ != mat.diffuse()) return false;
	if (specular_ != mat.specular()) return false;
	if (shininess_ != mat.shininess()) return false;
	return true;
}

Material::Material(const Material& m): color_{ Color(m.color()) }, ambient_{ m.ambient() }, diffuse_{ m.diffuse() }, specular_{ m.specular() }, shininess_{ m.shininess() } {
	if (m.pattern_ != nullptr) pattern(m.pattern());
	else pattern_ = nullptr;
}

void Material::swap(Material& first, Material& second) {
	std::swap(first.color_, second.color_);
	std::swap(first.ambient_, second.ambient_);
	std::swap(first.specular_, second.specular_);
	std::swap(first.diffuse_, second.diffuse_);
	std::swap(first.shininess_, second.shininess_);
	std::swap(first.pattern_, second.pattern_);
}

Material& Material::operator=(const Material& m) {
	Material tempMat(m); 
	swap(*this, tempMat);
	return *this;
}

Material::~Material() {
	if (pattern_ != nullptr) delete pattern_;
}



