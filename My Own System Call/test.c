/* Name: Samiksha Modi
   Roll_Number: 2019331 */
   
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[])
{

    long activity=syscall(440,getpid(),"output");
    
    if(activity==0)
    {
    	printf("System call is functional. Run the command dmesg in the terminal and find out\n");
    }
    
    else
    {
     	printf("sh_task_info System call did not execute as expected."); 
     	if(activity==-4)
        {
        	printf("Error while copying from user");
        }
        else if(activity==-2)
        {
        	printf("PID has no task_struct");
        }
        else if(activity==-3)
        {
        	printf("File not opened");
        }
     	else
     	{
     		printf("Error no: %d\n",errno);    
     	}    
    }

    return 0;
}

