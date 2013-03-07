/*
 * This file depends on 0130-extern-define.c and 0140-testExtern.h
 * Compile Command:
 * 	gcc 0012-extern-main.c 0130-extern-define.c 014-testExtern.h
 * Notes:
 * 	From this file, we can see that "extern" can be used 
 * either in Caller or Callee. Both is OK.
 */

/*
 * Now the head is no longer needed.
 * #include "0140-testExtern.h"
 */

extern fun1(void);

int main(void){
    fun1();
    fun2();
    return 0;
}
