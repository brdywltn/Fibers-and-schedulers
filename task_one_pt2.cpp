#include <iostream>
#include <cstdint>
#include "context/context.hpp"

//Global context
Context gooContext;


// func foo:
void foo(){
    //output 'you called foo'
    std::cout << "you called foo" << std::endl;
    set_context(&gooContext);
}

void goo(){
    std::cout << "you called goo" << std::endl;

    exit(0);
}

//func main:
int main(){
    // allocate space for stack
    // data is an array of 4096 characters
    char stack[4096];
    // stack grows downards
    // sp is a pointer to characters
    // set sp to data plus 4096
    char *sp = stack + 4096;

    //align to 16 bytes and correctly convert between ptr types
    sp = reinterpret_cast<char*>(reinterpret_cast<uintptr_t>(sp) & -16L);

    //adjust for red zone
    sp -= 128;
    
    // create an empty context c
    Context c;
    // set rip of c to foo
    c.rip = reinterpret_cast<void*>(&foo);
    // set rsp of c to sp
    c.rsp = sp;
    // call set_context with c

    char new_stack[4096];
    char *nsp = new_stack + 4096;

    nsp = reinterpret_cast<char*>(reinterpret_cast<uintptr_t>(nsp) & -16L);
    nsp -= 128;
    gooContext.rip = reinterpret_cast<void*>(&goo);
    gooContext.rsp = nsp;

    set_context(&c);

    return 0;
}