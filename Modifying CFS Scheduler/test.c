/* Name: Samiksha Modi
   Roll_Number: 2019331 */
#include <stdio.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>
#include<stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{    
	int pid;    
    	long i=0;

    	struct timeval start,end;
    	gettimeofday(&start,NULL);
 
    	pid=fork();
    	if(pid<0)
	{
		printf("Fork failed\n");
		return 0;
	}

    	if(pid==0)
    	{
 		for(i=0;i<2000000000;i++);
 		gettimeofday(&end,NULL);
 		double time=(double)(end.tv_usec-start.tv_usec)/1000000 + (double)(end.tv_sec-start.tv_sec);
 		printf("Time 2: %lf \n",time);
 		exit(EXIT_SUCCESS);
    	}
    	else
    	{
     		long ans=syscall(440,getpid(),100);
     		//long ans=syscall(440,-2,100);  
     		//long ans=syscall(440,getpid(),-4);      
		
		if(ans!=0)
		{
			printf("Error: %d\n",errno);
			return 0;
		}
		
 		for(i=0;i<2000000000;i++);
 		gettimeofday(&end,NULL);
 		double time=(double)(end.tv_usec-start.tv_usec)/1000000 + (double)(end.tv_sec-start.tv_sec);
 		printf("Time 1: %lf \n",time);
 		wait(NULL);
    	}
}
