// func foo:
int foo(){
    // output "you called foo"
    // call function exit
    return 0;
}

//func main:
int main(){
    // allocate space for stack
    // data is an array of 4096 characters
      
    // stack grows downards
    // sp is a pointer to characters
    // set sp to data plus 4096
    
    // create an empty context c
    // set rip of c to foo
    // set rsp of c to sp

    // call set_context with c 
    return 0;
}