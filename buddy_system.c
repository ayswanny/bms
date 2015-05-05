#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "buddy_system.h"

int main() {
//variables

    int depth, choice, size, index;

//welcome screen
    clrscr();
    printf("Hello and welcome to bs System Simulator!");
    printf("\n    Please press any key to continue...");
    getch();
    clrscr();

//determine memory size
    printf("First lets specify the size of the system!");
    printf("\nPlease enter any positive integer exponent.");
    printf("\nThis will determine the size of the memory chunk.");
    printf("\nFor example: 6");
    printf("\nThis input would result in 128 bytes");
    printf("\nExponent: ");
    scanf("%d", &depth);

//create memory structure
    struct mem_sys * bs = new_system(depth);

    while(1) {
//menu
        clrscr();
        printf("Main Menu!\n\n");
        printf("(1) - Load a process into memory\n");
        printf("(2) - Remove a process from memory\n");
        printf("(3) - Print the memory block\n");
        printf("(4) - Exit the program\n\n\n");
        printf("Selection: ");
        scanf("%d", &choice);

        switch(choice) {
          case 1:
              clrscr();
              printf("Allocate Memory To Block\n");
              printf("\nPlease enter the size of the process to be loaded in.");
              printf("\nFor example: 4 ");
              printf("\nThis would load a process of 4 bytes into memory");
              printf("\n\nSize of process: ");
              scanf("%d", &size);
              int insert = allocate(bs, size);
              if(insert != -1) {
                  printf("\n\n\nProcess was loaded into index %d", insert);
                  printf("\n\nPress any key to continue...");
              }
              else {
                  printf("\n\n\nThere was an error loading the process into memory");
                  printf("\n\nPress any key to continue...");
              }
              getch();
              getch();
          break;

          case 2:
              clrscr();
              printf("Deallocate Memory From Block\n");
              printf("\nPlease enter the index of the process to be deleted");
              printf("\nFor example: 0 ");
              printf("\nThis would remove a process at the index 0");
              printf("\n\nIndex of process: ");
              scanf("%d", &index);
              int delete = deallocate(bs, index);
              if(delete != -1) {
                  printf("\n\n\nProcess was loaded into index %d", insert);
                  printf("\n\nPress any key to continue...");
              }
              else {
                  printf("\n\n\nThere was an error loading the process into memory");
                  printf("\n\nPress any key to continue...");
              }
              getch();
              getch();
          break;

          case 3:
              clrscr();
              print_memory(bs, 0, 0);
              getch();
              getch();
              break;
          case 4:
            clrscr();
          return 0;

          default:
          break;
      }

  }

}

struct mem_sys {
    int depth;
    int bst[1];
};

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
                return offset_process(index, level, bs->depth);
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

static void set_parent(struct mem_sys * bs, int index) {
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
            return 0;
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

static void merge(struct mem_sys * bs, int index) {
    while(1) {
        int i = index - 1 + (index & 1) * 2;
        if (i < 0 || bs->bst[i] != 0) {
            bs->bst[index] = 0;
            while (((index = (index + 1) / 2 - 1) >= 0) &&  bs->bst[index] == 3){
              bs->bst[index] = 2;
          }
          return;
      }
      index = (index + 1) / 2 - 1;
  }
}

static int is_power_of_two(int n){
    return n && !(n & (n - 1));
}

static int next_power_of_two(int n) {
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

static inline int offset_process(int index, int level, int depth) {
    return ((index + 1) - (1 << level)) << (depth - level);
}

void clrscr()   {
    printf("\033[2J"); // clear
    printf("\033[0,0H"); // move cursor
}

void print_memory(struct mem_sys * bs, int index, int level) {
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
        print_memory(bs, index*2+1, level+1);
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

        }
        print_memory(bs, index*2+2, level+1);

    }

}

char getch()  {
    char c; // This function should return the keystroke
    system("stty raw");    // Raw input - wait for only a single keystroke
    system("stty -echo");  // Echo off
    c = getchar();
    system("stty cooked"); // Cooked input - reset
    system("stty echo");   // Echo on - Reset
    return c;
}