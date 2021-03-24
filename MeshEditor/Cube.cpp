#include "Cube.h"
#include "Parser.h"

using std::map;
using std::string;

const string& Cube::getName() const {
	static string name = "Cube";
	return name;
}

int Cube::execute(const map<string, string>& args){
	string input_L;
	string input_origin;
	string input_filename;
	double l;

	map<string, string>::const_iterator it;
	it = args.find(string("L"));
	if (it != args.end()) input_L = it->second;
	else return 3;
	
	it = args.find(string("origin"));
	if (it != args.end()) input_origin = it->second;
	else return 3;
	
	it = args.find(string("filename"));
	if (it != args.end()) input_filename = it->second;
	else return 3;

	std::cout << "Cube:" << std::endl
		<< "\t l: " << input_L << std::endl
		<< "\t origin: " << input_origin << std::endl
		<< "\t filename: " << input_filename << std::endl;

	l = std::stod(input_L);
	if (l <= 0) return 1;

	input_origin.erase(0, 1);
	input_origin.pop_back();
	Vec origin = Vec(input_origin, ',');
	
	TriangleSoup ts;

	// bottom points
	Vec b1 = Vec(0,0,0);
	Vec b2 = Vec(l,0,0);
	Vec b3 = Vec(0,l,0);
	Vec b4 = Vec(l,l,0);

	// top points
	Vec t1 = Vec(0,0,l);
	Vec t2 = Vec(l,0,l);
	Vec t3 = Vec(0,l,l);
	Vec t4 = Vec(l,l,l);

	// bottom
	ts.add_triangle(b1, b4, b2);
	ts.add_triangle(b1, b4, b3);

	// top
	ts.add_triangle(t1, t4, t2);
	ts.add_triangle(t1, t4, t3);
	
	// left
	ts.add_triangle(b1, t2, t1);
	ts.add_triangle(b1, t2, b2);

	// right
	ts.add_triangle(b3, t4, b4);
	ts.add_triangle(b3, t4, t3);

	// front
	ts.add_triangle(b2, t4, t2);
	ts.add_triangle(b2, t4, b4);

	// back
	ts.add_triangle(b1, t3, t1);
	ts.add_triangle(b1, t3, b3);

	ts.offset(origin);

	STLParser parser;
	parser.write(ts, input_filename);

	return 0;
}
