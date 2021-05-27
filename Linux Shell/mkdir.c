#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include<string.h>
#include<stdio.h>


void main(int argc, char *argv[])
{
    if(argv[1] == NULL)
    {
        printf("Insufficient arguments\n");
        return;
    }
    else if((strcmp(argv[1], "-p")==0 && (argv[2] != NULL && strcmp(argv[2], "-v")==0))||(strcmp(argv[1], "-v")==0 && (argv[2] != NULL && strcmp(argv[2], "-p")==0)))
    {
        if(argv[3] == NULL)
        {
            printf("Insuffient argument\n");
            return;
        }
        for(int i = 3; argv[i] != NULL; i++)
        {
            struct stat st = {0};
            if(stat(argv[i], &st) == 0)
            {
                printf("Directory %s exists already\n", argv[i] );
            }
            else  if(stat(argv[i], &st) == -1)
            {
                char *temp;
                for(temp = argv[i] + 1; *temp; temp++)
                {
                    if(*temp == '/')
                    {
                        *temp = 0;
                        mkdir(argv[i], 0777);
                        *temp = '/';
                    }
                    mkdir(argv[i], 0777);
                }
                printf("Created directory %s\n", argv[i] );
            }
            else
            {
                printf("Unable to create directory\n");
            }
        }
    }
    else if(strcmp(argv[1], "-p") == 0)
    {
        /*struct stat st={0};
        //if(stat(argv[i],&st)==0) directory already exists

        if(stat(argv[i],&st)==-1)
        {

        }*/
        if(argv[2] == NULL)
        {
            printf("Insuffient argument\n");
            return;
        }

        for(int i = 2; argv[i] != NULL; i++)
        {
            struct stat st = {0};
            if(stat(argv[i], &st) == 0)
            {
                printf("Directory %s exists already\n", argv[i] );
            }
            else  if(stat(argv[i], &st) == -1)
            {
                char *temp;
                for(temp = argv[i] + 1; *temp; temp++)
                {
                    if(*temp == '/')
                    {
                        *temp = 0;
                        mkdir(argv[i], 0777);
                        *temp = '/';
                    }
                    mkdir(argv[i], 0777);
                }
            }
            else
            {
                printf("Unable to create directory\n");
            }
        }

    }
    else if(strcmp(argv[1], "-v") == 0)
    {
        if(argv[2] == NULL)
        {
            printf("Insuffient argument\n");
            return;
        }
        for(int i = 2; argv[i] != NULL; i++)
        {
            struct stat st = {0};
            if(stat(argv[i], &st) == 0)
            {
                printf("Directory %s exists already\n", argv[i] );
            }
            else  if(stat(argv[i], &st) == -1)
            {
                if(mkdir(argv[i], 0777) != 0)
                {
                    printf("Cannot create directory %s: No such file or directory\n", argv[i]);
                }
                else
                {
                    printf("Created directory %s\n", argv[i] );
                }
            }
            else
            {
                printf("Unable to create directory\n");
            }
        }
    }
    else if(argv[1][0] == '-')
    {
        //argument is not supported only valid options are -p and -v
        printf("Invalid argument\n");
        return;
    }
    else
    {
        //mkdir with normal suffiecnt operands
        for(int i = 1; argv[i] != NULL; i++)
        {
            struct stat st = {0};
            if(stat(argv[i], &st) == 0)
            {
                printf("Directory %s exists already\n", argv[i] );
            }
            else  if(stat(argv[i], &st) == -1)
            {
                if(mkdir(argv[i], 0777) != 0)
                {
                    printf("Cannot create directory %s: No such file or directory\n", argv[i]);
                }

            }
            else
            {
                printf("Unable to create directory\n");
            }
        }
    }
}
