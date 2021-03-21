#include "Split.h"
#include "Parser.h"

using std::map;
using std::string;

const string& Split::getName() const {
	static string name = "Split";
	return name;
}

int Split::execute(const map<string, string>& args){
	
	string input_input;
	string input_origin;
	string input_direction;
	string input_output1;
	string input_output2;

	map<string, string>::const_iterator it;
	it = args.find(string("input"));
	if (it != args.end()) input_input = it->second;
	else return 3;
	
	it = args.find(string("origin"));
	if (it != args.end()) input_origin = it->second;
	else return 4;
	
	it = args.find(string("direction"));
	if (it != args.end()) input_direction = it->second;
	else return 5;
	
	it = args.find(string("output1"));
	if (it != args.end()) input_output1 = it->second;
	else return 6;
	
	it = args.find(string("output2"));
	if (it != args.end()) input_output2 = it->second;
	else return 7;

	std::cout << "Input:" << std::endl
		<< "\t origin:    " << input_origin    << std::endl
		<< "\t direction: " << input_direction << std::endl
		<< "\t input:     " << input_input     << std::endl
		<< "\t output1:   " << input_output1   << std::endl
		<< "\t output2:   " << input_output2   << std::endl;

	input_origin.erase(0, 1);
	input_origin.pop_back();
	Vec plane_origin = Vec(input_origin, ',');

	input_direction.erase(0, 1);
	input_direction.pop_back();
	Vec plane_normal = Vec(input_direction, ',');
	
	STLParser parser;
	TriangleSoup ts = parser.read(input_input);

	TriangleSoup ts_1;
	TriangleSoup ts_2;

	for (long unsigned int i = 0; i < ts.ts.size() + 2; i += 3){
		const Vec& a = ts.ts[i + 0].pos;
		const Vec& b = ts.ts[i + 1].pos;
		const Vec& c = ts.ts[i + 2].pos;

		std::vector<Vec> side_1;
		std::vector<Vec> side_2;

		// later I`ll assign "big" to index representing bigger side
		TriangleSoup     *ts_arr[2]   = {  &ts_1,   &ts_2};
		std::vector<Vec> *side_arr[2] = {&side_1, &side_2};

		((a - plane_origin).dot(plane_normal) <= 0) 
			? side_1.push_back(a) 
			: side_2.push_back(a);
		((b - plane_origin).dot(plane_normal) <= 0)
			? side_1.push_back(b)
			: side_2.push_back(b);
		((c - plane_origin).dot(plane_normal) <= 0)
			? side_1.push_back(c)
			: side_2.push_back(c);

		const int big = (side_1.size() > side_2.size()) ? 0 : 1;
		const int small = (big) ? 0 : 1;

		if (side_arr[big]->size() == 3){
			ts_arr[big]->add_triangle(a, b, c);
		} else {
			//point 1 and 2 are on the same side of the plane,
			// point 3 is on the other side of the plane
			Vec point_1 = (*side_arr[big])[0];
			Vec point_2 = (*side_arr[big])[1];
			Vec point_3 = (*side_arr[small])[0];
			
			// dirr_1 and dirr_2 are dirrections from point 1 and 2 to point 3
			Vec dirr_1 =  point_1 - point_3;
			Vec dirr_2 =  point_2 - point_3;
			
			// finding intersection points of triangle sides and plane
			// this formula was extracted from https://rosettacode.org/wiki/Find_the_intersection_of_a_line_with_a_plane#C.2B.2B
			Vec intersection_1 = point_1 - dirr_1 * (point_1 - plane_origin).dot(plane_normal) / dirr_1.dot(plane_normal);
			Vec intersection_2 = point_2 - dirr_2 * (point_2 - plane_origin).dot(plane_normal) / dirr_2.dot(plane_normal);

			ts_arr[big]->add_triangle(point_1, point_2, intersection_2);
			ts_arr[big]->add_triangle(point_1, intersection_1, intersection_2);
			ts_arr[small]->add_triangle(point_3, intersection_1, intersection_2);
		}
	}
	parser.write(ts_1, input_output1);
	parser.write(ts_2, input_output2);

	return 0;
}
