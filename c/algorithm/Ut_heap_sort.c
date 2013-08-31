#include "myalgorithm.h"

static void adjust_heap(int index, int length);
static void construct_heap(int length);

int                         heap[HEAP_MAX_LENGTH];

void heap_sort(int length){
    register int            i;

    construct_heap(length);

    for (i = length; i > 1; i --){
        heap[i-1] += heap[0];
        heap[0] = heap[i-1] - heap[0];
        heap[i-1] -= heap[0];
        adjust_heap(0, i-1);
    }
}

/**************************************************************************
 *
 * This functon will construct a heap.
 *
 * I will put bigger numbers on the top of the heap.
 *
 *************************************************************************/

static void construct_heap(int length){
    register int            i;
    for (i = length - 1; i >= 0; i--){
        adjust_heap(i, length);
    }
}

/**************************************************************************
 *
 * This functon will focus on one element pointed by index, it can't adjust
 * the whole heap, it can only put that element to its right place.
 * 
 * So, it
 * can at least adjust 3 elements every time(i.e, a small tree). So, keep
 * invoking this functin can adjust the whole heap.
 *
 *************************************************************************/

static void adjust_heap(int index, int length){
    /* This is the key element, for the main purpuse is to adjust it */
    int                     current = heap[index];
    int                     i = index << 1; /* God, this is index, too */
    int                     done = 0;

    while((done != 0) && (i < length)){
        if (heap[i] < heap[i+1]){
            i++;
        }

        if (current > heap[i]){
            done = 1;
        } else {
            heap[i/2] = heap[i];
            i <<= 1;
        }
    }

    heap[i>>=1] = current;
}
