#include "minicrt.h"

int main(int argc,char *argv[])
{
	int i;
	FILE* fp;

	fp	= fopen("temp.txt","w");
	
	//
	{
	  char* buf = "hello, how are you \n";
	  int len = strlen(buf);
	  fwrite(buf ,1,len,fp);
	  printf("%d  %s\n",len,buf);
	}

    char* buf1 = "original string";
    char* buf2;

    buf2 = (char *) malloc(15);
    strcpy(buf2, buf1);

    printf("%s\n", buf2);
	
	fclose(fp);

	return 0; 
}

