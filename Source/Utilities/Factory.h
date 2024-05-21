#pragma once

namespace MUtil
{
	template<typename T>
	class Factory 
	{
	private:

		std::function<T*(void* const)> factory;

	protected:
		virtual inline T* CreateProduct(void* const targetAddress)
		{
			return new(targetAddress) T;
		}
	public:
		inline std::function<T*(void* const)> GetFactory() const
		{
			return factory;
		}

	public:
		Factory() : factory(nullptr) { factory = std::bind(&Factory::CreateProduct, this, std::placeholders::_1); }
		virtual ~Factory() {}
	};
}// namespace MUtil
