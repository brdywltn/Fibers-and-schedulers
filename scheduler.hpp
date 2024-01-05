#pragma once
#include <deque>
#include "fiber.hpp"

class Scheduler {
private:
    std::deque<Fiber*> fibers_;
    Context context_;

public:
    Scheduler();

    ~Scheduler();

    void spawn(Fiber* f);

    void do_it();

    void fiber_exit();
};