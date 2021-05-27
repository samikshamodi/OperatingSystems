#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>


//internal commands
//cd echo history pwd exit

//external commands
//ls cat date rm mkdir

void exec_cd(char **command)
{
    if(command[1] == NULL)
    {
        //HOME      The name of the directory, used when no directory opeerand is specified.
        chdir(getenv("HOME"));
    }
    else if(command[2] != NULL)
    {
        printf("Too many arguments\n");
    }
    else if(strcmp(command[1], "~") == 0)
    {
        chdir(getenv("HOME"));
    }
    else if(strcmp(command[1], "..") == 0)
    {
        chdir("..");
    }
    else if(command[1][0] == '-')
    {
        printf("Invalid argument\n");
    }
    else if(chdir(command[1]) != 0)
    {
        printf("Directory not found\n");
        return;
    }

}

void exec_echo(char **command)
{
    //-n    do not append a newline
    if(command[1] == NULL)
    {
        printf("\n");
        return;
    }

    if(strcmp(command[1], "-n") == 0)
    {
        if(command[2] != NULL && command[2][0] == '"')
        {
            int i = 2;
            while(command[i] != NULL)
            {
                for(int j = 0; j < strlen(command[i]); j++)
                {
                    if(command[i][j] != '"')
                    {
                        printf("%c", command[i][j] );
                    }
                }
                printf(" ");
                i++;
            }

        }
        else
        {
            int i = 2;
            while(command[i] != NULL)
            {
                for(int j = 0; j < strlen(command[i]); j++)
                {
                    if(command[i][j] != '\\')
                    {
                        printf("%c", command[i][j] );
                    }
                }
                printf(" ");
                i++;
            }
        }
    }

    //-E    explicitly suppress interpretation of backslash escapes
    else if(strcmp(command[1], "-E") == 0)
    {
        if(command[2] != NULL && command[2][0] == '"')
        {
            int i = 2;
            while(command[i] != NULL)
            {
                for(int j = 0; j < strlen(command[i]); j++)
                {
                    if(command[i][j] != '"')
                    {
                        printf("%c", command[i][j] );
                    }
                }
                printf(" ");
                i++;
            }

        }
        else
        {
            int i = 2;
            while(command[i] != NULL)
            {
                for(int j = 0; j < strlen(command[i]); j++)
                {
                    if(command[i][j] != '\\')
                    {
                        printf("%c", command[i][j] );
                    }
                }
                printf(" ");
                i++;
            }
        }

        printf("\n");

    }

    else
    {
        if(command[1] != NULL && command[1][0] == '"')
        {
            int i = 1;
            while(command[i] != NULL)
            {
                for(int j = 0; j < strlen(command[i]); j++)
                {
                    if(command[i][j] != '"')
                    {
                        printf("%c", command[i][j] );
                    }
                }
                printf(" ");
                i++;
            }

        }
        else
        {
            int i = 1;
            while(command[i] != NULL)
            {
                for(int j = 0; j < strlen(command[i]); j++)
                {
                    if(command[i][j] != '\\')
                    {
                        printf("%c", command[i][j] );
                    }
                }
                printf(" ");
                i++;

            }
        }
        printf("\n");
    }
}

void exec_history(char **command, char **history, int *history_cnt)
{

    if (command[1] != NULL && command[1][0] == '-')
    {
        //-c  clear the history list by deleting all of the entries
        if(strcmp(command[1], "-c") == 0)
        {
            free (history);
            *history_cnt = 0;
            history = (char **) malloc(sizeof(char) * 1000);

        }
        //-w    write the current history to the history file
        else if(strcmp(command[1], "-w") == 0)
        {
            FILE *fPtr;
            if (command[2] == NULL)
            {
                fPtr = fopen("historyfile.txt", "w");
            }
            else
            {
                fPtr = fopen(command[2], "w");
            }

            if(fPtr == NULL)
            {
                printf("Unable to create file\n");
                return;
            }


            for(int i = 0; i < *history_cnt; i++)
            {

                fprintf(fPtr, "%d ", i + 1);
                fputs(history[i], fPtr);
                fputs("\n", fPtr);
            }

            fclose(fPtr);
        }
        else
        {
            printf("Invalid argument\n");
        }

    }

    else if(command[1] == NULL)
    {
        for(int i = 0; i < *history_cnt; i++)
        {
            printf("%d   %s\n", i + 1, history[i]);
        }
    }
    else
    {
        printf("Invalid argumetns\n");
    }
}

