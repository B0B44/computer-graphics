#include "Sphere.h"
#include <math.h>
#include "Parser.h"

using std::map;
using std::string;

const string& Sphere::getName() const {
	static string name = "Sphere";
	return name;
}

int Sphere::execute(const map<string, string>& args){
	string input_R;
	string input_origin;
	string input_filename;
	double r;

	map<string, string>::const_iterator it;
	it = args.find(string("R"));
	if (it != args.end()) input_R = it->second;
	else return 3;
	
	it = args.find(string("origin"));
	if (it != args.end()) input_origin = it->second;
	else return 3;
	
	it = args.find(string("filename"));
	if (it != args.end()) input_filename = it->second;
	else return 3;


	std::cout << "Input:" << std::endl
		<< "\t r: " << input_R << std::endl
		<< "\t origin: " << input_origin << std::endl
		<< "\t filename: " << input_filename << std::endl;

	r = std::stod(input_R);
	if (r <= 0) return 1;

	input_origin.erase(0, 1);
	input_origin.pop_back();
	Vec origin = Vec(input_origin, ',');
	
	TriangleSoup ts;
	TriangleSoup new_ts;

	// generating tetraeder with center at 0, 0, 0
	double n =  r / sqrt(3);
	Vec a = Vec(-n, -n, -n);
	Vec b = Vec( n,  n, -n);
	Vec c = Vec(-n,  n,  n);
	Vec d = Vec( n, -n,  n);
	
	ts.add_triangle(a, b, c);
	ts.add_triangle(a, b, d);
	ts.add_triangle(b, c, d);
	ts.add_triangle(a, c, d);

	double acc_len = r/5;

	while (1){
		bool clean = true;
		for (long unsigned int i = 0; i + 2 < ts.ts.size(); i += 3){
			Vec a = ts.ts[i + 0].pos;
			Vec b = ts.ts[i + 1].pos;
			Vec c = ts.ts[i + 2].pos;
			
			int long_i = i;
			if (ts.ts[long_i].length() < ts.ts[i + 1].length()) long_i = i + 1;
			if (ts.ts[long_i].length() < ts.ts[i + 2].length()) long_i = i + 2;

			if (ts.ts[long_i].length() > acc_len){
				Vec p1, p2, p3, m;
				switch (long_i % 3) {
					case 0:
						p1 = a;
						p2 = b;
						p3 = c;
						break;
					case 1:
						p1 = b;
						p2 = c;
						p3 = a;
						break;
					case 2:
						p1 = a;
						p2 = c;
						p3 = b;
						m = (c + a) / 2;
						break;
				}
				m = (p1 + p2) / 2;
				m = m * r / m.length();

				new_ts.add_triangle( p1, p3, m);
				new_ts.add_triangle( p2, p3, m);						

				clean = false;
			} else {
				new_ts.add_triangle( a, b, c);
			}
		}
		ts = new_ts;
		new_ts.ts.clear();
		if (clean) break;
	}

	ts.offset(origin);
	STLParser parser;
	parser.write(ts, input_filename);

	return 0;
}
