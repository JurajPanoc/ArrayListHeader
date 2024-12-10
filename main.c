#include <stdio.h>
#include <stdlib.h>
#include "list.h"


add_base_func(int, "%d")
add_base_func(char, "'%c'")
add_base_func(str, "\"%s\"")


int main(){
    List* ints = list_ctor(int);
    List* chars = list_ctor(char);
    List* words = list_ctor(str);

    for(int i = 0; i < 5; i++){
        append_int(ints, i);
        append_char(chars, i + 'a');
    }

    append_str(words, "Hello, ");
    append_str(words, "world");

    print_list_char(chars);
    print_list_int(ints);
    print_list_str(words);

    pop_int(ints);
    pop_char(chars);
    pop_str(words);

    print_list_char(chars);
    print_list_int(ints);
    print_list_str(words);

    list_dtor(&ints);
    list_dtor(&chars);
    list_dtor(&words);
    return 0;
}