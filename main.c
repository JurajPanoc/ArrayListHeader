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
    list_ctor(x, int);
    list_ctor(y, char);
    list_ctor(z, str);

    append(z, "Hello");
    append(z, "World");

    outside_scope(z);

    append(x, 4);
    append(x, 1);
    append(x, 7);

    append(y, 'a');
    append(y, 'h');
    append(y, 'a');

    char res = pop(y); //fix this buggy c extention behavior (compiler is fine with it just the extention doesn't like it)
    
    printf("popped item: %c\n", res);
    print_list(x, "%d");
    print_list(y, "%c");
    print_list(z, "%s");
    
    list_dtor(x);
    list_dtor(y);
    list_dtor(z);
    return 0;
}