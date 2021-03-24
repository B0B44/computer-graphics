#include <sstream>
#include <vector>
#include <memory>
#include "Application.h"

#include "Cube.h"
#include "Split.h"
#include "Sphere.h"



int main(int argc, char *argv[])
{
	Application app;

	app.registerCommand(std::make_unique<Cube>());
	app.registerCommand(std::make_unique<Split>());
	app.registerCommand(std::make_unique<Sphere>());

	return app.execute(argc, argv);
	return 0;
}