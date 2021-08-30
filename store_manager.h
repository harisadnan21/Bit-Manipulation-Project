// Written by Alvin Lebeck (alvy@cs.duke.edu) 
// adapted from Porter Jones (pbjones@cs.washington.edu)

#ifndef _FLEET_MANAGER_H
#define _FLEET_MANAGER_H

extern unsigned long aisles[];
extern int stockroom[];

struct aisle_section {
    int aisle_index, section_index;
};

// Function definitions for the store client
void refill_from_stockroom();
int fulfill_order(unsigned short id, int num);
struct aisle_section empty_section_with_id(unsigned short id);
struct aisle_section section_with_most_items();
void refill_from_stockroom_sol();
int fulfill_order_sol(unsigned short id, int num);
struct aisle_section empty_section_with_id_sol(unsigned short id);
struct aisle_section section_with_most_items_sol();

#endif // _FLEET_MANAGER_H
