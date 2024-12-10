#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_SIZE 10

typedef struct list_h {
    size_t size; // size of the array that is currently allocated
    size_t len; // "length" of the array, count of how many items are stored
    void* data; // the array itself (a void*)
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