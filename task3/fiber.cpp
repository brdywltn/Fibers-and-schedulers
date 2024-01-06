#include "fiber.hpp"
#include "../context/context.hpp"
#include <cstdint>

Fiber::Fiber(void (*function)(), void* data) : shared_data_(data) {
    char stack[4096];
    char* sp = stack + 4096;

    sp = reinterpret_cast<char*>(reinterpret_cast<uintptr_t>(sp) & -16L);
    sp -= 128;

    context_.rip = reinterpret_cast<void*>(function);
    context_.rsp = sp;

    stack_bottom_ = stack;
    stack_top_ = sp;
}

Fiber::~Fiber() {
    // Clean up if necessary
}

Context Fiber::get_context() const {
    return context_;
}

void* Fiber::get_data() const {
    return shared_data_;
}

void Fiber::yield() {
    //save the current context
    //get_context(&context_); //currently not accepting this, too many parameters?
    //set the ip to nullptr to yield
    context_.rip = nullptr;
    //switch back to scheduler
    set_context(&context_);
}