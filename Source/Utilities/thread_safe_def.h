#pragma once

#define THREAD_SAVE

#include <mutex>

#define LOCK(padlock) { std::lock_guard<std::mutex>guard(padlock);}