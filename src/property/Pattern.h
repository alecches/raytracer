#pragma once
#include "../property/Color.h"
#include "../struct/Tuple.h"
#include "../struct/Matrix.h"
class Object;

class Pattern {
protected:
	Color a_;
	Color b_;
	Matrix transform_;
public:

	Pattern(Color c1, Color c2) : a_{ c1 }, b_{ c2 }, transform_{ identity() } {}
	Pattern(const Pattern& p) : a_{ p.a() }, b_{ p.b() }, transform_{ p.transform() } {}

	Color a() const { return a_; }
	Color b() const { return b_; }
	Matrix transform() const { return transform_; }
	void transform(const Matrix& m) { transform_ = Matrix(m); }

	Color colorAtObject(const Tuple&, const Object&) const;
	virtual Color colorAt(const Tuple&) const = 0;
	virtual Pattern* heapPattern() const = 0;

	virtual ~Pattern() {}
};

class testPattern : public Pattern {

public:
	testPattern() : Pattern(Color(0,0,0), Color(1,1,1)) {}
	testPattern(const testPattern& p) : Pattern(p) {}
	Pattern* heapPattern() const { return new testPattern(*this); }

	Color colorAt(const Tuple& p) const { return Color(p.x, p.y, p.z); }
};

class stripePattern : public Pattern {

public:
	stripePattern(Color c1, Color c2) : Pattern(c1, c2) {}
	stripePattern(const stripePattern& p) : Pattern(p) {}
	Pattern* heapPattern() const { return new stripePattern(*this); }

	Color colorAt(const Tuple&) const;
	
};

class gradientPattern : public Pattern {

public:
	gradientPattern(Color c1, Color c2) : Pattern(c1, c2) {}
	gradientPattern(const gradientPattern& p) : Pattern(p) {}
	Pattern* heapPattern() const { return new gradientPattern(*this); }

	Color colorAt(const Tuple&) const;

};

class ringPattern : public Pattern {
public:
	ringPattern(Color c1, Color c2) : Pattern(c1, c2) {}
	ringPattern(const ringPattern& p) : Pattern(p) {}
	Pattern* heapPattern() const { return new ringPattern(*this); }

	Color colorAt(const Tuple&) const;
};

class checkerPattern : public Pattern {
public:
	checkerPattern(Color c1, Color c2) : Pattern(c1, c2) {}
	checkerPattern(const checkerPattern& p) : Pattern(p) {}
	Pattern* heapPattern() const { return new checkerPattern(*this); }

	Color colorAt(const Tuple&) const;
};