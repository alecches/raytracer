#pragma once
#include "Matrix.h"
#include "Canvas.h"

class Camera
{
private:
	int hsize_;
	int vsize_;
	double fov_;
	Matrix transform_;
	double halfHeight;
	double halfWidth;
	double pixelSize_;
public:
	Camera(int hsize, int vsize, double fov);
	int hsize() const { return hsize_; }
	int vsize() const { return vsize_; }
	double fov() const { return fov_; }
	Matrix transform() const { return transform_; }
	void transform(Matrix m) { transform_ = m; }
	double pixelSize() const { return pixelSize_; }

	Ray rayForPixel(int, int) const;
};

Canvas render(const Camera&, const World&);

