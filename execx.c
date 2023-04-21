#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define DELIMS " \t\r\n"

int main(int argc, char *param[])
{
    if (strcmp("-t", param[1]) != 0 || argc != 4) // check syntax
    {
        puts("Error! Example syntax: execx -t 3 ls");
        exit(0);
    }
    char *argv[] = {"/bin/", NULL};
    int val;
    int t = atoi(param[2]);

    //bus error!
    strcat(argv[0], param[3]);
    // printf("t: %d   -- argv[0]= %s\n",t,argv[0]);
    //bus error!

    for (int i = 0; i < t; i++)
    {
        pid_t pid = fork();
        if (pid == 0)
        {
            val = execve(argv[0], argv, NULL);
            if (val == -1)
            {
                perror("Exec error");
            }
        }
        else
        {
            // Wait for child to terminate
            wait(NULL);
        }
    }
}