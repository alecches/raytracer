#pragma once
#include "Color.h"
#include "Tuple.h"
#include "Matrix.h"
class Object;

class Pattern {
public:
	virtual Color colorAt(const Tuple&) const = 0;
	virtual Color colorAtObject(const Tuple&, const Object&) const = 0;
	virtual Pattern* heapPattern() const = 0;

	virtual ~Pattern() {}
};

class stripePattern : public Pattern {

private:
	Color a_;
	Color b_;
	Matrix transform_;

public:
	stripePattern(Color c1, Color c2) : a_{ Color(c1) }, b_{ Color(c2) }, transform_{ Matrix(identity()) } {}
	stripePattern(const stripePattern& p) : a_{ p.a() }, b_{ p.b() }, transform_{ p.transform() } {}
	// copy constructor? default okay..
	Pattern* heapPattern() const { return new stripePattern(*this); }

	Color colorAt(const Tuple&) const;
	Color colorAtObject(const Tuple&, const Object&) const;
	
	Color a() const { return a_; }
	Color b() const { return b_; }
	Matrix transform() const { return transform_;}
	void transform(const Matrix& m) { transform_ = Matrix(m); }

};