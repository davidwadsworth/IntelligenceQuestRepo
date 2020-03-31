#pragma once
#include "data_load.h"

namespace DataLoads
{
	class LController : public DataLoad
	{
	public:
		LController();
		~LController();

		void load(const char * path) override;
	};
}

