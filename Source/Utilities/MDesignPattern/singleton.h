// ---------------------------------------------------------------------------------------------------------------------------------------
// File name:           singleton.h
// Version:             v1.0
// Description:         A template singleton class
// Namespace:           MDesignPattern::MSingleton
// Note:                Example
//                          class SingletonClass :: public Singleton<SingletonClass>
//                          {
//                              friend class Singleton<SingletonClass>;
//                              private:
//                                  SingletonClass() = default;             // Constructor and Destructor need to be private or protected
//                                  ~SingletonClass() = default;            
//                          }
// Update:              2024/06/17  Create
//                      2024/08/15  Change GetInstance to raw-pointer(it was shared_ptr before)
//                                  Add Singleton GC(prevent memory leak if someone forget to release manually)
//
// Author:              MAI ZHICONG
// ---------------------------------------------------------------------------------------------------------------------------------------

#pragma once

//#include <memory>   // std::shared_ptr

#include "thread_safe_def.h"
#include <cassert>

#include <atomic>

namespace MDesignPattern
{
    namespace MSingleton
    {
        // シングルトン
        template<typename T>
        class Singleton
        {
        private:
            
            // GC class
            class SingletonGC
            {
                public:
                    ~SingletonGC()
                    {
                        T* temp = _instance.load();
                        if (temp != nullptr)
                        {
                            // TODO need test
                            delete temp;
                        }
                    }
            };

        public:
            //
            // smart pointer version
            //
            // static inline std::shared_ptr<T> GetInstance()
            // {
            //     // インスタンス生成は一回しか実行しない
            //     static std::once_flag flag;
            //     std::call_once(flag,[&]()
            //     {
            //         _instance = std::shared_ptr<T>(new T);
            //     });

            //     return std::make_shared<T>(_instance);
            // }

            /// <summary>
            /// シングルトンを初期化する
            /// </summary>
            /// <typeparam name="...Args">初期化子</typeparam>
            /// <param name="...args"></param>
            template<typename... Args>
            static inline void CreateInstance(Args... args)
            {
                // TODO need understand atomic
                T* instancePtr = _instance.load(std::memory_order_relaxed);
                std::atomic_thread_fence(std::memory_order_acquire);

                if (instancePtr == nullptr)
                {
                    LOCK(_padlock)
                    instancePtr = _instance.load(std::memory_order_relaxed);

                    if (instancePtr == nullptr)
                    {
                        instancePtr = new T(args...);
                        std::atomic_thread_fence(std::memory_order_release);
                        _instance.store(instancePtr,std::memory_order_relaxed);

                        // atexit can register at least 32 functions
                        // but......
                        // limit is implementation-defined
                        // so I can't use it in a template class

                        // atexit(ReleaseInstance);
                        
                    } // end of second null check
                } // end of first null check
            }

            static inline T* GetInstance()
            {
                return _instance.load();
            }

            static inline void ReleaseInstance()
            {
                T* instancePtr = _instance.load(std::memory_order_relaxed);
                std::atomic_thread_fence(std::memory_order_acquire);
                if (instancePtr != nullptr)
                {
                    LOCK(_padlock);
                    instancePtr = _instance.load(std::memory_order_relaxed);

                    if (instancePtr != nullptr)
                    {
                        delete instancePtr;
                        instancePtr = nullptr;

                        std::atomic_thread_fence(std::memory_order_release);
                        _instance.store(instancePtr,std::memory_order_relaxed);
                    } // end of second null check
                } // end of first null check
            }


        protected:
            Singleton() = default;
            virtual ~Singleton() = default;

        private:
            Singleton(const Singleton&) = delete;
            Singleton& operator=(const Singleton&) = delete;

        // private:
        //    void operator delete(void* ptr) noexcept
        //    {
        //        ((T*)ptr)->~T();
        //        free(ptr);
        //    }

        private:
            static std::atomic<T*> _instance;
            static std::mutex _padlock;
            // must place this under _instance
            static SingletonGC _gcObj;
        };

        // static member initialize
        template<typename T>
        std::atomic<T*> Singleton<T>::_instance;
        template<typename T>
        std::mutex Singleton<T>::_padlock;
        // TODO
        // need typename in front of it(tell compiler it is a type)
        template<typename T>
        typename Singleton<T>::SingletonGC Singleton<T>::_gcObj;

    }// namespace MSingleton

}// namespace MDesignPattern
