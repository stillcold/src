#include <stdio.h>

#define Length 26

void print_first_line(int);
void print_rest_lines();

int main(void)
{
    int index_x = 0;
    print_first_line(index_x);
    return 0;
}

void print_first_line(int index_x)
{
    int i;
    for (i = index_x; i < Length; i ++){
        printf("%d   ", i);
    }
    printf("\n");
    return;
}

void print_rest_lines()
{

}
