/** @file list.c
 *  Definition file for list.h
 *  Docs in list.h
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

list_t* create_empty_list(){
    // Assign the list pointer to initList
    list_t *list = (list_t*)malloc(sizeof(list_t));
    // test if memory allocated correctly
    if(list == NULL){
        printf("Memmory was not allocated correctly\n");
        exit(1);
    } else {
        // set headPtr = Null
        list ->headPtr = NULL;
        // initialize itemCount to 0
        list -> itemCount = 0;

        return list;
    }   
}

void printList(list_t * list){
    node_t *curPtr = list -> headPtr;
    for(int i = 0; i < list -> itemCount; ++i){

        printf("%s\n", curPtr -> string);
        curPtr = curPtr -> next;
    }
}

void add(list_t* list, char* elem){
    // new node
    node_t *new = (node_t*)malloc(sizeof(node_t));

    if(new == NULL){
        printf("Memmory was not allocated correctly\n");
        exit(1);
    } else {
        new -> next = NULL;
        new -> string = elem;
        
        // if list empty headptr = new
        if(list -> headPtr == NULL){
           list -> headPtr = new;
           // increment itemcount
           list ->itemCount = 1;
        } else {
            // start at the head ptr
           node_t *curPtr = list->headPtr;
            // iterate through list until find end
            while(curPtr -> next != NULL){
                curPtr = curPtr -> next;
            }
            curPtr -> next = new;
            // increment itemcount
            list ->itemCount = 1 + (list -> itemCount);
        }
    }
}

void add_at(list_t* list, char* elem, int i){
    if(i >= list -> itemCount){
        printf("index out of range\n");
        exit(0);
    } else {
        node_t *curPtr = list -> headPtr;
        node_t *prevPtr = NULL;

        for(int pos = 0; pos < i; pos++){
            prevPtr = curPtr;
            curPtr = curPtr -> next;
        }
        node_t *new = (node_t*)malloc(sizeof(node_t));
        if(new == NULL){
            printf("Memmory was not allocated correctly\n");
            exit(1);
        } else {
            new -> string = elem;
            new -> next = curPtr;
            prevPtr -> next = new;
            // increament item count
            list ->itemCount = 1 + (list -> itemCount);
        }
    }   
}

char* remove_at(list_t* list, int i){
    // because indexes start at itemCount -1
    if(i >= list -> itemCount){
        return NULL;
    } else {
        node_t * curPtr = list -> headPtr;
        node_t * prevPtr = NULL;
        for(int pos = 0; pos < i; ++pos){
            prevPtr = curPtr;
            curPtr = curPtr -> next;
        }
        // removing end
        if(curPtr -> next == NULL){
            char * string = curPtr -> string;
            free(curPtr);
            prevPtr -> next = NULL;
            list -> itemCount = list -> itemCount - 1;
            return string;

        } else if( i == 0){ // removing start
            prevPtr = curPtr;
            curPtr = curPtr -> next;
            list -> headPtr = curPtr;
            char *string = prevPtr -> string;
            free(prevPtr);
            list -> itemCount = list -> itemCount - 1;
            return string;

        } else { // removing middle
            prevPtr -> next = curPtr -> next;
            char * string = curPtr -> string;
            free(curPtr);
            list -> itemCount = list -> itemCount - 1;
            return string;
        }
    }
}

char* get(list_t* list, int i){
    if(i >= list -> itemCount){
        return NULL;
    } else {
        node_t * curPtr = list -> headPtr;
        for(int pos = 0; pos < i; ++pos){
            curPtr = curPtr -> next;
        }
        return curPtr -> string;
    }
}

int size(list_t* list){
    return list -> itemCount;
}

void clear(list_t* list){
    node_t * prevPtr = NULL;
    node_t * curPtr = list -> headPtr;
    while(curPtr != NULL){
        prevPtr = curPtr;
        curPtr = curPtr -> next;
        list -> headPtr = curPtr;
        free(prevPtr);
        list -> itemCount = list -> itemCount - 1;
    }
}

void destroy_empty_list(list_t* list){
    free(list);
}