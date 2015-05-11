#ifndef BUDDY_SYSTEM
#define BUDDY_SYSTEM

struct mem_sys {
    int depth;
    int bst[1];
};

struct mem_sys * new_system(int level);
void delete_system(struct mem_sys *);
int allocate(struct mem_sys *, int size);
void set_parent(struct mem_sys *, int);
int deallocate(struct mem_sys *, int);
void merge(struct mem_sys *, int);
int next_power_of_two(int);
int is_power_of_two(int);
void print_memory(struct mem_sys *, int, int);
void clrscr();
char getch();

#endif