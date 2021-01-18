#srcdir = src/
# CPPFLAGS = -lstdc++
CC = g++

objects = main.o io/ObjParser.o light/Light.o light/PointLight.o \
		object/Cone.o object/CSG.o object/Cube.o \
		object/Cylinder.o object/Group.o object/Object.o \
		object/Plane.o object/SmoothTriangle.o \
		object/Sphere.o object/Triangle.o \
		property/Color.o property/Material.o property/Pattern.o \
		render/Camera.o render/Canvas.o \
		struct/Bounds.o struct/Intersection.o struct/Matrix.o \
		struct/Tuple.o struct/Util.o \
		world/Ray.o world/World.o

raytracer : $(objects)
	g++ -o raytracer $(objects)

main.o : io/ObjParser.h light/Light.h light/PointLight.h \
		object/Cone.h object/CSG.h object/Cube.h \
		object/Cylinder.h object/Group.h object/Object.h \
		object/Plane.h object/SmoothTriangle.h object/Sphere.h \
		object/Triangle.h \
		property/Color.h property/Material.h property/Pattern.h \
		render/Camera.h render/Canvas.h \
		struct/Bounds.h struct/Intersection.h struct/Matrix.h \
		struct/Tuple.h struct/Util.h \
		world/Ray.h world/World.h
ObjParser.o : io/ObjParser.h
Light.o : light/Light.h
PointLight.o : light/PointLight.h
Cone.o : object/Cone.h
CSG.o : object/CSG.h
Cube.o : object/Cube.h
Cylinder.o : object/Cylinder.h
Group.o : object/Group.h
Object.o : object/Object.h
Plane.o : object/Plane.h
SmoothTriangle.o : object/SmoothTriangle.h
Sphere.o : object/Sphere.h
Triangle.o : object/Triangle.h
Color.o : property/Color.h
Material.o : property/Material.h
Pattern.o : property/Pattern.h
Camera.o : render/Camera.h
Canvas.o : render/Canvas.h
Bounds.o : struct/Bounds.h
Intersection.o : struct/Intersection.h
Matrix.o : struct/Matrix.h
Tuple.o : struct/Tuple.h
Util.o : struct/Util.h
Ray.o : world/Ray.h
World.o : world/World.h

clean:
	rm raytracer $(objects)
