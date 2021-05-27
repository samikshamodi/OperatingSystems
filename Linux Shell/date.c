#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void main(int argc, char **argv)
{
    struct tm *local;
    struct tm *utc;
    char temp[100];

    time_t t = time(NULL);

    if(t == -1)
    {
        printf("time failed\n");
        return;
    }

    if(argv[1] == NULL)
    {
        local = localtime(&t);
        printf("IST %s", asctime(local) );
    }
    else if(strcmp(argv[1], "-I") == 0)
    {
    	local=localtime(&t);
    	strftime(temp,100, "%F",local);
    	printf("%s\n",temp );

    }
    else if (strcmp(argv[1], "-u") == 0)
    {
        utc = gmtime(&t);
        printf("UTC %s", asctime(utc) );
    }
    else
    {
        printf("Invalid argument\n");
    }

}
