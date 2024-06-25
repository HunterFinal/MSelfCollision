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
//                                  SingletonClass() = default;             // Constructor need to be private or protected
//                              public:
//                                  ~SingletonClass() = default;            // Destructor need to be public
//                          }
// Update:              2024/06/17  Create
//
// Author:              MAI ZHICONG
// ---------------------------------------------------------------------------------------------------------------------------------------

#pragma once

#include <memory>   // std::shared_ptr

namespace MDesignPattern
{
    namespace MSingleton
    {
        // シングルトン
        template<typename T>
        class Singleton
        {

        public:
            static inline std::shared_ptr<T> GetInstance()
            {
                // インスタンス生成は一回しか実行しない
                static std::once_flag flag;
                std::call_once(flag,[&]()
                {
                    _instance = std::shared_ptr<T>(new T);
                });

                return _instance;
            }

        protected:
            Singleton() {}

        private:
            Singleton(const Singleton& other) = delete;
            Singleton& operator=(const Singleton& other) = delete;

        private:
            static std::shared_ptr<T> _instance;
        };

        template<typename T>
        std::shared_ptr<T> Singleton<T>::_instance = nullptr;
    }// namespace MSingleton

}// namespace MDesignPattern
