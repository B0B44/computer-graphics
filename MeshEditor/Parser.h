#pragma once
#include <vector>
#include <string>
#include <iostream>

struct Vec;
struct Vertex;

struct Vec
{
	double x, y, z;
	Vec();
	Vec(const std::string &input_string, const char delimiter);
	Vec(const double x_, const double y_, const double z_);
	double sum();
	double length() const;
	double dot(const Vec &that) const;
	const Vec operator +(const Vec &that) const;
	const Vec operator -(const Vec &that) const;
	const Vec operator *(const double &that) const;
	const Vec operator /(const double &that) const;
	const Vertex operator +(const Vertex &that) const;
	const Vertex operator -(const Vertex &that) const;
	friend std::ostream& operator<<(std::ostream &os, const Vec &vec);
};

std::ostream& operator <<(std::ostream &os, const Vec &vec);

struct Vertex
{
	Vec pos, normal;
	Vertex();
	Vertex(const Vec &pos_, const Vec &normal_);
	double length() const;
	const Vertex operator +(const Vec &that) const;
	const Vertex operator -(const Vec &that) const;
	friend std::ostream& operator<<(std::ostream &os, const Vertex &vertex);
};
std::ostream& operator<<(std::ostream &os, const Vertex &vertex);

struct TriangleSoup {
	std::vector<Vertex> ts;
	TriangleSoup(): ts() {};
	void offset(const Vec &vec);
	void add_triangle(const Vec &a, const Vec &b, const Vec &c);
};

class STLParser
{
public:
	TriangleSoup read(const std::string &filename);
	void write(const TriangleSoup &triangleSoup, const std::string &filename);
private:
	// TODO
};