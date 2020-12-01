//
// pch.h
// Header for standard system include files.
//

#pragma once

#include "gtest/gtest.h"

// all header files from Raytracer...

#include "../src/struct/Intersection.h"
#include "../src/struct/Matrix.h"
#include "../src/struct/Tuple.h"
#include "../src/struct/Util.h"
#include "../src/struct/Bounds.h"

#include "../src/world/Ray.h"
#include "../src/world/World.h"

#include "../src/render/Camera.h"
#include "../src/render/Canvas.h"

#include "../src/property/Color.h"
#include "../src/property/Material.h"
#include "../src/property/Pattern.h"

#include "../src/object/Object.h"
#include "../src/object/Sphere.h"
#include "../src/object/Plane.h"
#include "../src/object/Cube.h"
#include "../src/object/Cylinder.h"
#include "../src/object/Cone.h"
#include "../src/object/Group.h"
#include "../src/object/Triangle.h"
#include "../src/object/SmoothTriangle.h"
#include "../src/object/CSG.h"

#include "../src/light/Light.h"
#include "../src/light/PointLight.h"

#include "../src/io/ObjParser.h"