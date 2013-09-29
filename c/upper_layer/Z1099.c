#include <stdio.h>
#include <string.h>
/*
 * still cannot pass!
 */
int main(){
	int n=0;
	char cha[82];
	while(scanf("%s",cha) != EOF){
		if (strcmp(cha,"<br>")==0) {
			n=0;
			printf("\n");
		} else if (strcmp(cha,"<hr>")==0) {
			if (n==0) {
				printf("--------------------------------------------------------------------------------\n");
                n = 0;
			} else {
				printf("\n--------------------------------------------------------------------------------\n");
                n = 0;
			}
		} else if ((n+=strlen(cha))<80){
			printf("%s ",cha);
			n+=1;
		} else {
			if (n==80) {
				printf("%s ",cha);
				n=0;
			} else {
				printf("\n%s ",cha);
                n=0;
			}
		}
	}
	return 0;
}
