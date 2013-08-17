#include "mystates.h"
#include "mytypes.h"

int main(void){
    STATE                   state1  = 7;
    STATE                   state2  = 0;
    STATE                   state3  = 1;

    decode_state(state1);
    decode_state(state2);
    decode_state(state3);
    return 0;
}
