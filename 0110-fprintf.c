#include "stdio.h"

/*
 * use main(void) instead of main(), or will cause a warning.
 */
int main(void){

    FILE *stream;
    char test[] = "Standard test code, come from lib/0110-fprintf.c";

    stream = fopen ("/home/gc/workspace/tmp_can_del/test_fopen.txt","wr");
    fprintf (stream, "%s\n", test);

    /*
     * Note here: all single line comments will be treated as error.
     *            below will cause a warning.
     * const char *fmt = "%s\n";
     * fprintf(stream, fmt, test);
     */

    fputs (test, stream);
    fclose (stream);

    return 0;
}
