#pragma once

namespace MDesignPattern
{
	namespace MFactory
	{
		namespace
		{
			constexpr uint16_t FACTORY_MAX_PRODUCT = 1000;
		}

		template<typename T>
		class IFactory
		{
		public:
			virtual inline T GetFactory() const = 0;
		};

		template<typename T,typename Func = std::function<T*(void* const)>>
		class PlacementNewFactory : public IFactory<Func> 
		{
		private:
			Func _factory;

		protected:
			virtual inline T* CreateProduct(void* const targetAddress)
			{
				return new(targetAddress) T;
			}

		public:
			inline Func GetFactory() const override
			{
				return _factory;
			}

		public:
			PlacementNewFactory() : _factory(nullptr) { _factory = std::bind(&PlacementNewFactory::CreateProduct, this, std::placeholders::_1); }
			virtual ~PlacementNewFactory() {}
		};

		template<typename T,typename Func = std::function<T*()>>
		class CopyFactory : public IFactory<Func>
		{

		};

	} // namespace MFactory
} // namespace MDesignPattern
