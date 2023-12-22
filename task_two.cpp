#include <iostream>
#include <cstdint>
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
public:
    //fiber constructor
    Fiber(void (*function)()){
        //allocate space for stack
        char stack[4096];
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
        delete stack_bottom_;
        delete stack_top_;
    }

    //get context
    Context get_context() const {
        return context_;
    }
};

// foo func
void foo (){
    std::cout << "Foo fighter" << std::endl;
    exit(0);
}

// main
int main(){
    //set f by creating fiber with foo
    Fiber f(&foo);
    //set c calling method function get_context from f
    Context c = f.get_context();
    //call set_context with c
    set_context(&c);
    
    return 0;
}