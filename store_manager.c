// Written by Alvin Lebeck (alvy@cs.duke.edu) 
// adapted from Porter Jones (pbjones@cs.washington.edu)
//
// This is a file for managing a store of various aisles,
// represented by an array of 64-bit integers

#include <stddef.h>  // To be able to use NULL
#include "aisle_manager.h"
#include "store_manager.h"
#include "store_util.h"

// Number of aisles in the store
#define NUM_AISLES 10

// Number of sections per aisle
#define SECTIONS_PER_AISLE 4

// Number of items in the stockroom (2^6 different id combinations)
#define NUM_ITEMS 64

#define NUM_SPACES 10

// Global array of aisles in this store. Each unsigned long in the array
// represents one aisle.
unsigned long aisles[NUM_AISLES];

// Array used to stock items that can be used for later. The index of the array
// corresponds to the item id and the value at an index indicates how many of
// that particular item are in the stockroom.
int stockroom[NUM_ITEMS];


/* Starting from the first aisle, refill as many sections as possible using
 * items from the stockroom. A section can only be filled with items that match
 * the section's item id. Priotizes and fills sections with lower indicies
 * first. Sections with lower indicies should be fully filled (if possible)
 * before moving onto the next section.
 */
void refill_from_stockroom() {
  // TODO: implement this function
  for(int i = 0; i < NUM_AISLES; i++){
    for(int j = 0; j < SECTIONS_PER_AISLE; j++){
      unsigned long id = get_id(aisles[i], j);
      int sItems = stockroom[id];
      if(sItems > 0 && (num_items(aisles[i], j) < NUM_SPACES)){
        add_items(aisles[i], j, sItems);
        if(sItems > NUM_SPACES - num_items(aisles[i], j)){
          stockroom[id] = stockroom[id] - (NUM_SPACES - num_items(aisles[i], j));
        } else {
          stockroom[id] = 0;
        }
      }
    }
  }
}

/* Remove at most num items from sections with the given item id, starting with
 * sections with lower addresses, and return the total number of items removed.
 * Multiple sections can store items of the same item id. If there are not
 * enough items with the given item id in the aisles, first remove all the
 * items from the aisles possible and then use items in the stockroom of the
 * given item id to finish fulfilling an order. If the stockroom runs out of
 * items, you should remove as many items as possible.
 */
int fulfill_order(unsigned short id, int num) {
  // TODO: implement this function
  /*int dubnum = num;
  for (int i = 0; i < NUM_AISLES; i++){
    for (int j = 0; j < SECTIONS_PER_AISLE; j++){
      //if section id = id, remove 
      if (get_id(aisles[i], j) == (unsigned long)id ){
        unsigned short count = num_items( aisles[i], j);
        if (num - count >= 0){
          remove_items( aisles[i], j, count);
          num = num - count;
          
        }
        else{
          remove_items( aisles[i], j, num);
          return dubnum;

        }      
      }
    }
  }
  //num > 0 
  
  while(stockroom[id] > 0 ){
    
    stockroom[id]--;
    num--;
    if (num == 0){
      return dubnum;
    }
    
  }
  return dubnum - num;
  /*

  //outside of loop


  /*int icount = 0;
  for (int i = 0; i<NUM_AISLES; i++){
    for (int j = 0; j < SECTIONS_PER_AISLE){
      if (get_id(aisles[i], j) == (unsigned long)id){
        icount += num_items( aisle[i], j);
      }

    }
  }
  int ret = 0;
  if (icount >= num){
    for (int a  = 0; a<NUM_AISLES; i++){
      for (int b = 0 ; b<SECTIONS_PER_AISLE; b++){
        if (get_id(aisles[i], j) == (unsigned long)id)){
          unsigned short no = num_items(aisle[i], j) ;
          remove_items(aisle[i], j, no);
          ret += no;
      }
    }
  }
  else{

  }
  */

  int count = 0;
  for(int i = 0; i<NUM_AISLES; i++){
    for (int j=0; j<SECTIONS_PER_AISLE; j++){
      unsigned long code = get_id(aisles[i], j);
      unsigned long id1 = id;
      if (code == id1){
        unsigned short spaces = get_spaces(aisles[i], j);
        int a = 0;
        while(num>0 && a < 10){
          unsigned short copy = spaces;
          unsigned short check = (copy >>a) & 0x0001;
          if (check == 1){
            unsigned short var  = 1<<a;
            spaces = spaces &(~var);
            num--;
            count++;

          }
          a++;
        }
        aisles[i] = set_spaces(aisles[i],j, spaces);
      }
    }
  }
  if (num >0){
    if (stockroom[id] > num ){
      count += num;
      stockroom[id] -= num;
      num = 0;

    }
    else {
      count += stockroom[id];
      num -= stockroom[id];
      stockroom[id] = 0;

    }


  }
  return count;


  
}

#ifdef NOT
/* Return a pointer to the first section in the aisles with the given item id
 * that has no items in it or NULL if no such section exists. Only consider
 * items stored in sections in the aisles (i.e., ignore anything in the
 * stockroom). Break ties by returning the section with the lowest address.
 */
unsigned short* empty_section_with_id(unsigned short id) {
  // TODO: implement this function
  return NULL;
}

/* Return a pointer to the section with the most items in the store. Only
 * consider items stored in sections in the aisles (i.e., ignore anything in
 * the stockroom). Break ties by returning the section with the lowest address.
 */
unsigned short* section_with_most_items() {
  // TODO: implement this function
  return NULL;
}
#endif

// Returns the aisle and section index of the first section with the given id 
// that has no items in it.
// Returns -1, -1 if no such section exists.
//
// Breaks ties by returning the section with the lowest aisle index then section index.
struct aisle_section empty_section_with_id(unsigned short id) {
//TODO: implement this function
  struct aisle_section result = {-1,-1};
  return result;
}

// Returns the aisle and section index of the section with the highest inventory in the store.
//
// Breaks ties by returning the section with the lowest aisle index then section index.
struct aisle_section section_with_most_items() {

//TODO: implement this function

  struct aisle_section result = {-1,-1};
  return result;
}
