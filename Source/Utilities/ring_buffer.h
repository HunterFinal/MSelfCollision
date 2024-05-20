#pragma once
#include <cstdint>
#include <iostream>

#ifndef SAVE_RELEASE
#include "memory_release_def.h"
#endif // !SAVE_RELEASE

#define DEBUG

namespace MUtil
{
	namespace
	{
		constexpr uint16_t RING_BUFFER_MAX_SIZE = 1000;
		constexpr uint16_t RING_BUFFER_DEFAULT_SIZE = 10;

		template<typename T>
		class IFIFO
		{

		public:
			virtual void Enqueue(const T& pushInstance) = 0;
			virtual void Dequeue(T& popInstance) = 0;
		};
	}// unnamed namespace

	/// @brief ring buffer
	/// @tparam T type store in ring buffer
	template <typename T>
	class RingBuffer:public IFIFO<T>
	{

		// constructor and destructor
		public:
			RingBuffer();
			~RingBuffer();

		// initialize
		public:
			void Init(int size);

		// data manipulation method
		public:
			void Enqueue(const T& pushInstance) override final;
			void Dequeue(T& popInstance) override final;

		// property check method
		public:
			/// @brief capacity of ring buffer
			/// @return capacity
			int32_t Capacity() const;
			/// @brief pushable space count
			/// @return space count
			int32_t Size() const;
			T* const GetHeadAddress() const { return _pDataBuffer; }
			bool IsFull() const { return _isFull; }
			bool IsEmpty() const { return (_headIndex == _tailIndex) && (!_isFull); }

		// private property
		private:
			T* _pDataBuffer;
			int16_t _headIndex;
			int16_t _tailIndex;
			uint16_t _bufferSize;
			bool _isFull;

		// copy and move disable
		private:
			RingBuffer(const RingBuffer& rhs) = delete;
			RingBuffer& operator= (const RingBuffer& rhs) = delete;
			RingBuffer(const RingBuffer&& rhs) = delete;
			RingBuffer& operator= (const RingBuffer&& rhs) = delete;

	};
	// End ring buffer

	template<typename T>
	RingBuffer<T>::RingBuffer()
		: _pDataBuffer(nullptr)
		, _headIndex(0)
		, _tailIndex(0)
		, _bufferSize(0)
		, _isFull(false)
	{
		//#ifdef DEBUG
		//	std::cout << "Create ring buffer" << std::endl;
		//#endif
	}

	template<typename T>
	RingBuffer<T>::~RingBuffer()
	{
		{
			//#ifdef DEBUG
			//	std::cout << "Delete ring buffer" << std::endl;
			//	for (int i = 0; i < _bufferSize; ++i)
			//	{
			//		std::cout << _pDataBuffer[i] << std::endl;
			//	}
			//#endif
		}
		for (int i = 0; i < _bufferSize; ++i)
		{
			_pDataBuffer[i].~T();
		}
		// save release memory
		SAVE_FREE(_pDataBuffer)

	}

	/// @brief ring buffer initialize (call this method before use)
	/// @tparam T type store in ring buffer
	/// @param size 
	template<typename T>
	void RingBuffer<T>::Init(int size)
	{
		// set default size when receive negative value
		if (size <= 0)
		{
			_bufferSize = RING_BUFFER_DEFAULT_SIZE;

			//#ifdef DEBUG
			//	std::cout << "receive negative value,use default size" << std::endl;
			//#endif

		}
		// size limitation 10000
		_bufferSize = (size < RING_BUFFER_MAX_SIZE) ? size : RING_BUFFER_MAX_SIZE;
		_pDataBuffer = static_cast<T*>(malloc(sizeof(T) * _bufferSize));
	}

	/// @brief push obj in ring buffer
	/// @tparam T type store in ring buffer
	/// @param pushInstance push obj
	template<typename T>
	void RingBuffer<T>::Enqueue(const T& pushInstance)
	{
		// not initialized
		if(_pDataBuffer == nullptr)
			return;

		// buffer full
		if (IsFull())
		{
			#ifdef  DEBUG
			std::cout << "Ring buffer is full" << std::endl;
			#endif //  DEBUG
			return;
		}

		// push obj
		else
		{
			_pDataBuffer[_headIndex] = std::move(pushInstance);
			_headIndex = (_headIndex + 1) % _bufferSize;
			if (_headIndex == _tailIndex)
			{
				_isFull = true;
			}
			//#ifdef  DEBUG
			//	std::cout << "Ring buffer push method called" << std::endl;
			//#endif //  DEBUG

		}
	}

	/// @brief pop obj
	/// @tparam T type store in ring buffer
	/// @param popInstance pop obj
	template<typename T>
	void RingBuffer<T>::Dequeue(T& popInstance)
	{
		// not initialized
		if(_pDataBuffer == nullptr)
			return;
			
		// buffer empty
		if (IsEmpty())
		{
			#ifdef  DEBUG
				std::cout << "Ring buffer is empty" << std::endl;
			#endif //  DEBUG
			return;
		}

		// pop obj
		else
		{
			popInstance = std::move(_pDataBuffer[_tailIndex]);
			_tailIndex = (_tailIndex + 1) % _bufferSize;
			_isFull = false;
			//#ifdef  DEBUG
			//	std::cout << "Ring buffer pop method called" << std::endl;
			//#endif //  DEBUG
		}
	}

	template<typename T>
	int32_t RingBuffer<T>::Capacity() const
	{
		return _bufferSize;
	}

	template<typename T>
	int32_t RingBuffer<T>::Size() const
	{
		if (IsEmpty())
			return _bufferSize;

		return	(_tailIndex > _headIndex) ?

			// (true)_tailIndex > _headIndex
			(_headIndex - _tailIndex + _bufferSize) :

			// (false)_tailIndex <= _headIndex
			(_headIndex - _tailIndex);

	}
}// namespace MUtil
