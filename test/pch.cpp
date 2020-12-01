//
// pch.cpp
// Include the standard header and generate the precompiled header.
//

#include "pch.h"

#include "../src/struct/Intersection.cpp"
#include "../src/struct/Matrix.cpp"
#include "../src/struct/Tuple.cpp"
#include "../src/struct/Util.cpp"
#include "../src/struct/Bounds.cpp"

#include "../src/world/Ray.cpp"
#include "../src/world/World.cpp"

#include "../src/render/Camera.cpp"
#include "../src/render/Canvas.cpp"

#include "../src/property/Color.cpp"
#include "../src/property/Material.cpp"
#include "../src/property/Pattern.cpp"

#include "../src/object/Object.cpp"
#include "../src/object/Sphere.cpp"
#include "../src/object/Plane.cpp"
#include "../src/object/Cube.cpp"
#include "../src/object/Cylinder.cpp"
#include "../src/object/Cone.cpp"
#include "../src/object/Group.cpp"
#include "../src/object/Triangle.cpp"
#include "../src/object/SmoothTriangle.cpp"
#include "../src/object/CSG.cpp"

#include "../src/light/Light.cpp"
#include "../src/light/PointLight.cpp"

#include "../src/io/ObjParser.cpp"