#pragma once

#ifndef THREAD_SAVE || _THREAD_SAVE
#define THREAD_SAVE

#include <mutex>

#define LOCK(padlock) { std::lock_guard<std::mutex>guard(padlock);}
#endif