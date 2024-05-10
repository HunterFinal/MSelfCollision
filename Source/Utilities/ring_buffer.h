#pragma once
#include <cstdint>
#include <iostream>
#include <stdexcept>

#include "memory_release_def.h"

#define DEBUG

namespace MUtil
{
	namespace
	{
		constexpr uint16_t RING_BUFFER_MAX_SIZE = 10000;
		constexpr uint16_t RING_BUFFER_DEFAULT_SIZE = 20;
	}// unnamed namespace

	template <typename T>
	class RingBuffer
	{
		public:
			explicit RingBuffer(int size);
			~RingBuffer();
			RingBuffer(const RingBuffer& copy) = delete;
		public:
			void Push(const T& data);
			void Pop(T& popInstance);

		public:
			uint16_t Capacity() const;
			uint16_t Size() const;
			bool IsFull() const { return _isFull; }
			bool IsEmpty() const { return (_headIndex == _tailIndex) && (!_isFull); }

		private:
			T* _pDataBuffer;
			int16_t _headIndex;
			int16_t _tailIndex;
			uint16_t _bufferSize;
			bool _isFull;
	};

	template<typename T>
	RingBuffer<T>::RingBuffer(int size)
		: _pDataBuffer(nullptr)
		, _headIndex(0)
		, _tailIndex(0)
		, _bufferSize(size)
		, _isFull(false)
	{
		if (size <= 0)
		{
			_bufferSize = RING_BUFFER_DEFAULT_SIZE;
			//throw std::invalid_argument("receive negative value");
			#ifdef DEBUG
			std::cout << "receive negative value,use default size" << std::endl;
			#else
			#endif
		
		}
		// max size 10000
		_bufferSize = (_bufferSize < RING_BUFFER_MAX_SIZE) ? _bufferSize : RING_BUFFER_MAX_SIZE;
		_pDataBuffer = new T[_bufferSize];
	}

	template<typename T>
	RingBuffer<T>::~RingBuffer()
	{
		SAVE_DELETE_ARRAY(_pDataBuffer)

		// コンソールデバッグ用
		{
			#ifdef DEBUG
			std::cout << "Delete" << std::endl;
			#endif
		}
	}

	template<typename T>
	void RingBuffer<T>::Push(const T& data)
	{
		if (IsFull())
		{
			#ifdef  DEBUG
			std::cout << "Ring buffer is full" << std::endl;
			#endif //  DEBUG
			return;
		}
		else
		{
			_pDataBuffer[_headIndex] = data;
			_headIndex = (_headIndex + 1) % _bufferSize;
			if (_headIndex == _tailIndex)
			{
				_isFull = true;
			}
		}
	}

	/// <summary>
	/// Pop the last element added into the buffer
	/// </summary>
	/// <typeparam name="T">type of element store in the buffer</typeparam>
	/// <returns>T* (can be nullptr)</returns>
	template<typename T>
	void RingBuffer<T>::Pop(T& popInstance)
	{
		if (IsEmpty())
		{
			#ifdef  DEBUG
			std::cout << "Ring buffer is empty" << std::endl;
			#endif //  DEBUG
			return;
		}
		else
		{
			popInstance = _pDataBuffer[_tailIndex];
			_tailIndex = (_tailIndex + 1) % _bufferSize;
			_isFull = false;
		}
	}

	template<typename T>
	uint16_t RingBuffer<T>::Capacity() const
	{
		return _bufferSize;
	}

	template<typename T>
	uint16_t RingBuffer<T>::Size() const
	{
		return	(_tailIndex > _headIndex) ? 
				// _tailIndex > _headIndex
				(_headIndex - _tailIndex + _bufferSize) : 
				// _tailIndex <= _headIndex
				(_headIndex - _tailIndex);
	}
}// namespace MUtil
