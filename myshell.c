#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

#define ARGV_SIZE 10
#define TOKEN_SIZE 5
#define DELIMS " \t\r\n"

// variables for getline()
size_t n = 10;
char *cmd;

int main(int argc, char *argv[])
{

    while (1)
    {
        printf("myshell>> ");
        getline(&cmd, &n, stdin);
        if (strcmp(cmd, "exit\n") == 0)
        {
            exit(0);
        }
        pid_t pid = fork();
        if (pid == -1)
        {
            perror("Fork error!");
            exit(0);
        }
        else if (pid == 0) // Child process
        {
            // tokenize input
            char **newArgv = malloc(sizeof(char *) * ARGV_SIZE);
            char *token = strtok(cmd, DELIMS);

            int i = 0;
            while (token != NULL)
            {
                newArgv[i] = strdup(token);
                token = strtok(NULL, DELIMS);
                i++;
            }
            newArgv[i] = token;

            if (strcmp(newArgv[0], "ls") == 0)
            {
                // variables for execve()
                char cmdPath[] = "/bin/ls";
                char *argv[] = {"ls", newArgv[1], NULL};
                char *env[] = {NULL};

                int val = execve(cmdPath, argv, env);
                if (val == -1)
                {
                    perror("Exec error!");
                }
                puts("Something went wrong!");
            }
            else if (strcmp(newArgv[0], "bash") == 0)
            {
                // variables for execve()
                char cmdPath[] = "/bin/bash";
                char *argv[] = {"bash", NULL};

                int val = execve(cmdPath, argv, NULL);
                if (val == -1)
                {
                    perror("Exec error!");
                }
                puts("Something went wrong!");
            }
            else if (strcmp(newArgv[0], "clear") == 0)
            {
                // won't work if it's not called from default terminal

                // variables for execve()
                char cmdPath[] = "/usr/bin/clear";
                char *argv[] = {"clear", NULL};
                char *env[] = {NULL};
                int val = execve(cmdPath, argv, env);
                if (val == -1)
                {
                    perror("Exec error!");
                    exit(0);
                }
                puts("Something went wrong!");
            }
            else if (strcmp(newArgv[0], "writef") == 0)
            {
                char cmdPath[] = "writef";
                char *argv[] = {"writef", newArgv[1], newArgv[2], NULL};
                char *env[] = {NULL};
                int val = execve(cmdPath, argv, env);
                if (val == -1)
                {
                    perror("Exec error!");
                }
                puts("Something went wrong!");
            }
            else if (strcmp(newArgv[0], "cat") == 0)
            {
                char cmdPath[] = "/bin/echo";
                char *argv[] = {"echo", newArgv[1], NULL};
                char *env[] = {NULL};
                int val = execve(cmdPath, argv, env);
                if (val == -1)
                {
                    perror("Exec error!");
                }
                puts("Something went wrong!");
            }
            else
            {
                puts("Error! There is no such command.");
                exit(0);
            }
        }
        else // Parent process
        {
            wait(NULL);
        }
    }

    return 0;
}
