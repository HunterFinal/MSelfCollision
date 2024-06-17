#pragma once

#include <iostream>
#include <memory>

#ifndef THREAD_SAVE
#include "thread_safe_def.h"
#endif

template<typename T>
class Singleton
{

public:
    static inline T& GetInstance()
    {
        if(_instance == nullptr)
        {
            LOCK(_mutex);

            if(_instance == nullptr)
                _instance = std::make_unique<T>();
        }
        return *(_instance.get());
    }

protected:
    Singleton() {}
    virtual ~Singleton() { std::cout << "base singleton destructor" << std::endl;}

private:
    Singleton(const Singleton& other) = delete;
    Singleton& operator=(const Singleton& other) = delete;

private:
    static std::unique_ptr<T> _instance;
    static std::mutex _mutex;
};

template<typename T>
std::unique_ptr<T> Singleton<T>::_instance = nullptr;


class TestSingleton : public Singleton<TestSingleton>
{
    friend class Singleton<TestSingleton>;

public:
    ~TestSingleton() override { std::cout << "Test destructor" << std::endl;}

public:
    void print()
    {
        std::cout << "Test Singleton" << std::endl;
    }

public:
    TestSingleton() = default;

private:
    TestSingleton(const TestSingleton& other) = delete;
    TestSingleton& operator =(const TestSingleton& other) = delete; 
};