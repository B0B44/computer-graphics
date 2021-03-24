#include "Application.h"
#include "iostream"

void Application::registerCommand(std::unique_ptr<Command> command) {
	commands.insert(std::move(std::make_pair(command->getName(), std::move(command))));
}

int Application::execute(int argc, char *argv[]) {
	if (argc < 2) {
		return 3;
	}

	std::map<std::string, std::string> parameters;
	std::string name;
	std::string value;

	for(int i = 2; i+2 < argc; i+=3){		
		name = argv[i];
		value = argv[i+2];

		if (value.back() == ',')
			value.pop_back();
		parameters.insert(std::pair<std::string, std::string>(name, value));
		// std::cout << "Param " << (i-2)/3;
		// std::cout << " name \"" << name << "\"";
		// std::cout << " value \"" << value << "\"\n"; 
	}
	
	
	std::string command_name = argv[1];

	auto it = commands.find(command_name);
	if (it != commands.end()) {
		return it->second->execute(parameters);
	}
	else {
		return 6;
	}
}
