#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include<stdlib.h>

void main(int argc, char **argv)
{
    int aop = 0, rop = 0;
    if(argv[1] != NULL && argv[1][0] == '-')
    {
        if(strcmp(argv[1], "-a") == 0)
        {
            aop = 1;
        }
        else if(strcmp(argv[1], "-r") == 0)
        {
            rop = 1;
        }
        else
        {
            printf("Invalid argument.\n");
            return;
        }
    }

    //ls dont show hidden files
    //ls || ls -a or ls -r
    if(argv[1] == NULL || (argv[1] != NULL && argv[1][0] == '-' && argv[2] == NULL))
    {
        //just ls
        int n = 0;
        char *a[1000];
        struct dirent *dir;

        DIR *d = opendir(".");
        while((dir = readdir(d)) != NULL)
        {
            a[n++] = dir->d_name;
        }
        char temp[1000];
        for (int i = 1; i < n; i++)
        {
            for (int j = 1; j < n; j++)
            {
                if(rop == 1)
                {
                    if ( strcasecmp(a[j - 1], a[j]) < 0 )
                    {
                        strcpy(temp, a[j - 1]);
                        strcpy(a[j - 1], a[j]);
                        strcpy(a[j], temp);
                    }
                }
                else
                {
                    if ( strcasecmp(a[j - 1], a[j]) > 0 )
                    {
                        strcpy(temp, a[j - 1]);
                        strcpy(a[j - 1], a[j]);
                        strcpy(a[j], temp);
                    }
                }
            }
        }

        for( int i = 0 ; a[i] != NULL ; i++ )
        {
            if(aop == 0)
            {
                if(a[i][0] != '.')
                {
                    printf("%s    ", a[i]);
                }
            }
            else
            {
                printf("%s    ", a[i]);
            }
        }
        printf("\n");
        closedir(d);
    }
    else if(argv[1] != NULL && argv[2] == NULL)
    {
        //ls Desktop 
        DIR *d = opendir(argv[1]);
        if( d == NULL )
        {
            printf("Directory not found\n");
            return;
        }
        int n = 0;
        char *a[1000];
        struct dirent *dir;

        while((dir = readdir(d)) != NULL)
        {
            a[n++] = dir->d_name;
        }
        char temp[1000];
        for (int i = 1; i < n; i++)
        {
            for (int j = 1; j < n; j++)
            {
                if ( strcasecmp(a[j - 1], a[j]) > 0 )
                {
                    strcpy(temp, a[j - 1]);
                    strcpy(a[j - 1], a[j]);
                    strcpy(a[j], temp);
                }
            }
        }

        for( int i = 0 ; a[i] != NULL ; i++ )
        {
            if(a[i][0] != '.')
                printf("%s    ", a[i]);
        }
        printf("\n");
        closedir(d);
    }
    else if(argv[1] != NULL && argv[1][0] == '-' && argv[2] != NULL && argv[3]==NULL)
    {
        //ls -a Desktop or ls -r Desktop
        DIR *d = opendir(argv[2]);
        if( d == NULL )
        {
            printf("Directory not found\n");
            return;
        }
        int n = 0;
        char *a[1000];
        struct dirent *dir;

        while((dir = readdir(d)) != NULL)
        {
            a[n++] = dir->d_name;
        }
        char temp[1000];
        for (int i = 1; i < n; i++)
        {
            for (int j = 1; j < n; j++)
            {
                if(rop == 1)
                {
                    if ( strcasecmp(a[j - 1], a[j]) < 0 )
                    {
                        strcpy(temp, a[j - 1]);
                        strcpy(a[j - 1], a[j]);
                        strcpy(a[j], temp);
                    }
                }
                else
                {
                    if ( strcasecmp(a[j - 1], a[j]) > 0 )
                    {
                        strcpy(temp, a[j - 1]);
                        strcpy(a[j - 1], a[j]);
                        strcpy(a[j], temp);
                    }
                }
            }
        }

        for( int i = 0 ; a[i] != NULL ; i++ )
        {
            if(aop == 0)
            {
                if(a[i][0] != '.')
                {
                    printf("%s    ", a[i]);
                }
            }
            else
            {
                printf("%s    ", a[i]);
            }
        }
        printf("\n");
        closedir(d);
    }
    else
    {
        printf("Too many arguments.\n");
    }


}