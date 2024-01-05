#include <iostream>
#include "fiber.hpp"
#include "scheduler.hpp"

Scheduler s;

void foo() {
    std::cout << "Foo fighter" << std::endl;
    s.fiber_exit();
}

int main() {
    Fiber f1(&foo);
    Fiber f2(&foo);
    Fiber f3(&foo);

    s.spawn(&f1);
    s.spawn(&f2);
    s.spawn(&f3);

    s.do_it();

    return 0;
}



