/////////////////////////
// dynamic array list  //
// author: Juraj Panoc //
/////////////////////////

#include <stdlib.h>
#include <stdio.h>

#ifndef __LIST__H //include guarding
#define __LIST__H

#define DEFAULT_SIZE 10 //default list size

//////////////////
// custom types ///////////////////////////////////////////////////////////////////////////////////
//////////////////

//string type (char*) because of the list_"type" naming scheme 
//(list_char* is an invalid typedef name)
#define str char*

///////////////////
// setup and QOL //////////////////////////////////////////////////////////////////////////////////
///////////////////

//this macro has to be used globally before using a list of that type
#define init_list(type) \
typedef struct { \
    size_t size; \
    size_t len; \
    type* data;\
} list_##type;

//alternate syntax for accessing array elements (no name->data[index] needed)
#define iget(name, index) name->data[index]

#define printerr(msg) fprintf(stderr, msg)
////////////////////
// list "methods" /////////////////////////////////////////////////////////////////////////////////
////////////////////

/*
* creates pointer to a struct named list_"type" 
* struct is allocated on the heap that constains the array of items of the type specified,
*/
#define list_ctor(ident, type) \
    list_##type *ident = malloc(sizeof(list_##type)); \
    if(ident == NULL) exit(EXIT_FAILURE);\
    ident->data = malloc(sizeof(type) * DEFAULT_SIZE); \
    if(ident->data == NULL) exit(EXIT_FAILURE);\
    ident->size = DEFAULT_SIZE; \
    ident->len = 0

/*
* deallocates the memory tied to the list that is passed in,
* sets its pointer to NULL to prevent accidental use,
*/
#define list_dtor(list) \
    free(list->data); \
    free(list); \
    list = NULL

/*
* prints out the data that is in the list,
* format_str sets the way it is printed (the way the type is interpretted)
*/
#define print_list(list, format_str) \
    printf("[" format_str ", ", list->data[0]);\
    for(size_t i = 1; i < list->len - 1; i++){ \
        printf(format_str ", ", list->data[i]); \
    } \
    printf(format_str "]\n", list->data[list->len - 1])


/*
* doubles the size of the array and reallocates the memory,
* crashes the program if the reallocation failed

* (uses __typeof__ insted of typeof to avoid compiler warnings)
*/
#define list_reallocator(list) \
    list->size *= 2; \
    list->data = realloc(list->data, list->size * sizeof(__typeof__(list->data[0]))); \
    if(list->data == NULL) exit(EXIT_FAILURE)


/*
* adds an item to the end of the array and increments its length,
* if its about to exceed its size then it reallocs a new bigger array
*/
#define append(list, item) \
    if(list->len >= list->size - 1) { \
        list_reallocator(list); \
    } \
    list->data[list->len++] = item


/*
* pops the last item out and decrements the length variable,
* if the list is empty then it prints "list is empty, cant pop more items" 
  to stderr and crashes the program

  (parentheses are used in the definition so it can return the popped item value
  a.k.a the last line in the definition)
*/
#define pop(list) \
    ({ \
        __typeof__(list->data[0]) popped;\
        if (list->len == 0){ \
            printerr("list is empty, cant pop more items"); \
            exit(EXIT_FAILURE); \
        } \
        popped = list->data[list->len - 1]; \
        list->len--; \
        popped;\
    })

#endif