#include <iostream>
#include "fiber.hpp"
#include "scheduler.hpp"

Scheduler s;

void func1() {
    std::cout << "fiber 1 before" << std::endl;
    Fiber* current_fiber = s.get_current_fiber();
    current_fiber->yield();  // Yield control back to the scheduler
    std::cout << "fiber 1 after" << std::endl;
    s.fiber_exit();
}

void func2() {
    std::cout << "fiber 2" << std::endl;
    s.fiber_exit();
}

int main() {
    Fiber f2(&func2);
    Fiber f1(&func1);
    

    s.spawn(&f1);
    s.spawn(&f2);

    s.do_it();

    return 0;
}