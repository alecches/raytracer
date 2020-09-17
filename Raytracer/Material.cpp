#include "Material.h"
#include <cmath>

bool Material::operator==(const Material& mat) {
	if (!(color_ == mat.color())) return false;
	if (ambient_ != mat.ambient()) return false;
	if (diffuse_ != mat.diffuse()) return false;
	if (specular_ != mat.specular()) return false;
	if (shininess_ != mat.shininess()) return false;
	return true;
}

Color lighting(const Material& mat,const PointLight& light, const Tuple& position,const Tuple& eyev, const Tuple& normalv){
	Color effectiveColor = mat.color() * light.intensity();

	Tuple lightv = (light.position() - position).normalize();

	Color ambient = effectiveColor * mat.ambient();
	Color diffuse = Color(0, 0, 0);
	Color specular = Color(0, 0, 0);

	double lightDotNormal = lightv.dot(normalv);
	if (lightDotNormal > 0) {
		diffuse = effectiveColor * mat.diffuse() * lightDotNormal;

		Tuple reflectv = (-lightv).reflect(normalv);
		double reflectDotEye = reflectv.dot(eyev);

		if (reflectDotEye > 0) {
			double shinyFactor = pow(reflectDotEye, mat.shininess());
			specular = light.intensity() * mat.specular() * shinyFactor;
		}
	}

	return ambient + diffuse + specular;
}