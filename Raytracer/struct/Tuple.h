#pragma once

class Tuple {
	
public:

	double x, y, z, w;
	Tuple();
	Tuple(double, double, double, double);
	Tuple(const Tuple&);
	bool isAPoint() const { return w == 1; }
	bool isAVector() const { return w == 0; }
	double magnitude() const;
	Tuple normalize() const;
	Tuple reflect(const Tuple&) const;

	Tuple operator+(const Tuple&) const;
	Tuple operator-(const Tuple&) const;
	Tuple operator-() const;
	Tuple operator*(double) const;
	Tuple operator/(double) const;
	bool operator==(const Tuple&) const;
	double dot(const Tuple&) const;
	Tuple cross(const Tuple&) const;

};

Tuple point(double, double, double);
Tuple vec(double, double, double);

