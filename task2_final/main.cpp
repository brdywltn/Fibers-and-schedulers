// main.cpp

#include <iostream>
#include "fiber.hpp"
#include "scheduler.hpp"

Scheduler s;

void foo() {
    std::cout << "fiber 1: " << *static_cast<int*>(s.get_data()) << std::endl;
    int* dp = static_cast<int*>(s.get_data());
    *dp = *dp + 1;
    s.fiber_exit();
}

void goo() {
    std::cout << "fiber 2: " << *static_cast<int*>(s.get_data()) << std::endl;
    int* dp = static_cast<int*>(s.get_data());
    *dp = *dp + 1;
    s.fiber_exit();
}

int main() {
    int d = 10;
    int* dp = &d;

    Fiber f1(&foo, dp);
    Fiber f2(&goo, dp);

    s.spawn(&f1);
    s.spawn(&f2);

    s.do_it();

    return 0;
}
