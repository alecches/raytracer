#pragma once
#include "../object/Triangle.h"
#include "../object/SmoothTriangle.h"
#include "../object/Group.h"
#include <string>


class ObjParser
{
private:
	std::vector<std::pair<std::string, Group>> groups_;
	std::vector<Tuple> vertices_;
	std::vector<Tuple> normals_;
	std::vector<Triangle> faces_;
	std::vector<SmoothTriangle> smoothFaces_;
	int ignoredLines_;

	void parseFace(int, std::vector<std::string>&);
	void fanTriangulate(bool, int, std::vector<std::string>&);

public:

	ObjParser() : ignoredLines_{ 0 }, vertices_{ std::vector<Tuple>() }, faces_{ std::vector<Triangle>() }, 
		groups_{ std::vector<std::pair<std::string, Group>>() } {}

	Group objToGroup() const;
	void parse(std::string);
	int ignoredLines() const { return ignoredLines_; }
	const std::vector<Tuple>& vertices() const { return vertices_; }
	const std::vector<Tuple>& normals() const { return normals_; }
	const std::vector<Triangle>& faces() const { return faces_; }
	const std::vector<SmoothTriangle>& smoothFaces() const { return smoothFaces_; }
	const std::vector<std::pair<std::string, Group>>& groups() const { return groups_; }
	//void addVertex(Tuple t) { vertices_.push_back(t); }
	//void addTriangle(Triangle t) { faces_.push_back(t); }
	
};

