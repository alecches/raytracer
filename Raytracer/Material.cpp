#include "Material.h"
#include "Ray.h"
#include <cmath>

bool Material::operator==(const Material& mat) {
	if (!(color_ == mat.color())) return false;
	if (ambient_ != mat.ambient()) return false;
	if (diffuse_ != mat.diffuse()) return false;
	if (specular_ != mat.specular()) return false;
	if (shininess_ != mat.shininess()) return false;
	return true;
}

Color lighting(const Material& mat, const Light& light, const Tuple& position,const Tuple& eyev, const Tuple& normalv){

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

Color shadeHit(const World& w, const IntersectInfo& i) {
	std::list<Light*> lights = w.lights();

	Color c(0, 0, 0);
	for (auto l : lights) {
		c = c + lighting(i.object->material(), *l, i.point, i.eyev, i.normalv);
	}

	return c;
}

Color colorAt(const World& w, const Ray& r) {
	std::deque<Intersection> intx = r.intersect(w);
	int i = hit(intx);
	if (i < 0) return Color(0, 0, 0);
	IntersectInfo iInf(intx[i], r);
	return shadeHit(w, iInf);
}