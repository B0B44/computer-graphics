#pragma once
#include "Command.h"

class Cube : public Command
{
public:
	const std::string& getName() const override;
	int execute(const std::map<std::string, std::string>& args);
private:
	// TODO
};