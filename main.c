#include <stdio.h>
#include <stdlib.h>
#include "list.h"


init_list(int)
init_list(char)
init_list(str)

void outside_scope(list_str* z){
    print_list(z, "%s");
}

int main(){
    list_ctor(x, int)
    list_ctor(y, char)
    list_ctor(z, str)

    z->len = 2;
    iget(z, 0) = "Hello"; //alternate syntax for accessing array elements (no -> needed)
    z->data[1] = "World";
    
    outside_scope(z);
    
    y->len = 3;
    x->len = 3;
    
    x->data[0] = 4;
    x->data[1] = 1;
    x->data[2] = 7;
    y->data[0] = 'a';
    y->data[1] = 'h';
    y->data[2] = 'a';
    
    print_list(x, "%d")
    print_list(y, "%c")
    print_list(z, "%s")
    
    list_dtor(x)
    list_dtor(y)
    list_dtor(z)
    return 0;
}