// scheduler.cpp

#include "scheduler.hpp"

Scheduler::Scheduler(void* data) : shared_data_(data) {
    // initialize context if necessary
}

Scheduler::~Scheduler() {
    // Clean up if necessary
}

void Scheduler::spawn(Fiber* f) {
    fibers_.push_back(f);
}

void Scheduler::do_it() {
    get_context(&context_);

    while (!fibers_.empty()) {
        Fiber* f = fibers_.front();
        fibers_.pop_front();

        // Set shared data for each fiber before switching context
        shared_data_ = f->get_data();

        Context c = f->get_context();
        set_context(&c);
    }
}

void Scheduler::fiber_exit() {
    set_context(&context_);
}

void* Scheduler::get_data() const {
    return shared_data_;
}
