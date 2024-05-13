#pragma once
#include <cstdint>
#include <iostream>
#include <stdexcept>

#ifndef SAVE_RELEASE
#include "memory_release_def.h"
#endif // !SAVE_RELEASE
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
		// コピー禁止
		RingBuffer(const RingBuffer& copy) = delete;
		RingBuffer& operator= (const RingBuffer& copy) = delete;
		// ムーブ禁止
		RingBuffer(const RingBuffer&& copy) = delete;
		RingBuffer& operator= (const RingBuffer&& copy) = delete;

		public:
			RingBuffer();
			~RingBuffer();

		public:
			void Init(int size);

		public:
			void Push(const T& data);
			void Pop(T& popInstance);

		public:
			int32_t Capacity() const;
			int32_t Size() const;
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
		SAVE_DELETE_ARRAY(_pDataBuffer)

		// コンソールデバッグ用
		{
			//#ifdef DEBUG
			//	std::cout << "Delete ring buffer" << std::endl;
			//#endif
		}
	}

	template<typename T>
	void RingBuffer<T>::Init(int size)
	{
		if (size <= 0)
		{
			_bufferSize = RING_BUFFER_DEFAULT_SIZE;

			#ifdef DEBUG
				std::cout << "receive negative value,use default size" << std::endl;
			#else
			#endif

		}
		// max size 10000
		_bufferSize = (size < RING_BUFFER_MAX_SIZE) ? size : RING_BUFFER_MAX_SIZE;
		_pDataBuffer = new T[_bufferSize];
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
			//#ifdef  DEBUG
			//	std::cout << "Ring buffer push method called" << std::endl;
			//#endif //  DEBUG
		}
	}

	/// <summary>
	/// Pop the last element added into the buffer
	/// </summary>
	/// <typeparam name="T">type of element store in the buffer</typeparam>
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
		return	(_tailIndex > _headIndex) ? 
				// _tailIndex > _headIndex
				(_headIndex - _tailIndex + _bufferSize) : 
				// _tailIndex <= _headIndex
				(_headIndex - _tailIndex);
	}
}// namespace MUtil
