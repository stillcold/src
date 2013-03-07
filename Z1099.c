#include <stdio.h>
/*
 * still cannot pass!
 */
int main(){
	int n=0;
	char *cha;
	do{
		scanf("%s",cha);
		if (strcmp(cha,"<br>")==0) {
			n=0;
			printf("\n");
		} else if (strcmp(cha,"<hr>")==0) {
			if (n==0) {
				printf("--------------------------------------------------------------------------------\n");
			} else {
				printf("\n--------------------------------------------------------------------------------\n");
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
	}while(cha!=NULL&&cha!=EOF);
	return 0;
}
