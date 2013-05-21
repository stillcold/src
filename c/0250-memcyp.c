#include <stdio.h>
#include <string.h>

#include "mytypes.h"

typedef struct Complex{ u8 a; u8 b;} Complex;

Complex c1;

int main(void)
{
    /*
     * My HP PC is a little endian machine.
     */

    /* a: 1111 1111 1111 1111 */
    u16 a = 65535;
    /* b: 0000 0000 1111 1111 */
    u16 b = 65280;
    /* c: 1111 1111 0000 0000 */
    u16 c = 255;

    void * p = "12345";

    /* This works for me */

    printf("%d\n", sizeof (u8));
    memcpy (&c1, &a, 2);
    printf("%u %u\n", c1.a, c1.b);
    memcpy (&c1, &b, 2);
    printf("%u %u\n", c1.a, c1.b);
    memcpy (&c1, &c, 2);
    printf("%u %u\n", c1.a, c1.b);

    /* Need instructions for code below */

    memcpy (&c1, p, 1);
    printf("%u %u\n", c1.a, c1.b);

    return 0;
}
