#include <stdio.h>
#include <string.h>
#include <malloc.h>

/*
 * This code is first used to test the usage of malloc, but I am confused
 * when I want to generate an error report, seems that strcpy(des, src) can 
 * work when des doesn't have enought space for src(see the code below).
 */

typedef struct v1
{
    char Command[80];
    int Index;
}v1;

typedef struct v2
{
    int Index;
    char *Command;
}v2;

static v1 b1[5];
static v2 b2[5];

int main(void)
{
    char *str1 = "this is string1";
    char *str2 = "123456789";
    char *str3 = "this is string 3, and much longger than string 2.";
    char str4[10];
    char *str5 = "12345678901234567890";
    int length2;
    /*int length3;*/

    printf("The length of str4: %d\tstr5: %d\n", (int)sizeof(str4),
            (int)sizeof(str5));

    /*
     * free is somehow can't work.
     */
    /*free(str5);*/
    str5 = (char *)malloc(12);

    printf("The length of str5 after free is: %d\n",(int)sizeof(str5));

    strcpy(b1[1].Command, str1);

    length2 = strlen(str2);
    /*length3 = strlen(b2[1].Command);*/
    
    b2[1].Command = (char *)malloc(sizeof(char)*length2);
    strcpy(b2[1].Command, str2);

    printf("%s\n%s\n", b1[1].Command, b2[1].Command);

    /* 
     * free(b2[1].Command); 
     * length3 = strlen(str3);
     * b2[1].Command = (char *)malloc(sizeof(char)*length3); 
     */
    
    /*
     * Have no idea why this can work as well, did I miss something?
     */
    strcpy(b2[1].Command, str3);
    printf("length of b2[1].Command is: %d\n", (int)strlen(b2[1].Command));

    printf("%s\n", b2[1].Command);

    return 0;
}
