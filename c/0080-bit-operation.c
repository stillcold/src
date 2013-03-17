#include "stdio.h"
#define MAX_NUM 2
static int make_number(int number){
    switch (number){
    case (0): return 5;
    case (1): return 9;
    case (2): return 87;
}
}
int main(){
    int i;
    for(i = 0; i < 3; i ++){
        printf("%*d",8,(make_number(i) & MAX_NUM-1));
    }

}
