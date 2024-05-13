#pragma once

#include "ring_buffer.h"

#ifndef SAVE_RELEASE
#include "memory_release_def.h"
#endif // !SAVE_RELEASE


namespace MUtil
{
	template <typename obj>
	class IPool
	{
	public:
		virtual obj& Allocate() const = 0;
		virtual void Recycle(const obj& recycleObj) = 0;
	};

	template<typename T>
	class Pool : public IPool<T>
	{
	public:
		T& Allocate() const override;
		void Recycle(const T& recycleObj) override;

	public:
		explicit Pool(int size) 
			: _pPool(nullptr)
			, _poolSize(size)
		{
			_pPool = new RingBuffer<T>();
			InitPool();
			//#ifdef DEBUG
			//	std::cout << "Create pool" << std::endl;
			//#endif // DEBUG

		}
		virtual ~Pool()
		{
			SAVE_DELETE(_pPool)
			//#ifdef DEBUG
			//	std::cout << "Delete pool" << std::endl;
			//#endif // DEBUG
		}
	private:
		void InitPool();

	protected:
		RingBuffer<T> *_pPool;
		int _poolSize;
	};

	template <typename T>
	T& Pool<T>::Allocate() const
	{
		T obj;
		if (_pPool != nullptr)
		{
			_pPool->Pop(obj);

		}
		return obj;
	}

	template <typename T>
	void Pool<T>::Recycle(const T& recycleObj)
	{
		if (_pPool != nullptr)
		{
			_pPool->Push(recycleObj);
		}
	}

	template<typename T>
	void Pool<T>::InitPool()
	{
		_pPool->Init(_poolSize);
		_poolSize = _pPool->Capacity();
		for (int i = 0; i < _poolSize; ++i)
		{
			T obj;
			_pPool->Push(obj);
		}
	}
}// namespace MUtil
