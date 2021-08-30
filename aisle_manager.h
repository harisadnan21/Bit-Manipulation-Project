// Written by Alvin Lebeck (alvy@cs.duke.edu) 
// adapted from Porter Jones (pbjones@cs.washington.edu)

#ifndef _AISLE_MANAGER_H
#define _AISLE_MANAGER_H

// Function definitions for the aisle manager
unsigned short get_section(unsigned long aisle, int index);
unsigned short get_id(unsigned long aisle, int index);
unsigned short get_spaces(unsigned long aisle, int index);
unsigned long set_section(unsigned long aisle, int index, unsigned short new_section);
unsigned long set_id(unsigned long aisle, int index, unsigned short new_id);
unsigned long set_spaces(unsigned long aisle, int index, unsigned short new_spaces);
unsigned short num_items(unsigned long aisle, int index);
unsigned long add_items(unsigned long aisle, int index, int n);
unsigned long remove_items(unsigned long aisle, int index, int n);
unsigned long toggle_space(unsigned long aisle, int index, int space_index);
unsigned long rotate_items_left(unsigned long aisle, int index, int n);
unsigned long rotate_items_right(unsigned long aisle, int index, int n);

#endif // _AISLE_MANAGER_H
