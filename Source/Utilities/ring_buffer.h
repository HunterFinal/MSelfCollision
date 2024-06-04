#pragma once
#include <cstdint>
#include <iostream>
#include <mutex>

// --マクロ定義--

// メモリ解放
#ifndef SAVE_RELEASE
#include "memory_release_def.h"
#endif // !SAVE_RELEASE

// スレッドセーフ
#ifndef THREAD_SAVE
#include "thread_safe_def.h"
#endif // !THREAD_SAVE

// コンソールデバッグ用
#define DEBUG

// --マクロ定義--



namespace MUtil
{
	namespace
	{
		constexpr uint32_t RING_BUFFER_MAX_CAPACITY = 1000;
		constexpr uint32_t RING_BUFFER_DEFAULT_CAPACITY = 20;

		template<typename T>
		class IFIFO
		{
			public:
				virtual void Enqueue(const T& pushInstance) = 0;
				virtual void Dequeue(T& popInstance) = 0;
		};
	}// unnamed namespace

	/// @brief RingBuffer
	template <typename T>
	class RingBuffer:public IFIFO<T>
	{
		// コンストラクタとデストラクタ
		public:
			RingBuffer();
			~RingBuffer();

		// 初期化
		public:
			bool Init(int size);

		// データ操作
		public:
			void Enqueue(const T& pushInstance) override final;
			void Dequeue(T& popInstance) override final;

		// データ検索
		public:
			uint32_t GetCapacity() const { return _capacity; }
			uint32_t GetCount() const { return _count; }
			uint32_t GetUsedCount() const { return _capacity - _count; }

			T* const GetHeadAddress() const { return _pDataBuffer; }
			bool IsFull() const { return ((_tailIndex + 1) % _capacity) == _headIndex; }
			bool IsEmpty() const { return (_headIndex == _tailIndex); }

		// プロパティ
		private:
			T* _pDataBuffer;
			uint32_t _headIndex;
			uint32_t _tailIndex;
			uint32_t _capacity;
			uint32_t _count;
			std::mutex _mutex;

		// コピー禁止
		private:
			RingBuffer(const RingBuffer& rhs) = delete;
			RingBuffer& operator= (const RingBuffer& rhs) = delete;
	};
	// End RingBuffer

#pragma region RingBuffer Definition

	template<typename T>
	RingBuffer<T>::RingBuffer()
		: _pDataBuffer(nullptr)
		, _headIndex(0)
		, _tailIndex(0)
		, _capacity(0)
		, _count(0)
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
		for (int i = 0; i < _capacity; ++i)
		{
			_pDataBuffer[i].~T();
		}
		// save release memory
		SAVE_FREE(_pDataBuffer)

	}

	/// @brief ring buffer initialize (call this method before use)
	/// @tparam T type store in ring buffer
	/// @param capacity 
	template<typename T>
	bool RingBuffer<T>::Init(int capacity)
	{
		// set default capacity when receive negative value
		if (capacity <= 0)
		{
			_capacity = RING_BUFFER_DEFAULT_CAPACITY;
			//#ifdef DEBUG
			//	std::cout << "receive negative value,use default size " << RING_BUFFER_DEFAULT_SIZE << std::endl;
			//#endif
		}
		// size limitation RING_BUFFER_MAX_SIZE
		else if(capacity > RING_BUFFER_MAX_CAPACITY)
		{
			_capacity = RING_BUFFER_MAX_CAPACITY;
			//#ifdef DEBUG
			//	std::cout << "receive exceeded value,use max size " << RING_BUFFER_MAX_SIZE << std::endl;
			//#endif
		}
		else
		{
			_capacity = (uint32_t)capacity;
		}

		// メモリ確保
		_pDataBuffer = static_cast<T*>(malloc(sizeof(T) * _capacity));

		if(_pDataBuffer == nullptr)
		{
			return false;
		}

		++_headIndex;
		_count = _capacity;

		return true;
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
			LOCK(_mutex)

			_tailIndex = (_tailIndex + 1) % _capacity;
			_pDataBuffer[_tailIndex] = std::move(pushInstance);

			++count;
			
			/*
			#ifdef  DEBUG
				std::cout << "Ring buffer push method called" << std::endl;
				std::cout << "Enqueue Index :" << _tailIndex << std::endl;
			#endif //  DEBUG
			*/


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
			LOCK(_mutex)

			popInstance = std::move(_pDataBuffer[_headIndex]);
			/*
			#ifdef  DEBUG
				std::cout << "Ring buffer pop method called" << std::endl;
			  	std::cout << "Pop Index :" << _headIndex << std::endl;
			#endif //  DEBUG
			*/
			_headIndex = (_headIndex + 1) % _capacity;

			--count;
		}
	}

#pragma endregion // RingBuffer Definition

}// namespace MUtil
