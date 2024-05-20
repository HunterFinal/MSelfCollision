#pragma once

namespace MUtil
{
	template<typename T>
	class Factory 
	{
	protected:
		virtual inline T* CreateProduct(T* const targetAddress)
		{
			return new(targetAddress) T;
		}
	public:
		static inline std::function<T*(T* const)> GetFactory()
		{
			return &CreateProduct;
		}

	public:
		virtual ~Factory() {}
	};
}// namespace MUtil
