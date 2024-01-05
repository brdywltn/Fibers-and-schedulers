#include "fiber.hpp"
#include <cstdint>

Fiber::Fiber(void (*function)()){
    //allocate space for stack
    char stack[4096];
    //stack = new char[4096];
    //stack grows down
    char* sp = stack + 4096;

    //align to 16 bytes and correctly convert between ptr types
    sp = reinterpret_cast<char*>(reinterpret_cast<uintptr_t>(sp) & -16L);

    //adjust for red zone
    sp -= 128;

    //set the rip of context to the provided function now instead of the defined foo
    context_.rip = reinterpret_cast<void*>(function);
    //set rsp of context to sp
    context_.rsp = sp;

    //set stack bottom and top
    stack_bottom_ = stack;
    stack_top_ = sp;
}

Fiber::~Fiber() {
    //delete[] stack;
}

Context Fiber::get_context() const {
    return context_;
}
