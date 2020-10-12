#include "Camera.h"
#include "Tuple.h"
#include "Material.h"
#include <cmath>

Camera::Camera(int hsize, int vsize, double fov) : hsize_{ hsize }, vsize_{ vsize }, fov_{ fov }, transform_{ Matrix(identity()) } {

	double halfView = tan(fov_/2);
	double aspect = hsize_ / static_cast<double>(vsize_);

	if (aspect < 1) {
		halfWidth = halfView * aspect;
		halfHeight = halfView;
	}
	else {
		halfWidth = halfView;
		halfHeight = halfView / aspect;
	}

	pixelSize_ = (halfWidth * 2) / hsize_;
}

Ray Camera::rayForPixel(int x, int y) const {
	
	double xOffset = (static_cast<double>(x) + 0.5) * pixelSize_;
	double yOffset = (static_cast<double>(y) + 0.5) * pixelSize_;

	double worldX = halfWidth - xOffset;
	double worldY = halfHeight - yOffset;

	Matrix t = transform_.inverse();

	Tuple pixel = t * point(worldX, worldY, -1);
	Tuple origin = t * point(0, 0, 0);
	Tuple direction = (pixel - origin).normalize();

	return Ray(origin, direction);
}

Canvas render(const Camera& c, const World& w) {
	Canvas image(c.hsize(), c.vsize());

	for (int y = 0; y < c.vsize(); y++) {
		for (int x = 0; x < c.hsize(); x++) {
			Ray r = c.rayForPixel(x, y);
			Color c = colorAt(w, r);
			image.writePixel(x, y, c);
		}
	}

	return image;
}