#ifndef BUDDY_SYSTEM
#define BUDDY_SYSTEM

struct mem_sys;

struct mem_sys * new_system(int level);
void delete_system(struct mem_sys *);
int allocate(struct mem_sys *, int size);
static void set_parent(struct mem_sys *, int);
int deallocate(struct mem_sys *, int);
static void merge(struct mem_sys *, int);
static int next_power_of_two(int);
static int is_power_of_two(int);
static int offset_process(int, int, int);
void print_memory(struct mem_sys *, int, int);
void clrscr();
char getch();

#endif