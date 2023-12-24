#include <iostream>
#include <cstdint>
#include <deque>
#include "context/context.hpp"


// fiber class
class Fiber {
private:
    //context
    Context context_;
    //stack bottom
    char* stack_bottom_;
    //stack top
    char* stack_top_;
    //char* stack;
public:
    //fiber constructor
    Fiber(void (*function)()){
        //allocate space for stack
        char stack[4096];
        //stack = new char[4096];
        //stack grows down
        char* sp = stack + 4096;

        //align to 16 bytes and correctly convert between ptr types
        sp = reinterpret_cast<char*>(reinterpret_cast<uintptr_t>(sp) & -16L);

        //adjust for red zone
        sp -= 128;

        //set the rip of context to the provided function now instead of the defined foo
        context_.rip = reinterpret_cast<void*>(function);
        //set rsp of context to sp
        context_.rsp = sp;

        //set stack bottom and top
        stack_bottom_ = stack;
        stack_top_ = sp;


    }

    //fiber destructor
    ~Fiber() {
        //delete[] stack;
    }

    //get context
    Context get_context() const {
        return context_;
    }
};

class Scheduler {
private:
    //fibers_:std::deque<fiber*>
    std::deque<Fiber*> fibers_;
    //context_: Context
    Context context_;
public:
    //scheduler()
    Scheduler(){
        //initialise context
    }
    //~scheduler
    ~Scheduler(){
        //get rid
    }
    //spawn(f:fiber*): void
    void spawn(Fiber* f) {
        //add context to back of queue
        fibers_.push_back(f);
    }

    //do_it(): void
    void do_it(){
        //return here to reenter scheduler
        get_context(&context_);
        //continue executing fibers in RR mode
        while (!fibers_.empty()) {
            //pop front fiber from queue
            Fiber* f = fibers_.front();
            fibers_.pop_front();
            //set entry point for fiber
            Context c = f->get_context();
            set_context(&c);
        }
    }
    //fiber_exit(): void
    void fiber_exit() {
        //jump back to loop
        set_context(&context_);
    }
};

//global scheduler instance?
Scheduler s;

// foo func
void foo (){
    std::cout << "Foo fighter" << std::endl;
    s.fiber_exit();
}

// main
int main(){
    //set f by creating fiber with foo
    Fiber f1(&foo);
    Fiber f2(&foo);
    Fiber f3(&foo);
    //set c calling method function get_context from f
    s.spawn(&f1);
    s.spawn(&f2);
    s.spawn(&f3);
    s.do_it();
    
    return 0;
}