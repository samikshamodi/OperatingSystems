#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include<stdlib.h>

char *list[] = {"shell.c", "ls.c", "ls", "Makefile", "rm.c", "rm", "date.c", "date", "cat.c", "cat", "mkdir.c", "mkdir"};

int ifValid(char *str)
{
    for(int i = 0; i < 11; i++)
    {
        if(strcmp(str, list[i]) == 0)
        {
            return 0;
        }
    }
    return 1;
}


void main(int argc, char **argv)
{
    if(argv[1] == NULL)
    {
        printf("Insufficient arguments\n");
        return;
    }
    //  -i     prompt before every removal
    else if(strcmp(argv[1], "-i") == 0)
    {
        if(argv[2] == NULL)
        {
            printf("Insuffient argument\n");
            return;
        }

        for(int i = 2; argv[i] != NULL; i++)
        {
            //if you try to remove a file that is used in running the shell, then you cant delete it
            if(ifValid(argv[i]) == 0)
            {
                printf("You do not have the permission to remove %s file\n", argv[i]);
                return;
            }

            if(opendir(argv[i]) != NULL)
            {
                printf("Can't do rm on directories %s\n",argv[i]);
                continue;
            }

            printf("Do you want to remove %s(y/n)? ", argv[i]);
            char *ans;
            ans = malloc(10 * sizeof(char));
            fgets(ans, 10, stdin);
            if(ans[0] != 'y' && ans[0] != 'Y')
            {
                //printf("you said no\n");
                return;
            }
            int status;
            status = remove(argv[i]);
            if(status == 0)
            {
                //printf("successfull\n");
            }
            else
            {
                printf("%s: cannot remove file or directory\n", argv[i]);
            }
            free(ans);

        }
    }
    //  -d, remove empty directories
    else if(strcmp(argv[1], "-d") == 0)
    {

        if(argv[2] == NULL)
        {
            printf("Insuffient arguments.\n");
            return;
        }
        for(int i = 2; argv[i] != NULL; i++)
        {
            if(ifValid(argv[i]) == 0)
            {
                printf("You do not have the permission to remove %s file\n", argv[i]);
                return;
            }
            int status;
            status = remove(argv[i]);
            if(status == 0)
            {
                //printf("successfull\n");
            }
            else
            {
                printf("%s: cannot remove file or directory\n", argv[i]);
            }
        }

    }
    else if(argv[1][0] == '-')
    {
        //argument is not supported only valid options are -i and -d
        printf("Invalid argument\n");
        return;
    }
    else
    {
        for(int i = 1; argv[i] != NULL; i++)
        {
            if(ifValid(argv[i]) == 0)
            {
                printf("You do not have the permission to remove %s file\n", argv[i]);
                return;
            }
            if(opendir(argv[i]) != NULL)
            {
                printf("Can't do rm on directories %s\n",argv[i]);
                continue;
            }

            int status;
            status = remove(argv[i]);
            if(status == 0)
            {
                //printf("successfull\n");
            }
            else
            {
                printf("cannot remove file %s\n", argv[i]);
            }
        }
    }

}