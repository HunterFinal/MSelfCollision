#pragma once

namespace MUtil
{
	namespace
	{
		constexpr uint16_t FACTORY_MAX_PRODUCT = 1000;
	}
	template<typename T>
	class IFactory
	{
		public:

	};

	template<typename T>
	class Factory 
	{
	private:
		std::function<T*(void* const)> _factory;
		std::vector<T*> _needReleasePointers;

	protected:
		virtual inline T* CreateProduct(void* const targetAddress)
		{
			return new(targetAddress) T;
		}
		/// @brief Create product by new(if delete,please set it to nullptr)
		/// @return T*
		virtual inline T* CreateCopyProduct()
		{
			if(_needReleasePointers.size() >= FACTORY_MAX_PRODUCT)
				return nullptr;
				
			T* product = new T();
			_needReleasePointers.push_back(product);
			return product;
		}
	public:
		inline std::function<T*(void* const)> GetFactory() const
		{
			return _factory;
		}

	public:
		Factory() : _factory(nullptr),_needReleasePointers({}) { _factory = std::bind(&Factory::CreateProduct, this, std::placeholders::_1); }
		virtual ~Factory() 
		{
			for(auto it = _needReleasePointers.begin(); it != _needReleasePointers.end(); ++it)
			{
				if(*it != nullptr)
				{
					SAVE_DELETE(*it);
				}
			}
			_needReleasePointers.clear();
		}
	};
}// namespace MUtil
