#pragma once
#include "ECS.h"

class Command
{
public:
	bool is_terminated = false;
	virtual ~Command() = default;
	virtual void execute() = 0;
	virtual void undo() {}
};

