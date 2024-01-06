#pragma once
#include "../context/context.hpp"

class Fiber {
private:
    Context context_;
    char* stack_bottom_;
    char* stack_top_;
    void* shared_data_;  // Added member for shared data
public:
    Fiber(void (*function)(), void* data = nullptr);  // Updated constructor
    ~Fiber();
    Context get_context() const;
    void* get_data() const;  // Added function to get shared data
    int yield();  // Added function to yield control to the scheduler
};