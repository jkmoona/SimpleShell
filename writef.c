#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    if (strcmp("-f", argv[1]) != 0 || argc != 3) // check syntax
    {
        puts("Error! Writef syntax: writef -f filename.txt");
        exit(0);
    }

    char *fileName = argv[2];
    FILE *fPtr;
    fPtr = fopen(fileName, "a"); // open file in append mode

    if (fPtr == NULL) // check if file opened
    {
        printf("\nUnable to open '%s' file.\n", fileName);
        exit(0);
    }

    // get and print time
    time_t rawtime;
    struct tm *timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);

    fprintf(fPtr, "systime: %02d:%02d:%02d, ppid: %d, pid: %d\n", timeinfo->tm_hour, timeinfo->tm_min,
            timeinfo->tm_sec, getppid(), getpid());
    return 0;
}