#include "Material.h"
#include "Ray.h"
#include "Object.h"
#include <cmath>

bool Material::operator==(const Material& mat) {
	if (!(color_ == mat.color())) return false;
	if (ambient_ != mat.ambient()) return false;
	if (diffuse_ != mat.diffuse()) return false;
	if (specular_ != mat.specular()) return false;
	if (shininess_ != mat.shininess()) return false;
	return true;
}



