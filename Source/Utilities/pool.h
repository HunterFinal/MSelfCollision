#pragma once

#include <functional>
#include <mutex>

#include "ring_buffer.h"

#ifndef SAVE_RELEASE
#include "memory_release_def.h"
#endif // !SAVE_RELEASE

namespace MUtil
{

	// IPoolインターフェース
	template <typename obj>
	class IPool
	{
	public:
		virtual inline void Allocate(obj& allocateObj) const = 0;
		virtual inline void Recycle(const obj& recycleObj) = 0;
		virtual inline void InitPool(std::function<obj*(void* const targetAddress)> factory) = 0;
		//virtual inline obj* const GetBufferHeadAddress() const = 0;
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
		inline void Allocate(T& allocateObj) const override;
		inline void Recycle(const T& recycleObj) override;
		inline void InitPool(std::function<T* (void* const targetAddress)> factory) override;
		//inline T* const GetBufferHeadAddress() const override;

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
	inline void Pool<T>::Allocate(T& allocateObj) const
	{
		if (_pPool != nullptr)
		{
			_pPool->Dequeue(allocateObj);
		}
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
	inline void Pool<T>::InitPool(std::function<T* (void* const targetAddress)> factory)
	{
		// vessel initialize
		if(_pPool->Init(_poolSize))
		{
			_poolSize = _pPool->GetCapacity();
			// create obj in advance
			for (int i = 0; i < _poolSize; ++i)
			{
				auto obj = factory(_pPool->GetHeadAddress() + i);

				//#ifdef DEBUG
				//	std::cout << obj << std::endl;
				//#endif
			}

		}

	}

/*
	template <typename T>
	inline T* const Pool<T>::GetBufferHeadAddress() const
	{
		if (_pPool == nullptr)
		{
			return nullptr;
		}

		return _pPool->GetHeadAddress();

	}
*/
}// namespace MUtil
