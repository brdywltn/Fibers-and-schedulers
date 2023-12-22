#include <iostream>
#include <cstdint>
#include "context/context.hpp"

// fiber class
class Fiber{
private:
    //context
    //stack bottom
    //stack top
public:
    //fiber constructor
    //fiber destructor
    //get context
};

// foo func
void foo (){
    std::cout << "Foo fighter" << std::endl;
}

// main
int main(){
    //set f by creating fiber with foo
    //set c calling method function get_context from f
    //call set_context with c
    return 0;
}