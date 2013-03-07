#include "stdio.h"
#include "string.h"
#include "stdarg.h"
int main(){
    char *d;
    char *s = "abcdefgh";
    typedef struct hello{
    int a;
    char *b;
    }h;
    h e;
    printf("%d",(int)sizeof(h));
    printf("%d",(int)sizeof(va_list));
    //memcpy(d,s,sizeof(s));
    //printf("%s\n",d);
    return 0;
}
