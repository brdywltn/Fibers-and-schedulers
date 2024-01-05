#include "scheduler.hpp"

Scheduler::Scheduler() {
    //initialise context if necessary
}

Scheduler::~Scheduler() {
    // Clean up if necessary
}

void Scheduler::spawn(Fiber* f){
    fibers_.push_back(f);
}

void Scheduler::do_it(){
    get_context(&context_);

    while (!fibers_.empty()) {
        Fiber* f = fibers_.front();
        fibers_.pop_front();
        Context c = f->get_context();
        set_context(&c);
    }
}

void Scheduler::fiber_exit() {
    set_context(&context_);
}