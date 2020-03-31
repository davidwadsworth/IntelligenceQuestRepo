#pragma once

class DataLoad
{
public:
	virtual ~DataLoad() = default;
	virtual void load(const char * path) = 0;
};
