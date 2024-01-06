#include "scheduler.hpp"

Scheduler::Scheduler(void* data) : shared_data_(data), current_fiber_(nullptr) {
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

        current_fiber_ = f;  // Update the current executing fiber

        // Set shared data for each fiber before switching context
        shared_data_ = f->get_data();

        Context c = f->get_context();
        set_context(&c);

        // Check if the fiber yielded control
        if (c.rip == nullptr) {
            fibers_.push_back(f);  // Push the fiber back to the queue
        }
    }

    current_fiber_ = nullptr;  // Reset the current executing fiber after execution
}

void Scheduler::fiber_exit() {
    set_context(&context_);
}

void* Scheduler::get_data() const {
    return shared_data_;
}

Fiber* Scheduler::get_current_fiber() const {
    return current_fiber_;
}
