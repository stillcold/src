#include "myalgorithm.h"
#include "mytools.h"
#include "mytypes.h"
#include "sys/time.h"

#include <stdio.h>

void init(void);

u32                         i;
extern int                  heap[HEAP_MAX_SIZE];
int                         array[HEAP_MAX_SIZE];
struct timeval              time_count;

void init(void){
    /* Init heap */
    for (i = 1; i < HEAP_MAX_LENGTH; i++){
        array[i] = heap[i] = get_rand_number((HEAP_MAX_LENGTH - 1) * 10);
    }
    /*dp-demo*/
    init_dp_array();
}

int main(void){

    init();

#ifdef DEBUG_MODE
    print_heap(HEAP_MAX_LENGTH);
#endif

    /* Heap sort */
    mark_start();
    heap_sort(HEAP_MAX_LENGTH);
    mark_stop();
    get_time_difference(&time_count);

    printf("Time taken by heap sort: %d\n",(int)time_count.tv_usec);

#ifdef DEBUG_MODE
    print_heap(HEAP_MAX_LENGTH);
#endif

#ifdef DEBUG_MODE
    printf("Sort with bitmap.\n");
#endif

    /* Bitmap sort algorithm */
    mark_start();
    for (i = 1; i < HEAP_MAX_LENGTH; i++){
        set_bit_in_map((unsigned)array[i]);
    }
    mark_stop();
    get_time_difference(&time_count);

    printf("Time taken by bitmap sort: %d\n",(int)time_count.tv_usec);

#ifdef DEBUG_MODE
    show_bitmap();
    for (i = 1; i < MAP_MAX_LENGTH; i++){
        if (check_bit_in_map(i)){
            printf("%u\t", i);
        }
    }
    printf("\n");
#endif

    /* Algorithm: dp */
    printf("This is dp result: %d\n", dp_demo(5));

    return 0;
}
