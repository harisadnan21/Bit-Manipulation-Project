// ----------------------------------------------------------------------------
// Overview
// ----------------------------------------------------------------------------
//  This is a program to keep track of the items in a small aisle of a store.
//
//  A store's aisle is represented by a 64-bit long integer, which is broken
//  into 4 16-bit sections representing one type of item each. Note that since
//  a section is 16-bits, it fits nicely into C's short datatype.
//
//  Aisle Layout:
//
//    Within an aisle, sections are indexed starting with the least-significant
//    section being at index 0 and continuing up until one less than the number
//    of sections.
//
//    Example aisle:
//
//                MSB                                                       LSB
//                  +-------------+-------------+-------------+-------------+
//                  |  Section 3  |  Section 2  |  Section 1  |  Section 0  |
//                  +-------------+-------------+-------------+-------------+
//                  |             |             |             |             |
//      bit offset: 64            48            32            16            0
//
//  Section Layout:
//
//    A section in an aisle is broken into 2 parts. The 6 most significant bits
//    represent a unique identifier for the type of item stored in that
//    section. The rest of the bits in a section (10 least significant)
//    indicate individual spaces for items in that section. For each of the 10
//    bits/spaces, a 1 indicates that an item of the section's type is stored
//    there and a 0 indicates that the space is empty.
//
//    Example aisle section: 0x651A
//
//                MSB                               LSB
//                  +-----------+-------------------+
//                  |0 1 1 0 0 1|0 1 0 0 0 1 1 0 1 0|
//                  +-----------+-------------------+
//                  | item id   | section spaces    |
//      bit offset: 16          10                  0
//
//      In this example, the item id is 0b011001, and there are currently 4
//      items stored in the section (at bit offsets 8, 4, 3, and 1) and 6
//      vacant spaces.
//
//  Written by Alvin Lebeck (alvy@cs.duke.edu) inspired by problems from
//  Porter Jones (pbjones@cs.washington.edu)
// ------------------------------------------------------------------------------------------------

#include "test_util.h"

#define NUM_SPACES 10

// TODO: Fill in these with the correct hex values

// Mask for extracting a section from the least significant bits of an aisle.
// (aisle & SECTION_MASK) should preserve a section's worth of bits at the lower
// end of the aisle and set all other bits to 0
#define SECTION_MASK 0xFFFF

// Mask for extracting the spaces bits from a section
// (section & SPACES_MASK) should preserve all the spaces bits in a section
// and set all non-spaces bits to 0.
#define SPACES_MASK 0x03FF

// Mask for extracting the ID bits from a section
// (section & ID_MASK) should preserve all the id bits in a section
// and set all non-id bits to 0.
#define ID_MASK 0xFC00

// Given a an aisle and a section index.
//
// Returns the section at the given index of the given aisle.
//
// Can assume the index is a valid index (0-3 inclusive)
unsigned long get_section(unsigned long aisle, int index) {
// TODO: Implement this function
  if(index == 0){
    return aisle & SECTION_MASK;
  } else if (index == 1){
    return (aisle >> 16) & SECTION_MASK;
  } else if (index == 2){
    return (aisle >> 32) & SECTION_MASK;
  } else {
    return (aisle >> 48) & SECTION_MASK;
  }
}

// Given an aisle and a section index.
//
// Returns the id of the section at the given index of the given aisle.
// The returned short should have the least 6 significant bits set to the id
// and the 10 most significant bits set to 0.
//
// Can assume the index is a valid index (0-3 inclusive)
unsigned long get_id(unsigned long aisle, int index) {
// TODO: Implement this function
  return get_section(aisle, index) >> 10;
}

// Given an aisle and a section index.
//
// Returns the spaces of the section at the given index of the given aisle.
// The returned short should have the least 10 significant bits set to the spaces
// and the 6 most significant bits set to 0.
//
// Can assume the index is a valid index (0-3 inclusive)
unsigned short get_spaces(unsigned long aisle, int index) {
// TODO: Implement this function
  return get_section(aisle, index) & SPACES_MASK;
}

// Given an aisle, a section index, and a short representing a 
// new bit pattern to be used for section.
//
// Sets the section at the given index of the given aisle to
// to the new bit pattern.
//
//Return the updated aisle
//
// Can assume the index is a valid index (0-3 inclusive)

// Alternative solution w/shifting
unsigned long set_section(unsigned long aisle, int index, unsigned short new_section) {
  // TODO: Implement this function
  unsigned long number_with_middle_zeros = ~((unsigned long)SECTION_MASK << (index * 16)) ;
  
  unsigned long n2 = number_with_middle_zeros & aisle;
  unsigned long number_with_section_only= ((unsigned long)new_section<<(index *16));
  

  unsigned long ret = n2 | number_with_section_only;
  
  //unsigned long ret = 0;
  //ret = ret | get_section(aisle, index)
  return  ret;
  
}

// Given an aisle, a section index, and a short representing a 
// new bit pattern to be used for the id of the section.
//
// Sets the id for the section at the given index of the given aisle to
// to the new bit pattern. The new id will be in the least significant bits
// of the given bit pattern. If the new bit pattern does not fit in 6 bits,
// then the method should leave the id unchanged.
//
// Can assume the index is a valid index (0-3 inclusive)
unsigned long set_id(unsigned long aisle, int index, unsigned short new_id) {
// TODO: Implement this function
  if(new_id > 63){
    return aisle;
  }
  return ((~((unsigned long)ID_MASK << (index * 16)) & aisle) | (((long)new_id) << (index * 16 + 10)));
}

