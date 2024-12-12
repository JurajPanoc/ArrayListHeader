#include <stdio.h>
#include <stdlib.h>

//default size of the List array
#define DEFAULT_SIZE 10

typedef struct list_h {
    size_t size; // size of the array in memory measured in slots, can change at runtime, defaults to 10
    size_t len; // current amount of items stored in the array
    void* data; //the array itself, contains the items
} List;


List* list_ctor_(size_t type_size){
    List *list = malloc(sizeof(List));
    if(list == NULL) exit(EXIT_FAILURE);
    
    list->data = malloc(type_size * DEFAULT_SIZE);
    if(list->data == NULL) exit(EXIT_FAILURE);
    
    list->size = DEFAULT_SIZE;
    list->len = 0;
    return list;
}

void list_dtor(List **list_ptr){
    free((*list_ptr)->data);
    free(*list_ptr);
    *list_ptr = NULL;
}
