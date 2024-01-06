#pragma once
#include <deque>
#include "fiber.hpp"

class Scheduler {
private:
    std::deque<Fiber*> fibers_;
    Context context_;
    void* shared_data_;  // Added member for shared data
public:
    Scheduler(void* data = nullptr);  // Updated constructor
    ~Scheduler();
    void spawn(Fiber* f);
    void do_it();
    void fiber_exit();
    void* get_data() const;  // Added function to get shared data
};