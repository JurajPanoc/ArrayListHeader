#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

// added here just to test out the find functions
int int_cmp(int x, int y){return x - y;}

int char_cmp(char x, char y) {return x - y;}

typedef struct testing{
    int num;
    char* name;
} TestStruct;

int struct_cmp(TestStruct x, TestStruct y) {return x.num - y.num;}

void multiply(int* i) {*i *= 2;}
void capitalize(char* i) {*i -= 32;}

int filter_for_int(int x){return x < 5;}
int filter_for_char(char x){return x >= 'A' && x <= 'F';}
int filter_for_str(str x){return x[0] == 'H';}
int filter_for_struct(TestStruct x){return x.num <= 15;}


// define the way the print_list_type function will print out the type
// TODO: make this less painful to set up
#define print_int(i) printf("%d", iget(list, int, i));
#define print_char(i) printf("'%c'", iget(list, char, i));
#define print_str(i) printf("\"%s\"", iget(list, str, i));
#define print_test_struct(i) printf("(num: %d, name: \"%s\")", \
                                    iget(list, TestStruct, i).num, iget(list, TestStruct, i).name);


// TODO: add an initializer with the possibility of copying in preexisting arrays
add_base_func(int, print_int, int_cmp)
add_base_func(char, print_char, char_cmp)
add_base_func(str, print_str, strcmp) //strings are static, cannot be modified
add_base_func(TestStruct, print_test_struct, struct_cmp)

// only used for the ease of writing new test functions
#define TEST_ARGS List* int_list, List* char_list, List* str_list, List* struct_list

//tests
void test_append(TEST_ARGS);

void test_print(TEST_ARGS);

void test_insert(TEST_ARGS);

void test_pop(TEST_ARGS);

void test_remove(TEST_ARGS);

void test_find(TEST_ARGS);

void test_map(TEST_ARGS);

void test_filter(TEST_ARGS);


int main(){
    List* ints = list_ctor(int);
    List* chars = list_ctor(char);
    List* words = list_ctor(str);
    List* structs = list_ctor(TestStruct);
    

    test_append(ints, chars, words, structs);

    test_pop(ints, chars, words, structs);

    test_insert(ints, chars, words, structs);

    test_remove(ints, chars, words, structs);

    test_find(ints, chars, words, structs);

    test_map(ints, chars, words, structs);

    test_filter(ints, chars, words, structs);

    list_dtor(&ints);
    list_dtor(&chars);
    list_dtor(&words);
    list_dtor(&structs);
    return 0;
}


void test_append(TEST_ARGS){
    puts("append test");
    for(int i = 0; i < 12; i++){
        append_int(int_list, i);
        append_char(char_list, i + 'a');
    }

    append_str(str_list, "Hello, ");
    append_str(str_list, "world");
    append_TestStruct(struct_list, (TestStruct){.num = 8, .name = "John"});
    append_TestStruct(struct_list, (TestStruct){.num = 17, .name = "Amy"});
    append_TestStruct(struct_list, (TestStruct){.num = 55, .name = "Cain"});

    test_print(int_list, char_list, str_list, struct_list);
}


void test_insert(TEST_ARGS){
    puts("insert test");
    insert_int(int_list, 1, 5);
    insert_char(char_list, 1, 'A');
    insert_str(str_list, 0, "AHOJ");
    insert_TestStruct(struct_list, 1, (TestStruct){.num = 4, .name = "Fred"});

    test_print(int_list, char_list, str_list, struct_list);
}


void test_pop(TEST_ARGS){
    puts("pop test");
    pop_int(int_list);
    pop_char(char_list);
    pop_str(str_list);
    pop_TestStruct(struct_list);

    test_print(int_list, char_list, str_list, struct_list);
}


void test_remove(TEST_ARGS){
    puts("remove test");
    remove_int(int_list, 1);
    remove_char(char_list, 1);
    remove_str(str_list, 0);
    remove_TestStruct(struct_list, 0);

    test_print(int_list, char_list, str_list, struct_list);
}


void test_print(TEST_ARGS){
    printf("char arr len %ld\n", char_list->len);
    printf("char arr size %ld\n", char_list->size);

    print_list_char(char_list);
    print_list_int(int_list);
    print_list_str(str_list);
    print_list_TestStruct(struct_list);
    
    puts("-------------------------");
}


void test_find(TEST_ARGS){
    puts("find test");
    int FIND_NUM = 5;
    char FIND_CH = 'o';
    char* FIND_ST = "Hello, ";
    TestStruct FIND_STRUCT = {.num = 4, .name = "Angel"}; 

    int int_index = find_int(int_list, FIND_NUM);
    int char_index = find_char(char_list, FIND_CH);
    int str_index = find_str(str_list, FIND_ST);
    int struct_index = find_TestStruct(struct_list, FIND_STRUCT);

    printf("found: int %d at: %d \nchar '%c' at: %d \nstr \"%s\" at: %d\nstruct \"%d\" at: %d\n\n", 
           FIND_NUM, int_index, FIND_CH, char_index, FIND_ST, str_index, FIND_STRUCT.num, struct_index);
    test_print(int_list, char_list, str_list, struct_list);
}

void test_map(TEST_ARGS){
    puts("map test");
    map_int(int_list, multiply);
    map_char(char_list, capitalize);

    test_print(int_list, char_list, str_list, struct_list);
}

void test_filter(TEST_ARGS){
    puts("filter test");
    List* filtered_int = filter_int(int_list, filter_for_int);
    List* filtered_char = filter_char(char_list, filter_for_char);
    List* filtered_str = filter_str(str_list, filter_for_str);
    List* filtered_struct = filter_TestStruct(struct_list, filter_for_struct);

    test_print(filtered_int, filtered_char, filtered_str, filtered_struct);

    list_dtor(&filtered_int);
    list_dtor(&filtered_char);
    list_dtor(&filtered_str);
    list_dtor(&filtered_struct);
}