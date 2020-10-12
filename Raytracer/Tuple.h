#pragma once

class Tuple {
	
public:

	double x, y, z, w;
	Tuple();
	Tuple(double, double, double, double);
	Tuple(const Tuple&);
	bool isAPoint() { return w == 1; }
	bool isAVector() { return w == 0; }
	bool equals(Tuple);
	double magnitude();
	Tuple normalize();
	Tuple reflect(Tuple);

	Tuple operator+(Tuple);
	Tuple operator-(Tuple);
	Tuple operator-();
	Tuple operator*(double);
	Tuple operator/(double);
	bool operator==(Tuple);
	double dot(Tuple);
	Tuple cross(Tuple);

};

Tuple point(double, double, double);
Tuple vec(double, double, double);

