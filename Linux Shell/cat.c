#include <stdio.h>
#include <string.h>

void main(int argc, char **argv)
{
    if(argv[1] == NULL)
    {
        char line[1000];
        while( 1 )
        {
            fgets(line, 1000, stdin);
            if(line[strlen(line) - 1] == '\n')
            {
                line[strlen(line) - 1] = 0;
            }
            printf("%s\n", line);
        }
    }
    else if(strcmp(argv[1], "-E") == 0)
    {
        if(argv[2] == NULL)
        {
            char line[1000];
            while( 1 )
            {
                fgets(line, 1000, stdin);
                if(line[strlen(line) - 1] == '\n')
                {
                    line[strlen(line) - 1] = 0;
                }
                printf("%s$\n", line);
            }
        }
        else
        {
            for(int i = 2; argv[i] != NULL; i++)
            {
                FILE *file = fopen(argv[i], "r");
                if (file == NULL)
                {
                    printf("File %s doesn't exist\n", argv[i]);
                }
                else
                {
                    char line[1000];
                    while(fgets(line, 1000, file) != NULL)
                    {
                        if(line[strlen(line) - 1] == '\n')
                        {
                            line[strlen(line) - 1] = 0;
                        }
                        printf("%s$\n", line );
                    }
                }
            }
        }
    }
    else if(strcmp(argv[1], "-n") == 0)
    {
        if(argv[2] == NULL)
        {
            int in = 1;
            char line[1000];
            while( 1 )
            {
                fgets(line, 1000, stdin);
                if(line[strlen(line) - 1] == '\n')
                {
                    line[strlen(line) - 1] = 0;
                }
                printf("\t%d %s\n", in, line);
                in++;
            }
        }
        else
        {
            int jn = 1;
            for(int i = 2; argv[i] != NULL; i++)
            {
                FILE *file = fopen(argv[i], "r");
                if (file == NULL)
                {
                    printf("File %s doesn't exist\n", argv[i]);
                }
                else
                {
                    char line[1000];
                    while(fgets(line, 1000, file) != NULL)
                    {
                        if(line[strlen(line) - 1] == '\n')
                        {
                            line[strlen(line) - 1] = 0;
                        }
                        printf("\t%d %s\n", jn, line );
                        jn++;
                    }
                }
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
            FILE *file = fopen(argv[i], "r");
            if (file == NULL)
            {
                printf("File %s doesn't exist\n", argv[i]);
            }
            else
            {
                char line[1000];
                while(fgets(line, 1000, file) != NULL)
                {
                    if(line[strlen(line) - 1] == '\n')
                    {
                        line[strlen(line) - 1] = 0;
                    }
                    printf("%s\n", line );
                }
            }
        }
    }

}