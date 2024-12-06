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
    ident->len = 0;

/*
* deallocates the memory tied to the list that is passed in,
* sets its pointer to NULL to prevent accidental use,
*/
#define list_dtor(list) \
    free(list->data); \
    free(list); \
    list = NULL;

/*
* prints out the data that is in the list,
* format_str sets the way it is printed (the way the type is interpretted)
*/
#define print_list(list_ptr, format_str) \
    printf("[" format_str ", ", list_ptr->data[0]);\
    for(size_t i = 1; i < list_ptr->len - 1; i++){ \
        printf(format_str ", ", list_ptr->data[i]); \
    } \
    printf(format_str "]\n", list_ptr->data[list_ptr->len - 1]);


#endif