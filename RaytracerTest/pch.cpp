//
// pch.cpp
// Include the standard header and generate the precompiled header.
//

#include "pch.h"

#include "../Raytracer/struct/Intersection.cpp"
#include "../Raytracer/struct/Matrix.cpp"
#include "../Raytracer/struct/Tuple.cpp"
#include "../Raytracer/struct/Util.cpp"
#include "../Raytracer/struct/Bounds.cpp"

#include "../Raytracer/world/Ray.cpp"
#include "../Raytracer/world/World.cpp"

#include "../Raytracer/render/Camera.cpp"
#include "../Raytracer/render/Canvas.cpp"

#include "../Raytracer/property/Color.cpp"
#include "../Raytracer/property/Material.cpp"
#include "../Raytracer/property/Pattern.cpp"

#include "../Raytracer/object/Object.cpp"
#include "../Raytracer/object/Sphere.cpp"
#include "../Raytracer/object/Plane.cpp"
#include "../Raytracer/object/Cube.cpp"
#include "../Raytracer/object/Cylinder.cpp"
#include "../Raytracer/object/Cone.cpp"
#include "../Raytracer/object/Group.cpp"

#include "../Raytracer/light/Light.cpp"
#include "../Raytracer/light/PointLight.cpp"