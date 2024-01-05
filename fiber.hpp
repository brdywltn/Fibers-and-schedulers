#pragma once
#include "context/context.hpp"

class Fiber {
private:
    Context context_;
    char* stack_bottom_;
    char* stack_top_;
public:
    Fiber(void (*function)());
    ~Fiber();
    Context get_context() const;
};