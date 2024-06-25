#pragma once

#include <functional>	// std::function
#include <mutex>		// std::mutex
#include <bitset>		// std::bitset

#define DEBUG

#ifndef SAVE_RELEASE
#include "memory_release_def.h"
#endif // !SAVE_RELEASE

// スレッドセーフ
#ifndef THREAD_SAVE
#include "thread_safe_def.h"
#endif // !THREAD_SAVE

namespace MUtil
{
	namespace
	{
		constexpr uint32_t MAX_POOL_SIZE = 1000;
		constexpr uint32_t DEFAULT_POOL_SIZE = 20;

		// プールの値を合法的な値にする
		inline void SetValidSize(int& size)
		{
			// sizeが負の数やゼロの場合はデフォルト値にする (20) 
			// sizeが最大値に超えた場合は限界値にする　(1000)
			// それ以外は何もしない

			if(size <= 0)
			{
				#ifdef DEBUG
					std::cout << "Pool receive invalid size.\nSet to default value = " << DEFAULT_POOL_SIZE << '\n';
				#endif
				size = (int)DEFAULT_POOL_SIZE;
			}

			else if(size > MAX_POOL_SIZE)
			{
				#ifdef DEBUG
					std::cout << "Pool receive too big size.\nSet to max value = " << MAX_POOL_SIZE << '\n';
				#endif

				size = (int)MAX_POOL_SIZE;
			}	
		}
	}// nameless namespace

	// IPoolインターフェース
	template <typename obj>
	class IPool
	{
	public:
		virtual inline obj* Allocate() = 0;
		virtual inline void Recycle(obj* recycleObj) = 0;
		virtual inline void InitPool(std::function<obj*(void* const targetAddress)> factory) = 0;

	// Getter
	public:
		virtual inline bool IsEmpty() const = 0;
		virtual inline bool IsFull() const = 0;
		virtual inline int GetCapacity() const = 0;
		virtual inline int GetCount() const = 0;

	public:
		virtual ~IPool() {}
	};
	// End IPool

	/// @brief Pool
	/// @tparam T type
	template<typename T>
	class Pool : public IPool<T>
	{
	// copy disable
	private:
		Pool(const Pool& rhs) = delete;
		Pool& operator = (const Pool& rhs) = delete;

	// interface implements
	public:
		inline T* Allocate() override;
		inline void Recycle(T* recycleObj) override;
		inline void InitPool(std::function<T* (void* const targetAddress)> factory) override;

	// IPool

	public:
		inline bool IsEmpty() const override { return _headIndex == _tailIndex && (_rwSign == 0b0);}
		inline bool IsFull() const override {	return _headIndex == _tailIndex && (_rwSign == 0b1);}
		inline int GetCapacity() const override { return _poolSize;}
		inline int GetCount() const override
		{
			// プールが満タンになったら最初の計算だと0になってしまうため、
			// プールサイズを加える
			return (_poolSize - _headIndex + _tailIndex) % _poolSize + (IsFull() ? _poolSize : 0);
		}

	// コンストラクタ
	public:
		explicit Pool(int size = 0) 
			: _pPool(nullptr)
			, _poolSize(0)
			, _headIndex(0)
			, _tailIndex(0)
			, _rwSign(0b0)
		{
			// サイズを合理的な値にする
			SetValidSize(size);
			_poolSize = (uint32_t)size;
		}

		// デストラクタ
		virtual ~Pool()
		{
			// スレッドセーフ
			LOCK(_mutex);

			// mallocでメモリを作ったのでコンストラクタを呼び出す
			for(int i = 0;i < _poolSize; ++i)
			{
				_pPool[i].~T();
			}

			// mallocで確保したメモリの解放
			SAVE_FREE(_pPool);
			SAVE_FREE(_pAddressBuffer);

		}

	// Method
	private:

	// Protectedプロパティ
	protected:
		T *_pPool;
		T **_pAddressBuffer;
		uint16_t _poolSize;
		uint16_t _headIndex;
		uint16_t _tailIndex;

	private:
		std::mutex _mutex;		// 
		std::bitset<1> _rwSign;	// 最後の操作の標識		0(読み込み)	1(書き込み)
	 
	};// class Pool  

	/// @brief allocate obj 
	/// @tparam T type
	/// @return ref of allocated obj
	template <typename T>
	inline T* Pool<T>::Allocate()
	{
		LOCK(_mutex);

		if(IsEmpty())
		{
			#ifdef  DEBUG
				std::cout << "Can't allocate object from pool because pool is EMPTY!!\n" ;
			#endif //  DEBUG
			return nullptr;
		}

		if (_pAddressBuffer != nullptr)
		{
			T* alloc = _pAddressBuffer[_headIndex];
			_headIndex = (_headIndex + 1) % _poolSize;
			_rwSign = 0b0;

			return alloc;
		}

		return nullptr;
	}

	/// @brief recycle obj 
	/// @tparam T type
	/// @param recycleObj 
	template <typename T>
	inline void Pool<T>::Recycle(T* recycleObj)
	{
		LOCK(_mutex);

		if(IsFull())
		{
			#ifdef  DEBUG
				std::cout << "Can't recycle object into pool because pool is FULL!!\n";
			#endif //  DEBUG
			return;
		}
		if (_pAddressBuffer != nullptr)
		{
			_pAddressBuffer[_tailIndex] = recycleObj;
			_tailIndex = (_tailIndex + 1) % _poolSize;	
			_rwSign = 0b1;
		}
	}

	/// @brief プールを初期化
	/// @tparam オブジェクトのタイプT
	template<typename T>
	inline void Pool<T>::InitPool(std::function<T* (void* const targetAddress)> factory)
	{
		_pPool = static_cast<T*>(malloc(sizeof(T) * _poolSize));

		// On 32-bit systems, sizeof(void*) = 4 bytes. On 64-bit systems, sizeof(void*) = 8 bytes.
		_pAddressBuffer = static_cast<T**>(malloc(sizeof(void*) * _poolSize));

		if(_pPool != nullptr  && _pAddressBuffer != nullptr)
		{
			// オブジェクトを作って、アドレスをバッファに入れる
			for (int i = 0; i < _poolSize; ++i)
			{
				_pAddressBuffer[i] = factory(_pPool + i);
				//#ifdef DEBUG
				//	std::cout << obj << std::endl;
				//#endif
			}

			// 最後のプール処理サインを書き込みにする
			_rwSign = 0b1;
		}

		// プールやアドレスバッファいずれかのメモリ確保失敗
		else
		{
			// 確保したメモリを解放
			SAVE_FREE(_pPool);
			SAVE_FREE(_pAddressBuffer);

			#ifdef  DEBUG
				std::cout << "Can't init pool because memory is not enough!!\n";
			#endif //  DEBUG
		}
	}

}// namespace MUtil
