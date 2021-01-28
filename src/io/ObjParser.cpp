#include "ObjParser.h"
#include <regex>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

void ObjParser::fanTriangulate(bool smooth, int group, std::vector<std::string>& face) {

	if (!smooth) {
		for (int i = 2; i < face.size() - 1; i++) {
			Triangle tri(vertices_[stoi(face[1]) - 1], vertices_[stoi(face[i]) - 1], vertices_[stoi(face[i + 1]) - 1]);
			faces_.push_back(tri);
			groups_[group].second.addChild(tri);
		}
	}
	else {
		std::vector<int> verts;
		std::vector<int> norms;

		for (int i = 1; i < face.size(); i++) {
			int len = face[i].size();
			int firstSlash = face[i].find("/");
			verts.push_back(stoi(face[i].substr(0, firstSlash)));
			int lastSlash = face[i].rfind("/");
			norms.push_back(stoi(face[i].substr(lastSlash + 1, len - lastSlash - 1)));
		}

		for (int i = 0; i < verts.size() - 2; i++) {
			SmoothTriangle tri(vertices_[verts[0] - 1], vertices_[verts[i + 1] - 1], vertices_[verts[i + 2] - 1],
				normals_[norms[0] - 1], normals_[norms[i + 1] - 1], normals_[norms[i + 2] - 1]);
			smoothFaces_.push_back(tri);
			groups_[group].second.addChild(tri);
		}
	}
}

void ObjParser::parseFace(int group, std::vector<std::string>& s) {

	if (s[1].find("/") != std::string::npos) fanTriangulate(true, group, s);
	else fanTriangulate(false, group, s);
	return;

}

bool containsPoint(const Tuple& point, const Bounds& bounds) {

	Tuple bMin = bounds.min;
	Tuple bMax = bounds.max;

	if (point.x < bMin.x) return false;
	if (point.x > bMax.x) return false;
	if (point.y < bMin.y) return false;
	if (point.y > bMax.y) return false;
	if (point.z < bMin.z) return false;
	if (point.z > bMax.z) return false;
	
	return true;
	
}

void ObjParser::parse(std::string path) {

	std::ifstream ifs(path);
	if (!ifs) std::cerr << "Unable to open file: " << path << "\n";

	std::regex pattern(R"~(f((\s+\d+){3,}\s*|(\s+\d+/\d+/\d+){3,}\s*|(\s+\d+//\d+){3,}\s*)|(v|vn)(\s+\-?\d+\.?\d*\e?\-?\d*){3}\s*|g\s+\w+\s*)~", 
		std::regex_constants::ECMAScript);

	std::string line;

	groups_.push_back(std::pair<std::string, Group>("DefaultGroup", Group()));
	int currentGroup = 0;

	Tuple min, max;

	while (std::getline(ifs, line)) {

		if (std::regex_match(line, pattern)) {

			std::vector<std::string> words;
			std::istringstream stringStream(line);
			std::copy(std::istream_iterator<std::string>(stringStream),
				std::istream_iterator<std::string>(),
				std::back_inserter(words));

			if (words[0] == "v") {
				Tuple vert = point(stod(words[1]), stod(words[2]), stod(words[3]));
				vertices_.push_back(vert);

				// manage the overall bounding box
				if (vert.x < min.x) min.x = vert.x;
				else if (vert.x > max.x) max.x = vert.x;
				if (vert.y < min.y) min.y = vert.y;
				else if (vert.y > max.y) max.y = vert.y;
				if (vert.z < min.z) min.z = vert.z;
				else if (vert.z > max.z) max.z = vert.z;

			}
			else if (words[0] == "vn") {
				Tuple norm = vec(stod(words[1]), stod(words[2]), stod(words[3]));
				normals_.push_back(norm);
			}
			else if (words[0] == "f") {
				parseFace(currentGroup, words);
			}
			else if (words[0] == "g") {
				groups_.push_back(std::pair<std::string, Group>(words[1], Group()));
				currentGroup++;
			}
		}
		else ignoredLines_++;

	}

	// bounding boxes allocation
	if (bounded_) {

		// by default we will cut up the box into eighths
		int xCuts = 4;
		int yCuts = 2;
		int zCuts = 0;

		Tuple diagonal = max - min;
		/*
		Tuple center = diagonal * 0.5 + min;
		Tuple diagonalX = vec(diagonal.x, 0, 0);
		Tuple diagonalY = vec(0, diagonal.y, 0);
		Tuple diagonalZ = vec(0, 0, diagonal.z);
		*/
		std::vector<Group> potentialGroups;

		for (int x = 0; x <= xCuts; x++){
			double xMin = min.x + diagonal.x * ((1.0 / (xCuts + 1)) * x);
			double xMax = min.x + diagonal.x * ((1.0 / (xCuts + 1)) * (x + 1));

			for (int y = 0; y <= yCuts; y++) {
				double yMin = min.y + diagonal.y * ((1.0 / (yCuts + 1)) * y);
				double yMax = min.y + diagonal.y * ((1.0 / (yCuts + 1)) * (y + 1));

				for (int z = 0; z <= zCuts; z++) {
					double zMin = min.z + diagonal.z * ((1.0 / (zCuts + 1)) * z);
					double zMax = min.z + diagonal.z * ((1.0 / (zCuts + 1)) * (z + 1));

					Group g;
					Tuple groupMin = point(xMin, yMin, zMin);
					Tuple groupMax = point(xMax, yMax, zMax);
					g.boundingBox(Bounds(groupMin, groupMax));
					g.setBounds(); // could consolidate with boundingBox(box)

					potentialGroups.push_back(g);
				}
			}
		}

		for (auto tri : smoothFaces_) {

			for (auto& grp : potentialGroups) {

				Bounds grpBox = grp.boundingBox();
	
				if (containsPoint(tri.p1(), grpBox)) grp.addChild(tri);
				else if (containsPoint(tri.p2(), grpBox)) grp.addChild(tri);
				else if (containsPoint(tri.p3(), grpBox)) grp.addChild(tri);
				// for now, triangles can be members of multiple boxes, to assure no intersections are missed
			}
		}

		for (auto tri : faces_) {

			for (auto grp : potentialGroups) {

				Bounds grpBox = grp.boundingBox();

				if (containsPoint(tri.p1(), grpBox)) grp.addChild(tri);
				else if (containsPoint(tri.p2(), grpBox)) grp.addChild(tri);
				else if (containsPoint(tri.p3(), grpBox)) grp.addChild(tri);
				// for now, triangles can be members of multiple boxes, to assure no intersections are missed
				// this may cause duplicates...
			}
		}

		for (auto grp : potentialGroups) {
			if (grp.children().size() > 0) boundedGroups_.push_back(grp);
		}
		
	}

	ifs.close();

}

Group ObjParser::objToGroup() const {
	if (groups_.size() == 1) return groups_[0].second;
	Group all;
	for (int i = 0; i < groups_.size(); i++) {
		if (groups_[i].second.children().size() > 0) all.addChild(groups_[i].second);
	}
	return all;
}