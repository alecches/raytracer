#include "Light.h"

Color lighting(const Material& mat, const Light& light, const Tuple& position, const Tuple& eyev, const Tuple& normalv, bool inShadow) {

	Color effectiveColor = mat.color() * light.intensity();

	Tuple lightv = (light.position() - position).normalize();

	Color ambient = effectiveColor * mat.ambient();
	if (inShadow) return ambient;
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