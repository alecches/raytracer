//
// pch.h
// Header for standard system include files.
//

#pragma once

#include "gtest/gtest.h"

// all header files from Raytracer...

#include "../Raytracer/struct/Intersection.h"
#include "../Raytracer/struct/Matrix.h"
#include "../Raytracer/struct/Tuple.h"
#include "../Raytracer/struct/Util.h"
#include "../Raytracer/struct/Bounds.h"

#include "../Raytracer/world/Ray.h"
#include "../Raytracer/world/World.h"

#include "../Raytracer/render/Camera.h"
#include "../Raytracer/render/Canvas.h"

#include "../Raytracer/property/Color.h"
#include "../Raytracer/property/Material.h"
#include "../Raytracer/property/Pattern.h"

#include "../Raytracer/object/Object.h"
#include "../Raytracer/object/Sphere.h"
#include "../Raytracer/object/Plane.h"
#include "../Raytracer/object/Cube.h"
#include "../Raytracer/object/Cylinder.h"
#include "../Raytracer/object/Cone.h"
#include "../Raytracer/object/Group.h"
#include "../Raytracer/object/Triangle.h"
#include "../Raytracer/object/SmoothTriangle.h"
#include "../Raytracer/object/CSG.h"

#include "../Raytracer/light/Light.h"
#include "../Raytracer/light/PointLight.h"

#include "../Raytracer/io/ObjParser.h"