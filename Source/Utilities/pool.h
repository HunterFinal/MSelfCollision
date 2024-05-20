#pragma once

#include "ring_buffer.h"

#include <functional>

#ifndef SAVE_RELEASE
#include "memory_release_def.h"
#endif // !SAVE_RELEASE


namespace MUtil
{
	// IPool (interface)
	template <typename obj>
	class IPool
	{
	public:
		virtual inline obj& Allocate() const = 0;
		virtual inline void Recycle(const obj& recycleObj) = 0;
		virtual inline void InitPool(std::function<obj*(obj* const targetAddress)> factory) = 0;
	public:
		virtual ~IPool() {}
	};
	// End IPool

	/// @brief Pool
	/// @tparam T type
	template<typename T>
	class Pool : public IPool<T>
	{

	// copy and move disable
	private:
		Pool(const Pool& rhs) = delete;
		Pool& operator = (const Pool& rhs) = delete;
		Pool(const Pool&& rhs) = delete;
		Pool& operator = (const Pool&& rhs) = delete;

	// interface implements
	public:
		inline T& Allocate() const override;
		inline void Recycle(const T& recycleObj) override;
		inline void InitPool(std::function<T* (T* const targetAddress)> factory) override;
	// IPool

	// constructor/destructor
	public:
		explicit Pool(int size) 
			: _pPool(nullptr)
			, _poolSize(size)
		{
			_pPool = new RingBuffer<T>();
			//#ifdef DEBUG
			//	std::cout << "Create pool" << std::endl;
			//#endif // DEBUG
		}
		virtual ~Pool()
		{
			SAVE_DELETE(_pPool)
			#ifdef DEBUG
				std::cout << "Delete pool" << std::endl;
			#endif // DEBUG
		}

	// Method
	private:

	// Protected property
	protected:
		RingBuffer<T> *_pPool;
		int _poolSize;
	// 
	};
	// End Pool  

	/// @brief allocate obj 
	/// @tparam T type
	/// @return ref of allocated obj
	template <typename T>
	inline T& Pool<T>::Allocate() const
	{
		T obj;
		if (_pPool != nullptr)
		{
			_pPool->Dequeue(obj);

		}
		return obj;
	}

	/// @brief recycle obj 
	/// @tparam T type
	/// @param recycleObj 
	template <typename T>
	inline void Pool<T>::Recycle(const T& recycleObj)
	{
		if (_pPool != nullptr)
		{
			_pPool->Enqueue(recycleObj);
		}
	}

	/// @brief Pool initialize
	/// @tparam T type
	template<typename T>
	inline void Pool<T>::InitPool(std::function<T* (T* const targetAddress)> factory)
	{
		// vessel initialize
		_pPool->Init(_poolSize);
		_poolSize = _pPool->Capacity();
		// create obj in advance
		for (int i = 0; i < _poolSize; ++i)
		{
			auto obj = factory(_pPool->GetHeadAddress() + i);

			std::cout << obj << std::endl;
		}
	}
}// namespace MUtil