void exec_pwd(char **command)
{

    if((command[1] == NULL))
    {
        char cwd[1000];
        getcwd(cwd, 1000);
        if(cwd == NULL)
        {
            printf("Unable to get working directory\n");
            return;
        }
        printf("%s\n", cwd);
    }
    else
    {
        printf("Invalid argument\n");
        return;

    }
}

void runExternalCommand(char **command)
{
    pid_t pid;

    if(strcmp(command[0], "ls") == 0)
    {
        pid = fork();
        if(pid < 0)
        {
            printf("fork failed.");
            return;
        }
        else if(pid == 0)
        {
            execvp("/home/samiksha/Desktop/shell/ls", command);
        }
        else
        {
            wait(NULL);
        }
    }
    else  if(strcmp(command[0], "cat") == 0)
    {
        pid = fork();
        if(pid < 0)
        {
            printf("fork failed.");
            return;
        }
        else if(pid == 0)
        {
            execvp("/home/samiksha/Desktop/shell/cat", command);
        }
        else
        {
            wait(NULL);
        }
    }
    else  if(strcmp(command[0], "date") == 0)
    {
        pid = fork();
        if(pid < 0)
        {
            printf("fork failed.");
            return;
        }
        else if(pid == 0)
        {
            execvp("/home/samiksha/Desktop/shell/date", command);
        }
        else
        {
            wait(NULL);
            return;
        }
    }
    else  if(strcmp(command[0], "rm") == 0)
    {
        pid = fork();
        if(pid < 0)
        {
            printf("fork failed.");
            return;
        }
        else if(pid == 0)
        {
            execvp("/home/samiksha/Desktop/shell/rm", command);
        }
        else
        {
            wait(NULL);
        }
    }
    else  if(strcmp(command[0], "mkdir") == 0)
    {
        pid = fork();
        if(pid < 0)
        {
            printf("fork failed.");
            return;
        }
        else if(pid == 0)
        {
            execvp("/home/samiksha/Desktop/shell/mkdir", command);
        }
        else
        {
            wait(NULL);
        }
    }
}


void runInternalCommand(char **command, char **history, int *history_cnt)
{

    if(strcmp(command[0], "cd") == 0)
    {
        exec_cd(command);
    }
    else if(strcmp(command[0], "echo") == 0)
    {
        //printf("exec_echo");
        exec_echo(command);
    }
    else if(strcmp(command[0], "history") == 0)
    {
        exec_history(command, history, history_cnt);
    }
    else if(strcmp(command[0], "pwd") == 0)
    {
        exec_pwd(command);
    }
    else if(strcmp (command[0], "exit") == 0)
    {
        exit(EXIT_SUCCESS);
    }
}
char **parseCommand(char *commandStr)
{
    char *token;
    char **tokens;
    tokens = malloc(1000 * sizeof(char *));
    int i = 0;
    token = strtok(commandStr, " \n");
    while(token != NULL)
    {
        tokens[i] = token;
        i++;
        token = strtok(NULL, " \n");

    }
    tokens[i] = NULL;
    return tokens;
}
char *readCommand(char **history, int *history_cnt)
{
    char *temp;
    temp = malloc(1000 * sizeof(char));
    fgets(temp, 1000, stdin);
    if(temp == NULL)
    {
        char *str = "Input error";
        return str;
    }
    history[*history_cnt] = strdup(temp);
    *history_cnt += 1;
    return temp;
}

void printPrompt()
{
    printf("<Shell>$");
}


int main()
{
    int N = 1000;
    char *commandStr;
    char **command;
    char **history;
    history = (char **) malloc(sizeof(char) * N);
    int history_cnt = 0;

    while(1)
    {
        //terminal prompt
        printPrompt();

        //readCommand
        commandStr = readCommand(history, &history_cnt);
        command = parseCommand(commandStr);

        //internal commands
        //cd echo history pwd exit
        if (command[0] == NULL)
        {

        }
        else if(strcmp(command[0], "cd") == 0 || strcmp(command[0], "echo") == 0 ||  strcmp(command[0], "history") == 0 || strcmp(command[0], "pwd") == 0 || strcmp(command[0], "exit") == 0)
        {
            runInternalCommand(command, history, &history_cnt);
        }
        //external commands
        //ls cat date rm mkdir
        else if(command[0] != NULL && strcmp(command[0], "ls") == 0 || strcmp(command[0], "cat") == 0 ||  strcmp(command[0], "date") == 0 || strcmp(command[0], "rm") == 0 || strcmp(command[0], "mkdir") == 0)

        {
            runExternalCommand(command);
        }
        else
        {
            printf("Invalid command. Not supported\n");
        }

    }
    return 0;
}