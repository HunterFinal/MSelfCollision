#pragma once

namespace MUtil
{
	template<typename T>
	class Factory 
	{
	public:
		T GetProduct() = 0;
	};
}
