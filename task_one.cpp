#include <iostream>
#include <cstdint>
#include "context/context.hpp"

int main(){
    // 1. set x to 0 (volatile)
    volatile int x = 0;
    // 2. set c to get_context
    Context c;
    get_context(&c);
    // 3. output "a message"
    std::cout << "a message" << std::endl;
    // 4. if x == 0:
    if (x == 0) {
        // 5. set x to x plus one
        x = x + 1;
        // 6. call set_context with c
        set_context(&c);
    }
    
    return 0;
}