#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "buddy_system.h"

struct mem_sys* bs;


/*
  - Test suite for buddy_system.c
  - Testing all functions except those
  - in which test would be trivial. 
  - Functions not tested:
  - delete_system() - simple a free() function of a struct
  - print_memory() - this function is no longer used
  -                 since gui has been developed.
  - getch() - this function is no longer user since
  -           since gui has been developed.
  - clrscr() - this function is no longer user since
  -           since gui has been developed.
*/

/*  test_new_system() testing new_system() of buddy_system.c
 -  Function tests the creation of a struct mem_sys.
 -  This pass an integer of 5, and assert this value
 -  has been passed into the depth variable of the struct.
 -  It will also check indices to ensure all indices
 -  of array are set to 0 as done in new_system().
*/ 

void test_new_system() {
  bs = new_system(5);
  assert(bs->depth == 5);
  for(int i = 0; i < 32; i++) {
    assert(bs->bst[i] == 0);
  }
}

/* test_allocate() testing allocate() of buddy_system.c
 -  Function will test the insertion of several processes.
 -  
 -  The function allocate() should only return -1 upon reaching
 -  a case in which a process could not be insert due to:
 -  size of process is greater than maximum memory
 -  there isn't enough space left in the system to allocate
 -
*/

void test_allocate() {
  int test = allocate(bs, 33); // test inserting over the limit
  assert(test == -1);
  
  test = allocate(bs, 4);
  assert(test != -1);
  test = allocate(bs, 4);
  assert(test != -1);     // test some inserts...
  test = allocate(bs, 8);
  assert(test != -1);
  test = allocate(bs, 8);
  assert(test != -1);
  test = allocate(bs, 8);
  assert(test != -1);     // at this point the system is full
  
  test = allocate(bs, 4);     // test at this point should all 
  assert(test == -1);     // fail.
  test = allocate(bs, 8);
  assert(test == -1);
}

/*
  - test_deallocate will test deallocate() of buddy_system.c
  -
  - deallocate() will return -1 if nothing is to be deleted
  - from specified index. Otherwise, the function will return
  - the index from which it was deleted.
  -
  - the test will delete several nodes inserted in test_allocate
  - and ensure the indices after deallocate() runs are equal
  - to 0, or an empty space.
*/

void test_deallocate() {
  int test = deallocate(bs, 0);
  assert(test != -1);
  assert(bs->bst[test] == 0);
  test = deallocate(bs, 4);
  assert(test != -1);
  assert(bs->bst[test] == 0);
  test = deallocate(bs, 24);
  assert(bs->bst[test] == 0);

}

/* test_merge will test merge() of buddy_system.c
 * merge will be called upon running the function deallocate
 * once a process is found which can be removed, merge will
 * be called on that index. the function will test whether its
 * sibling node is being used, if not, it will merge the parent
 * node
 */

void test_merge() {
  assert(bs->bst[3] == 0); // ensure that the deallocates
                           // from test_deallocate produced
                           // produced a merge at index 3


  assert(bs->bst[1] == 2); // ensure that the index, with a free node at 3 
                         // and a full node at 4, is marked as split

  deallocate(bs, 8);       // deallocate the space from node four

  assert(bs->bst[1] == 0); // now we look to find if the previously split node
                           // has now been marked as empty since its last
                           // remaining child has been removed.

  assert(bs->bst[0] == 2); // for out last remaining process in this structure
  assert(bs->bst[2] == 2); // at index 5, we want to ensure that the parent of 
                           // index 5 (index 2) is split and the parent of index 2 
                           // (the root or index 0) is split as well

  deallocate(bs, 16);      // remove the remaining space from the node
  assert(bs->bst[2] == 0); // ensure the merge resets the parent node to empty
  assert(bs->bst[0] == 0); // ensure tha merge recursively traverses the tree so root
                           // is empty
}

/*
- test_next_power_of_two testing next_power_of_two()
- 
-
-
*/
void test_next_power_of_two () {
  int test = next_power_of_two(3);
  assert(test == 4);
  test = next_power_of_two(7);
  assert(test == 8);
  test = next_power_of_two(15);
  assert(test == 16);
  test = next_power_of_two(17);
  assert(test == 32);
  test = next_power_of_two(36);
  assert(test == 64);
}

void test_is_power_of_two() {
  int test = is_power_of_two(2);
  assert(test == 1);
  test = is_power_of_two(8);
  assert(test == 1);
  test = is_power_of_two(32);
  assert(test == 1);
  test = is_power_of_two(128);
  assert(test == 1);


}

// main function for test.
int main(int argc, char **argv) {
  test_new_system();
  test_allocate();
  test_deallocate();
  test_merge();
  test_next_power_of_two();
  test_is_power_of_two();
  printf("All tests completed. No error founds.");
  return 0;
}