#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "buddy_system.h"

struct mem_sys * new_system (int depth){ 
    int size = 1 << depth; 
    struct mem_sys * bs = malloc(sizeof(struct mem_sys) + sizeof(int) * (size * 2 - 2));
    memset(bs->bst, 0, size*2-1);
    bs->depth = depth;
    return bs;
}

void delete_system(struct mem_sys * bs) {
    free(bs);
}

int allocate(struct mem_sys * bs , int insert) {
    int size;
    if (insert==0) {
        size = 1;
    } else {
        size = next_power_of_two(insert);
    }
    int capacity = 1 << bs->depth;

    if (size > capacity)
        return -1;

    int index = 0;
    int level = 0;

    while (index >= 0) {
        if (size == capacity) {
            if (bs->bst[index] == 0) {
                bs->bst[index] = 1;
                set_parent(bs, index);
                return index;
             }
        } 
        else {
            switch (bs->bst[index]) {
                case 0:
                    bs->bst[index] = 2;
                    bs->bst[index*2+1] = 0;
                    bs->bst[index*2+2] = 0;
                    index = index * 2 + 1;
                    capacity /= 2;
                    level++;
                    continue;
                case 1:
                    break;
                case 2:
                    index = index * 2 + 1;
                    capacity /= 2;
                    level++;
                    continue;
                case 3:
                    break;
                default:
                    //invalid input 
                    break;
            }
        }
        if (index & 1) {
          ++index;
          continue;
        }
        while(1) {
            level--;
            capacity *= 2;
            index = (index+1)/2 -1;
            if (index < 0)
                return -1;
            if (index & 1) {
                ++index;
                break;
            } 
        }
    }
    return -1;
}

void set_parent(struct mem_sys * bs, int index) {
    while(1) {
        int i = index - 1 + (index & 1) * 2;
        if (i > 0 && (bs->bst[i] == 1 || bs->bst[i] == 3)) {
          index = (index + 1) / 2 - 1;
          bs->bst[index] = 3;
      } else {
          return;
      }
  }
}

int deallocate(struct mem_sys * bs, int position) {
    int left = 0;
    int capacity = 1 << bs->depth;
    int index = 0;

    while(1) {
        if(bs->bst[index] == 0) {
            return -1;
        }
        else if(bs->bst[index] == 1) {
            merge(bs, index);
            return index;
        }
        else {
             capacity /= 2;
                if (position < left + capacity) {
                    index = index * 2 + 1;
                } else {
                    left += capacity;
                    index = index * 2 + 2;
                }
        }
    }
}

void merge(struct mem_sys * bs, int index) {
    while(1) {
        int i = index - 1 + (index & 1) * 2;
        if (i < 0 || bs->bst[i] != 0) {
            bs->bst[index] = 0;
            while (((index = (index + 1) / 2 - 1) >= 0) &&  bs->bst[index] == 3){
              bs->bst[index] = 2;
          }
          return;
      }
      bs->bst[index] = 0;
      index = (index + 1) / 2 - 1;
  }
}

int is_power_of_two(int n){
    return n && !(n & (n - 1));
}

int next_power_of_two(int n) {
  if( is_power_of_two(n) ) {
    return n;
  }
  else {
    n |= n>>1;
    n |= n>>2;
    n |= n>>4;
    n |= n>>8;
    n |= n>>16;
    return n+1;
  }
}

void clrscr()   {
    printf("\033[2J"); // clear
    printf("\033[0,0H"); // move cursor
}

/*void print_memory(struct mem_sys * bs, int index, int level) {
    if(bs->depth-1 == level) {
      if(bs->bst[index] == 1) {
            printf("|P:2^%d|", bs->depth-level);
        }
        else if(bs->bst[index] == 0 && bs->bst[index - 1 + (index & 1) * 2] == 1) {
            printf("|E:2^%d|", bs->depth-level);
        }
        else if(bs->bst[index] == 0 && bs->bst[index - 1 + (index & 1) * 2] == 2) {
            printf("|E:2^%d|", bs->depth-level);
        }
        else {

        }
    }    
    else {
        if(bs->bst[index] == 1) {
            printf("|P:2^%d|", bs->depth-level);
        }
        else if(bs->bst[index] == 0 && bs->bst[index - 1 + (index & 1) * 2] == 1) {
            printf("|E:2^%d|", bs->depth-level);
        }
        else if(bs->bst[index] == 0 && bs->bst[index - 1 + (index & 1) * 2] == 2) {
            printf("|E:2^%d|", bs->depth-level);
        }
        else{
          print_memory(bs, index*2+1, level+1);
          print_memory(bs, index*2+2, level+1);
        }

    }

}*/

char getch()  {
    char c; // This function should return the keystroke
    system("stty raw");    // Raw input - wait for only a single keystroke
    system("stty -echo");  // Echo off
    c = getchar();
    system("stty cooked"); // Cooked input - reset
    system("stty echo");   // Echo on - Reset
    return c;
}