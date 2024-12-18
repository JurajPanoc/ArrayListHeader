/////////////////////////
// dynamic array list  //
// author: Juraj Panoc //
/////////////////////////

#include <stdio.h>
#include <stdlib.h>

#ifndef __LIST__H //include guarding
#define __LIST__H

#define DEFAULT_SIZE 10 //default List size

//////////////////
// custom types ///////////////////////////////////////////////////////////////////////////////////
//////////////////

//List type
typedef struct list_h {
    size_t size; // size of the array in memory, can change at runtime, defaults to 10
    size_t len; // current amount of items stored in the array
    void* data; //the array itself, contains the items 
} List;

//string type (char*) because of the "function name"_"type" naming scheme 
//(for example: append_char*() is an invalid function name)
typedef char* str;

///////////////////
//      QOL      //////////////////////////////////////////////////////////////////////////////////
///////////////////

//alternate syntax for accessing array elements (no "((type*)name->data)[index]" needed)
#define iget(name, type, index) (((type*)name->data)[index])

//prints an error message to stderr 
#define printerr(msg) fprintf(stderr, msg "\n")

/////////////////////////
// list base "methods" ////////////////////////////////////////////////////////////////////////////
/////////////////////////

/*
 * macro that calls other macros that initialize the base functions for list manipulation,
 * type is the type of data you would like to store,
 * format_str is a string that determines how the array will be printed (formatting just like in printf),
 * cmp_func is a function pointer that determines how the arrays content will be compared (example: strcmp() in <string.h>)
*/

#define add_base_func(type, format_str, cmp_func) \
add_print_list(type, format_str) \
add_append(type) \
add_pop(type) \
add_insert(type) \
add_remove(type) \
add_find(type, cmp_func) \
add_map(type) \
add_filter(type) \


/*
 * macro that calls a fuction that returns a pointer to a struct named List,
 * struct is allocated on the heap that constains the array of items of the type specified,
 */
#define list_ctor(type) list_ctor_(sizeof(type), DEFAULT_SIZE)

List *list_ctor_(size_t type_size, size_t size);


/*
 * deallocates the memory tied to the list that is passed in,
 * sets its pointer to NULL to prevent accidental use
 */
void list_dtor(List **list_ptr);


/*
 * prints out the data that is in the list,
 * printf_macro sets the way it is printed (gets called with the index as a parameter)
 */
#define add_print_list(type, printf_macro) \
void print_list_##type(List *list){ \
    printf("["); \
    for(size_t i = 0; i < list->len; i++){ \
        printf_macro(i); \
        printf(", "); \
    } \
    printf("]\n"); \
}


/*
 * macro that doubles the size of the array and reallocates the memory,
 * crashes the program if the reallocation failed
 */
#define list_reallocator(list, type) \
    list->size *= 2; \
    list->data = realloc(list->data, list->size * sizeof(type)); \
    if(list->data == NULL) exit(EXIT_FAILURE);


/*
 * adds an item to the end of the array and increments its length,
 * if its about to exceed its size then it reallocs a new bigger array
   and updates its pointer to point to the new array
*/
#define add_append(type) \
void append_##type(List *list, type item){ \
    if(list->len >= list->size - 1) { \
        list_reallocator(list, type) \
    } \
    ((type*)list->data)[list->len++] = item; \
}


/*
 * pops the last item out and decrements the length variable,
 * if the list is empty then it prints "list is empty, cant pop more items" 
   to stderr and crashes the program
*/
#define add_pop(type) \
type pop_##type(List *list){ \
    if (list->len == 0){ \
        printerr("List is empty, can't pop more items"); \
        exit(EXIT_FAILURE); \
    } \
    list->len--; \
    return ((type*)list->data)[list->len]; \
}


/*
 * inserts an item into the array at the index that is passed in
   and pushes all of the items in front of it,
 * if you pass in an index thats out of range it throws an error and kills the program
 * if you want to add to the end of the list use append_"type" instead
 */
#define add_insert(type) \
void insert_##type(List* list, const unsigned int index, const type item) { \
    if(index > list->len - 1) { \
        printerr("Invalid insert operation, index out of range"); \
        exit(EXIT_FAILURE); \
    } \
    if(list->size <= list->len) { \
        list_reallocator(list, type) \
    } \
    for(size_t i = list->len - 1; i + 1 > index; i--) { \
        ((type*)list->data)[i + 1] = ((type*)list->data)[i]; \
    } \
    ((type*)list->data)[index] = item; \
    list->len++; \
}


/*
 * removes an item at the give index and moves all of the items to fill in the gap left behind
 * if you pass in an index thats out of range it throws an error and kills the program
 */
#define add_remove(type) \
void remove_##type(List* list, const unsigned int index) { \
    if(index > list->len - 1) { \
        printerr("Invalid remove operation, index out of range"); \
        exit(EXIT_FAILURE); \
    } \
    for(size_t i = index; i + 1 < list->len; i++) { \
        ((type*)list->data)[i] = ((type*)list->data)[i + 1]; \
    } \
    list->len--; \
}

/*
 * finds the item that is passed in according to the criteria defined in the cmp_func,
 * returns the items index,
 * if not found returns -1
 */
#define add_find(type, cmp_func) \
int find_##type(List* list, type item) { \
    for(size_t i = 0; i < list->len; i++) { \
        if (cmp_func(iget(list, type, i), item) == 0){ \
            return i; \
        } \
    } \
    return -1; \
}


#define add_map(type) \
void map_##type(const List* list, void(*func)(type*)) { \
    for(size_t i = 0; i < list->len; i++) { \
        func(&iget(list, type, i)); \
    } \
}


/*
 * creates a new list that contains the items that satisfy the condition criteria,
 * returns a pointer to the new list
 */
#define add_filter(type) \
List* filter_##type(List* list, int(*condition)(type)) { \
    List* res = list_ctor_(sizeof(type), list->len); \
    for(size_t i = 0; i < list->len; i++){ \
        if(condition(iget(list, type, i))) { \
            iget(res, type, res->len) = iget(list, type, i); \
            res->len++; \
        } \
    } \
    return res; \
}

#endif //final endif