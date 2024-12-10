/////////////////////////
// dynamic array list  //
// author: Juraj Panoc //
/////////////////////////

#include <stdio.h>
#include <stdlib.h>

#ifndef __LIST__H //include guarding
#define __LIST__H

#define DEFAULT_SIZE 10 //default list size

//////////////////
// custom types ///////////////////////////////////////////////////////////////////////////////////
//////////////////

//List type
typedef struct list_h {
    size_t size; // size of the array in memory, can change at runtime, defaults to 10
    size_t len; // current amount of items stored in the array
    void* data; //the array itself, contains the items 
} List;

//string type (char*) because of the list_"type" naming scheme 
//(list_char* is an invalid typedef name)
typedef char* str;

///////////////////
//      QOL      //////////////////////////////////////////////////////////////////////////////////
///////////////////

//alternate syntax for accessing array elements (no "name->data[index]" needed)
#define iget(name, type, index) (((type*)name->data)[index])

#define printerr(msg) fprintf(stderr, msg)

/////////////////////////
// list base "methods" ////////////////////////////////////////////////////////////////////////////
/////////////////////////

/*
* macro that calls other macros that initialize the base functions for list manipulation
*/
#define add_base_func(type, format_str) \
add_print_list(type, format_str) \
add_append(type) \
add_pop(type) \


/*
* macro that calls a fuction that returns a pointer to a struct named List,
* struct is allocated on the heap that constains the array of items of the type specified,
*/
#define list_ctor(type) list_ctor_(sizeof(type))

List *list_ctor_(size_t type_size);


/*
* deallocates the memory tied to the list that is passed in,
* sets its pointer to NULL to prevent accidental use,
*/
void list_dtor(List **list_ptr);


/*
* prints out the data that is in the list,
* format_str sets the way it is printed (the way the type is interpretted)
*/
#define add_print_list(type, format_str) \
void print_list_##type(List *list){ \
    printf("["); \
    for(size_t i = 0; i < list->len; i++){ \
        printf(format_str, ((type*)list->data)[i]); \
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


#endif //final endif