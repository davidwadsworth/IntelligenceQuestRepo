#pragma once

namespace UpdateSystems
{
	class Animation : public System
	{
	public:
		Animation();
		~Animation();

		void update() override;
	};
}
