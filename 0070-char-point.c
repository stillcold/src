#include <stdio.h>
char * get_output(void){
	return "hello, world.\n";
}
int main(){
	printf("%s",get_output());
	return 0;
}
