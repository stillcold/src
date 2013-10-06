#include "mytypes.h"
#include "mystatus.h"
#include "myalgorithm.h"
#include "mytools.h"
#include "sys/time.h"

#include <stdio.h>
#include <math.h>
#include <string.h>

void init_heap_and_dp(void);
void test_aritificial_neural_network(void);
void test_manacher(void);

u32                         i;
extern int                  heap[HEAP_MAX_SIZE];
extern boolean              is_end;
int                         array[HEAP_MAX_SIZE];
struct timeval              time_count;
extern double               sum_of_error_per_round;

void init_heap_and_dp(void){
    /* Init heap */
    for (i = 1; i < HEAP_MAX_LENGTH; i++){
        array[i] = heap[i] = get_random_number((HEAP_MAX_LENGTH - 1) * 10);
    }
    /*dp-demo*/
    init_dp_array();
}

int main(void){

    init_heap_and_dp();

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

    /* Algorithm: BP(artificial network) */
    test_aritificial_neural_network();

    /* Algorithm: manacher */
    test_manacher();

    return 0;
}

void test_aritificial_neural_network(void){
    u32                     i;
    double                  fan_in;
    boolean                 successed = FALSE;

    initiate_neural_network();
    for (i = 0; i < MAX_LOOP_TIMES; i++){
        train_neural_network();
        if (sum_of_error_per_round < TARGET_ERROR_VALUE){
            successed = TRUE;
            break;
        }
        if ((i & 2047) == 0)
            printf("Variance of diff between real and desired : %f\n",
                    sum_of_error_per_round);
        get_delta();
        modify_network_weight();
    }
    if (successed){
        while (TRUE){
            printf("Input the number to be calculated. ");
            printf("0 for terminated, number should between 0 and 1.\n");
            scanf("%lf", &fan_in);
            if (fan_in){
                if ((fan_in > 0) && (fan_in < 1))
                    printf("Input: %f, desired: %f, real: %f\n",
                            fan_in, proceed(fan_in), cos(fan_in));
                else
                    printf("Invalid input, should between 0 and 1.\n");
            }
            else
                break;
        }
    } else {
        printf("Error! Difference between real output and desired: %f\n",
                sum_of_error_per_round);
    }
}

void test_manacher(void){
    register int i;
    int ret;

    while(scanf("%s", original_manacher_str) != EOF)
    {
        manacher_length = strlen(original_manacher_str);
        init_manacher();
        manacher_do();
        ret = 0;
        for (i = 0; i < manacher_length; i++)
            if (manacher_result[i] > ret)
                ret = manacher_result[i];
        printf("%d\n", ret - 1);
    }
}
