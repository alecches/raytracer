#include "../struct/Tuple.h"
#include <cmath>

Tuple::Tuple() {
	x = 0.0;
	y = 0.0;
	z = 0.0;
	w = 3.0;
}

Tuple::Tuple(double a, double b, double c, double d) {
	x = a;
	y = b;
	z = c;
	w = d;
}

Tuple::Tuple(const Tuple& t) {
	x = t.x;
	y = t.y;
	z = t.z;
	w = t.w;
}

bool Tuple::operator==(const Tuple& t) const {

	const double E = 0.00001;

	if(abs(x - t.x) > E) return false;
	if (abs(y - t.y) > E) return false;
	if (abs(z - t.z) > E) return false;
	if (abs(w - t.w) > E) return false;
	return true;

}

Tuple Tuple::operator+(const Tuple& t) const {

	Tuple sum;
	sum.x = x + t.x;
	sum.y = y + t.y;
	sum.z = z + t.z;
	sum.w = w + t.w;

	return sum;
}

Tuple Tuple::operator-(const Tuple& t) const {

	Tuple difference;
	difference.x = x - t.x;
	difference.y = y - t.y;
	difference.z = z - t.z;
	difference.w = w - t.w;

	return difference;
}

Tuple Tuple::operator-() const {

	Tuple negative;
	negative.x = -x;
	negative.y = -y;
	negative.z = -z;
	negative.w = -w;

	return negative;
}

Tuple Tuple::operator*(double scalar) const {

	Tuple product;
	product.x = scalar * x;
	product.y = scalar * y;
	product.z = scalar * z;
		product.w = scalar * w;

	return product;
}

Tuple Tuple::operator/(double scalar) const {

	Tuple dividend;
	dividend.x = x / scalar;
	dividend.y = y / scalar;
	dividend.z = z / scalar;
	dividend.w = w / scalar;

	return dividend;

}

double Tuple::magnitude() const {

	return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));

}

Tuple Tuple::normalize() const {

	double m = magnitude();
	Tuple normalized(x / m, y / m, z / m, w / m);

	return normalized;
}

double Tuple::dot(const Tuple& t) const {
	return x * t.x + y * t.y + z * t.z + w * t.w;
}

Tuple Tuple::cross(const Tuple& t) const {
	Tuple product;

	product.x = y * t.z - z * t.y;
	product.y = z * t.x - x * t.z;
	product.z = x * t.y - y * t.x;
	product.w = w;

	return product;
}

Tuple Tuple::reflect(const Tuple& normal) const {
	if (w == 0) return (*this) - normal * 2 * (*this).dot(normal);
	else return Tuple(0, 0, 0, 0);
}


// Past TupleFactory members...

Tuple point(double a, double b, double c) {
	return Tuple(a, b, c, 1.0);
}

Tuple vec(double a, double b, double c) {
	return Tuple(a, b, c, 0.0);
}