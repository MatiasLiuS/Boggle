#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <math.h>
#include <string.h>

#include "llist.h"
#include "hashmap.h"

//local function for hashing an input value (do not edit)
unsigned int _hash(hashmap_t * hm, char * val){
  //based on Java's String.hashcode()
  double k = 0;
  double len = (double) strlen(val);
  int i=1;
  for(char * c = val; *c ; c++,i++){
    k += (*c) * pow(31,len-i);
  }
  return (unsigned int) (((unsigned long) k) % hm->num_buckets);
}

//local function: resize the hashmap by doubling the number of buckets and rehashing
void _resize(hashmap_t * hm){
  //TODO: resize the hashmap if the load gets too high
 llist_t ** ob = hm->buckets; //get old buckets and put them in the hashmap
  hm->num_buckets *= 2; //double size
  hm->buckets = calloc(hm->num_buckets, sizeof(hm->buckets)); //allocation
  hm->size = 0;
  llist_t **cur_b = hm->buckets; //rehash
  for (int i = 0; i < hm->num_buckets; i++){
    cur_b[i] = ll_init();
  }
  cur_b = ob;
  for (int i = 0; i < hm->num_buckets/2; i++){
    llist_t *cur = cur_b[i];
    ll_node_t *curNode = cur->head;
    while (curNode != NULL)
    {
      hm_add(hm,curNode->val);
      curNode = curNode->next;
    }
    ll_delete(cur_b[i]);
  }
  free(ob);//free all
}



//initliaze a hashmap with initial number of buckets
hashmap_t * hm_init(){

  //create the hashmap
  hashmap_t * hm = calloc(sizeof(hashmap_t),1);

  //TODO the rest of the setup!
  //add inital buckets
  hm->num_buckets = HM_INIT_NUM_BUCKETS; 
  hm->buckets = calloc(HM_INIT_NUM_BUCKETS, sizeof(hm->buckets)); //allocate
  llist_t **cur_b = hm->buckets; //create the pointer in the buckets
  for (int i = 0; i < hm->num_buckets; i++){
    cur_b[i] = ll_init();
  }
  hm->size = 0; 
  return hm;
}


//delete/deallocate the hashmap
void hm_delete(hashmap_t * hm){

  //TODO: properly deallocate
//delete each hash
  for (int i = 0; i < hm->num_buckets; i++){
    ll_delete(hm->buckets[i]);
  }
  //delete the empty hashmap
  free(hm->buckets);
  //free
  free(hm);
}

//add a string value to the hashmap
void hm_add(hashmap_t * hm, char * val){
  // You get this function for free :) //slay  
  //check the load on the hashtable, if > max load, resize!
  if(((hm->size+1)/(double) hm->num_buckets) > HM_MAX_LOAD){
    _resize(hm); 
  }
  unsigned int h = _hash(hm,val); //get hash
  ll_push(hm->buckets[h],val); //note that list does string dup
  hm->size++; //increase size
}

//see if a string value is in the hashmap
bool hm_check(hashmap_t * hm, char * val){

  //TODO check if a value is in the hashmap
ll_node_t *current = hm->buckets[_hash(hm, val)]->head; 
  while (current != NULL){ //keep comparing all the values until it finds a match unless its not null of course. 
    if (strcmp(current->val,val) == 0){
      return true;
    }
    current = current->next;
  }
  return false; //if no match found then no match is found
}

