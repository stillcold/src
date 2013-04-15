#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define Length 31

static void print_first_line(int index_x);
static void print_rest_lines(int line_number);
static void print_monospace_number(int number);

int main(void)
{
    int i;
    int index_x = 0;

    print_first_line(index_x);
    for (i = 1; i < Length; i ++){
        print_rest_lines(i);
    }
    return 0;
}

static void print_monospace_number(int number)
{
    if (number > 99){
        printf("\nThe maximum number is invalid, program exits.\n");
        exit(0);
    }
    /*
     * The statement below will make no sense,
     * I will leave it here, because it makes this program very easy to extend
     * to use maximum 999( by change the 99 above to 999).
     */
    if (number > 99){
        printf("%d", number);
        return;
    }
    if (number > 9){
        printf("%d ", number);
        return;
    }
    printf("%d  ", number);
    return;
}

static void print_first_line(int index_x)
{
    int i;

    for (i = index_x; i < Length; i ++){
        print_monospace_number(i);
    }
    printf("\n");
    return;
}

static void print_rest_lines(int line_number)
{
    int i, j;

    print_monospace_number(line_number);
    if (line_number == 1){
        srand((unsigned) time(NULL));
    }
    for (i = 0; i < Length -1; i++){
        /*
         * Below is better, but slower: 
         * j = (int) (10.0*rand() / (RAND_MAX + 1.0)); 
         *
         */
        j = (int) (10.0*rand() / (RAND_MAX + 1.0));
        /*j = rand() % 10;*/
        print_monospace_number(j);
    }
    printf("\n");
    return;
}
