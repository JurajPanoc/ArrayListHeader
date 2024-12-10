#include <stdio.h>
#include <stdlib.h>
#include "list.h"


add_base_func(int, "%d")
add_base_func(char, "'%c'")
add_base_func(str, "\"%s\"")

//tests
void test_append(List* ints, List* chars, List* words);

void test_print(List* int_list, List* char_list, List* str_list);

void test_insert(List* int_list, List* char_list, List* str_list);

void test_pop(List* int_list, List* char_list, List* str_list);

void test_remove(List* int_list, List* char_list, List* str_list);


int main(){
    List* ints = list_ctor(int);
    List* chars = list_ctor(char);
    List* words = list_ctor(str);

    test_append(ints, chars, words);

    test_pop(ints, chars, words);

    test_insert(ints, chars, words);

    test_remove(ints, chars, words);

    list_dtor(&ints);
    list_dtor(&chars);
    list_dtor(&words);
    return 0;
}


void test_append(List* int_list, List* char_list, List* str_list){
    puts("append test");
    for(int i = 0; i < 12; i++){
        append_int(int_list, i);
        append_char(char_list, i + 'a');
    }

    append_str(str_list, "Hello, ");
    append_str(str_list, "world");

    test_print(int_list, char_list, str_list);
}


void test_insert(List* int_list, List* char_list, List* str_list){
    puts("insert test");
    insert_int(int_list, 1, 5);
    insert_char(char_list, 1, 'A');
    insert_str(str_list, 0, "AHOJ");

    test_print(int_list, char_list, str_list);
}


void test_pop(List* int_list, List* char_list, List* str_list){
    puts("pop test");
    pop_int(int_list);
    pop_char(char_list);
    pop_str(str_list);

    test_print(int_list, char_list, str_list);
}


void test_remove(List* int_list, List* char_list, List* str_list){
    puts("remove test");
    remove_int(int_list, 1);
    remove_char(char_list, 1);
    remove_str(str_list, 0);

    test_print(int_list, char_list, str_list);
}


void test_print(List* int_list, List* char_list, List* str_list){
    printf("char arr len %ld\n", char_list->len);
    printf("char arr size %ld\n", char_list->size);

    print_list_char(char_list);
    print_list_int(int_list);
    print_list_str(str_list);
    
    puts("-------------------------");
}