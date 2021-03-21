#include "Parser.h"
#include <math.h>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>


static inline void trim(std::string &s) {
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {return !std::isspace(ch);}));
	s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {return !std::isspace(ch);}).base(), s.end());
}

Vec::Vec() : x(0.0), y(0.0), z(0.0) {}

Vec::Vec(double x_, double y_, double z_) : x(x_), y(y_), z(z_) {}

Vec::Vec(const std::string input_string, char delimiter){
	std::stringstream ss(input_string);
	std::vector<double> vect;
	std::string str;

	while (getline(ss, str, delimiter)) {
		vect.push_back(std::stod(str));
	}

	x = vect[0];
	y = vect[1];
	z = vect[2];
}

double Vec::sum() {
	return x + y + z;
}
double Vec::length() const {
	return sqrt(x*x + y*y + z*z);
}
double Vec::dot(const Vec &that) const {
	return x * that.x + y * that.y + z * that.z;
}

const Vec Vec::operator +(const Vec &that) const {
	return Vec(x + that.x, y + that.y, z + that.z);
}
const Vec Vec::operator -(const Vec &that) const {
	return Vec(x - that.x, y - that.y, z - that.z);
}
const Vec Vec::operator *(const double &that) const {
	return Vec(x * that, y * that, z * that);
}
const Vec Vec::operator /(const double &that) const {
	return Vec(x / that, y / that, z / that);
}

const Vec operator *(const double &num, const Vec vec) {
	return Vec(vec.x * num, vec.y * num, vec.z * num);
}
const Vec operator /(const double &num, const Vec vec) {
	return Vec(vec.x / num, vec.y / num, vec.z / num);
}


const Vertex Vec::operator +(const Vertex &that) const {
	return Vertex(that.pos + *this, that.normal + *this);
}
const Vertex Vec::operator -(const Vertex &that) const {
	return Vertex(that.pos - *this, that.normal - *this);
}


std::ostream& operator<<(std::ostream &os, const Vec &vec){
	auto old_precision = os.precision(20);
	os << vec.x << " " << vec.y << " " << vec.z;
	os.precision(old_precision);
	return os;
}


Vertex::Vertex() : pos(), normal() {}

Vertex::Vertex(Vec pos_, Vec normal_) : pos(pos_), normal(normal_) {}

std::ostream& operator<<(std::ostream &os, const Vertex &vertex){
	os << vertex.pos << " == > " << vertex.normal;
	return os;
}

double Vertex::length() const {
	const Vec len = pos - normal;
	return len.length();
}

const Vertex Vertex::operator +(const Vec &that) const {
	return Vertex(pos + that, normal + that);
}
const Vertex Vertex::operator -(const Vec &that) const {
	return Vertex(pos - that, normal - that);
}

void TriangleSoup::add_triangle(const Vec a, const Vec b, const Vec c) {
	const Vertex v1 = Vertex(a, b);
	const Vertex v2 = Vertex(b, c);
	const Vertex v3 = Vertex(c, a);

	if(v1.length() == 0) return;
	if(v2.length() == 0) return;
	if(v3.length() == 0) return;

	ts.push_back(v1);
	ts.push_back(v2);
	ts.push_back(v3);
}

void TriangleSoup::offset(const Vec vec) {
	for (long unsigned int i = 0; i < ts.size(); i++) {
		ts[i] = ts[i] + vec;
	}
}

TriangleSoup STLParser::read(const std::string& filename){
	TriangleSoup result;
	std::string line;
	std::ifstream myfile (filename);

	Vec normal;
	std::vector<Vec> facet;


	if (myfile.is_open()) {
		while ( getline (myfile, line) ) {
			trim(line);
			
			if (line.find("facet normal", 0) == 0){
				normal = Vec(line.erase(0, 13), ' ');
			} else if (line.find("vertex", 0) == 0){
				facet.push_back(Vec(line.erase(0, 7), ' '));
			} else if (line.find("endfacet", 0) == 0){
				if(facet.size() >= 3) {
					result.add_triangle(facet[0], facet[1], facet[2]);
				}
				facet.clear();
			}
		}
		myfile.close();
	} else {
		exit(5);
	}
	return result;
}

void STLParser::write(const TriangleSoup& triangleSoup, const std::string& filename) {
	std::ofstream myfile (filename, std::ofstream::out);
	
	if (myfile.is_open()) {
		myfile << "solid model" << std::endl;
		for (long unsigned int i = 0; i + 2 < triangleSoup.ts.size(); i+=3) {
			Vec a = triangleSoup.ts[i + 0].pos;
			Vec b = triangleSoup.ts[i + 1].pos;
			Vec c = triangleSoup.ts[i + 2].pos;

			Vec u = b - a;
			Vec v = c - a;
			Vec normal(
				u.y * v.z - u.z * v.y,
				u.z * v.x - u.x * v.z,
				u.x * v.y - u.y * v.x);

			normal = normal / normal.length();

			myfile << "  facet normal " << normal << std::endl;
			myfile << "    outer loop" << std::endl;
			myfile << "      vertex " << a << std::endl;
			myfile << "      vertex " << b << std::endl;
			myfile << "      vertex " << c << std::endl;
			myfile << "    endloop" << std::endl;
			myfile << "  endfacet" << std::endl;
		}
		myfile << "endsolid model" << std::endl;
		myfile.close();
	} else {
		exit(5);
	}
}