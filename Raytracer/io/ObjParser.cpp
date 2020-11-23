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
			SmoothTriangle tri(vertices_[verts[i] - 1], vertices_[verts[i + 1] - 1], vertices_[verts[i + 2] - 1],
				normals_[norms[i] - 1], normals_[norms[i + 1] - 1], normals_[norms[i + 2] - 1]);
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

void ObjParser::parse(std::string path) {

	std::ifstream ifs(path);
	if (!ifs) std::cerr << "Unable to open file: " << path << "\n";

	std::regex pattern(R"~(f((\s+\d+){3,}|(\s+\d+/\d+/\d+){3,}|(\s+\d+//\d+){3,})|(v|vn)(\s+\-?\d+\.?\d*){3}|g\s+\w+)~", 
		std::regex_constants::ECMAScript);

	std::string line;
	groups_.push_back(std::pair<std::string, Group>("DefaultGroup", Group()));
	int currentGroup = 0;
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

}

Group ObjParser::objToGroup() const {
	if (groups_.size() == 1) return groups_[0].second;
	Group all;
	for (int i = 0; i < groups_.size(); i++) {
		if (groups_[i].second.children().size() > 0) all.addChild(groups_[i].second);
	}
	return all;
}