// Given an aisle, a section index, and a short representing a 
// new bit pattern to be used for the spaces of the section.
//
// Sets the spaces for the section at the given index of the given aisle to
// to the new bit pattern. The new spaces pattern will be in the least significant bits
// of the given bit pattern. If the new bit pattern does not fit in 10 bits,
// then the method should leave the spaces unchanged.
//
// Can assume the index is a valid index (0-3 inclusive)
unsigned long set_spaces(unsigned long aisle, int index, unsigned short new_spaces) {
// TODO: Implement this function
  if(new_spaces >> 10 != 0){
    return aisle;
  }
  return ((~((unsigned long)SPACES_MASK << (index * 16)) & aisle) | (((long)new_spaces) << (index * 16)));
}

// Given an aisle and a section index.
// 
// Returns the number of items in the section 
// at the given index of the given aisle.
//
// Can assume the index is a valid index (0-3 inclusive)
unsigned short num_items(unsigned long aisle, int index) {
// TODO: Implement this function
  unsigned short count = 0;
  for(int i = 0; i < 10; i++){
      count += 0x0001 & (get_spaces(aisle, index) >> i);
  }
  return count;
}


// Given an aisle, a section index, and the desired
// number of items to add.
//
// Add at most the given number of items to the section at the given index in the
// given aisle. Items should be added to the least significant spaces possible.
// If a given n is larger than or equal to the number of empty spaces in the 
// section, then the section should appear full after the method finishes.
// 
// Return the updated aisle
//
// Can assume the index is a valid index (0-3 inclusive)
unsigned long add_items(unsigned long aisle, int index, int n) { 
// TODO: Implement this function
  //Check if num_items>n
  int zero_count= 0;
  unsigned short spaces = get_spaces(aisle, index);
  
  for(int i = 0; i < 10; i++){
    unsigned short lsbit = spaces & (0x0001<<i);
    if (lsbit == 0 && zero_count < n){
      spaces = spaces | (0x0001<<i);
      zero_count++;
    }
    
  }
  

  return set_spaces(aisle, index, spaces);
}

// Given an aisle, a section index, and the desired
// number of items to remove.
//
// Remove at most the given number of items from the section at the given index in the
// given aisle. Items should be removed from the least significant spaces possible.
// If a given n is larger than or equal to the number of items in the 
// section, then the section should appear empty after the method finishes.
//
// Return the updated aisle
//
// Can assume the index is a valid index (0-3 inclusive)
unsigned long remove_items(unsigned long aisle, int index, int n) {
// TODO: Implement this function

  int count= 0;
  unsigned short spaces = get_spaces(aisle, index);
  
  for(int i = 0; i < 10; i++){
    unsigned short lsbit = spaces & (0x0001<<i);
    if (lsbit != 0 && count < n){
      spaces = spaces ^ (0x0001<<i);
      count++;
    }
    
  }
  

  return set_spaces(aisle, index, spaces);

}

// Given an aisle, a section index, and a space index.
//
// Toggle the item in the given space index of the section at 
// the given section index in the given aisle.
//
// Toggling means that if the space was previously empty, it should now be filled with an item, 
// and if the space was previously filled it should now be empty.
//
// Can assume the section index is a valid index (0-3 inclusive)
// Can assume the spaces index is a valid index (0-9 inclusive)
unsigned long toggle_space(unsigned long aisle, int section_index, int space_index) {
// TODO: Implement this function
  unsigned short spaces = get_spaces(aisle, section_index);
  for(int i = 0; i < 10; i++){
    unsigned short g = 0x0001 << i;
    if (i == space_index){
      if (((spaces & g)>>i)== 1){
        spaces = ((~g) & spaces);
      }
      else{
        spaces = (g | spaces);

      }
    }

  }

  return set_spaces(aisle, section_index, spaces);
}

// Given an aisle, a section index, and a number
// of slots to rotate by.
//
// Rotate the items in the section at the
// given index of the given aisle to the left by the given number of slots
//
// For example, if the spaces are 0b0111100001, then rotating
// left by 2 results in the spaces 0b1110000101
//
// Can assume the index is a valid index (0-3 inclusive)
// NOTE: do not assume n < NUM_SPACES 
// (hint: think about what rotating by a value >= NUM_SPACES is equivalent to)
unsigned long rotate_items_left(unsigned long aisle, int index, int n) {
// TODO: Implement this function
  unsigned short spaces = get_spaces(aisle,index);
  if (n < 10){
    spaces = ((spaces<<n) & SPACES_MASK) | ((spaces>> (10 - n)) & SPACES_MASK);
  }
  else{
    int rem = n % 10;
    spaces = ((spaces<<rem) & SPACES_MASK) | ((spaces>> (10 - rem)) & SPACES_MASK);

  }
  return set_spaces(aisle, index, spaces);
}

// Given an aisle, a section index, and a number
// of slots to rotate by.
//
// Rotate the items in the section at the
// given index of the given aisle to the right by the given number of slots
//
// For example, if the spaces are 0b1000011110, then rotating
// right by 2 results in the spaces 0b1010000111
//
// Return the updated aisle.
//
// Can assume the index is a valid index (0-3 inclusive)
// NOTE: do not assume n < NUM_SPACES 
// (hint: think about what rotating by a value >= NUM_SPACES is equivalent to)
unsigned long rotate_items_right(unsigned long aisle, int index, int n) {
// TODO: Implement this function
  unsigned short spaces = get_spaces(aisle,index);
  if (n < 10){
    spaces = ((spaces>>n) & SPACES_MASK) | ((spaces<< (10 - n)) & SPACES_MASK);
  }
  else{
    int rem = n % 10;
    spaces = ((spaces>>rem) & SPACES_MASK) | ((spaces<< (10 - rem)) & SPACES_MASK);

  }
  return set_spaces(aisle, index, spaces);
  return 0;
}

