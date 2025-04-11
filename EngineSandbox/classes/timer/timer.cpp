#pragma once
#include <iostream>
#include<chrono>

class ScopedTimer{
public:
    ScopedTimer() = delete;
    ScopedTimer(const char* name) : name_m(name){
        start = std::chrono::high_resolution_clock::now();
    }
    ~ScopedTimer(){
        end = std::chrono::high_resolution_clock::now();
        auto ms = std::chrono::duration<float, std::chrono::milliseconds::period>(end - start);
        std::cout   << name_m << "::"  << ms.count() << "ms" << "\n";
    }
private:
    const char* name_m{"default"};
    std::chrono::time_point<std::chrono::steady_clock> start;
    std::chrono::time_point<std::chrono::steady_clock> end;
};
//#define LOG_PROFILE
#ifdef LOG_PROFILE
#define PROFILE_FUNC(...) ScopedTimer timer_##__LINE__(__FUNCTION__);
#define PROFILE_SCOPE(name) ScopedTimer timer_##__LINE__(name);
#else
#define PROFILE_FUNC(...)
#define PROFILE_SCOPE(name) 
#endif

