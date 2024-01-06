#pragma once
#include <deque>
#include "fiber.hpp"

class Scheduler {
private:
    std::deque<Fiber*> fibers_;
    Context context_;
    void* shared_data_;
    Fiber* current_fiber_;  // Added member to track the current executing fiber
public:
    Scheduler(void* data = nullptr);  // Updated constructor declaration
    ~Scheduler();
    void spawn(Fiber* f);
    void do_it();
    void fiber_exit();
    void* get_data() const;
    Fiber* get_current_fiber() const;  // Added function to get the current executing fiber
};
