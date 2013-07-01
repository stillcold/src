#include   <stdio.h>
#include   <stdlib.h>
#include   <sys/time.h>
#include   <time.h>
char *
GetTimestamp (
                void)
{
        struct timeval          Now;
	static char TimeBuffer[17];
        
	gettimeofday(&Now, NULL); 
	sprintf(TimeBuffer, "%d:%6d", Now.tv_sec,Now.tv_usec);

        return TimeBuffer;
}

int  main(int argc,   char **argv)
{
	struct   timeval   start,stop,diff;
	gettimeofday(&start,0);
	//做你要做的事...
	gettimeofday(&stop,0);
	tim_subtract(&diff,&start,&stop);
	printf("总计用时:%d毫秒\n",diff.tv_usec);

	//struct timeval          Now;
	//        gettimeofday(&Now, NULL); 
	//sprintf(TimeBuffer, "%.63s", Now.tv_usec+4);
	//      printf("saahdashdsa%u\n", Now.tv_usec);

	//	GetTimestamp();
	while(1){
		printf ("%s \n", GetTimestamp());
		sleep(2);
	}
}


int tim_subtract(struct timeval *result, struct timeval *x, struct timeval *y)
{
	int nsec;
	if ( x->tv_sec > y->tv_sec )
		return   -1;
	if ((x->tv_sec==y->tv_sec) && (x->tv_usec>y->tv_usec))
		return   -1;
	result->tv_sec = ( y->tv_sec-x->tv_sec );
	result->tv_usec = ( y->tv_usec-x->tv_usec );
	if (result->tv_usec<0)
	{
		result->tv_sec--;
		result->tv_usec+=1000000;
	}
	return   0;
}
