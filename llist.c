#include <stdlib.h>
#include <string.h>

#include "llist.h"

//initialize a linked list
llist_t * ll_init(){
  //TODO
  llist_t * llist= malloc(sizeof(llist_t));//allocate
  llist->head = NULL; //create head
  llist->size = 0; //create the size
  return llist; //return the list if not null
}

//delete a linked list
void ll_delete(llist_t * ll){
   //TODO
  ll_node_t *cur= ll->head; //go to head
  while (cur != NULL){ //go until last value is pointing to null
    free(cur->val); //free memoryt
    ll_node_t *next = cur->next;
    free(cur); //free memory
    cur = next; 
  }
  free(ll); //free the empty list
}


//push an item onto the front of the list
void ll_push(llist_t * ll, char * s){
  //TODO
  ll_node_t *cur = malloc(sizeof(ll_node_t)); //allocate
  cur->val = strdup(s); 
  cur->next = ll->head;
  ll->head = cur; //set head to current
  ll->size++; //increase size
}




