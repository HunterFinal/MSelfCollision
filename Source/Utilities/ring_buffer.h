#pragma once
#include <cstdint>
#include <iostream>

#include "memory_release_def.h"

#define RING_BUFFER_MAX_SIZE 10000


namespace MUtil
{
	template <typename T>
	class RingBuffer
	{
		public:
			RingBuffer(const int size);
			~RingBuffer();
		public:

		private:
			T* _dataBuffer;
			int16_t _lastRead;
			int16_t _lastInsert;
			int16_t _bufferSize;
	};

	template<typename T>
	RingBuffer<T>::RingBuffer(const int size)
		: _dataBuffer(nullptr)
		, _lastRead(0)
		, _lastInsert(0)
		, _bufferSize(size)
	{
		_dataBuffer = new T[_bufferSize];
	}

	template<typename T>
	RingBuffer<T>::~RingBuffer()
	{
		SAVE_DELETE_ARRAY(_dataBuffer)

	#ifdef DEBUG
			std::cout << "Delete" << std::endl;
	#endif
	}
}// namespace MUtil
