/**
 * @author          Svetoslav Nizhnichenkov 
 * @StudentID       17712081
 * @email           svetoslav.nizhnichenkov@ucdconnect.ie
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <ctype.h>
#include <signal.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include "functions.h"
#define BUFFSIZE 1024
#define size 50

// shell
void shell_loop(void)
{

    int status;

    do
    {
        char *line = NULL;
        char **arguments = malloc(BUFFSIZE * sizeof(char *));
        size_t len = 0;
        int count = 0;

        signal(SIGINT, signal_handler);
        console_prompt();
        signal(SIGINT, signal_handler);

        getline(&line, &len, stdin); // get command entered by user

        trim(line); // remove newline character

        split(line, arguments, &count); // split string into tokens ( command + arguments )

        // decides which function to call
        // depending on arguments passed
        status = decider(arguments, count);
        // printf("NMBR : %d\n", status2);

        // free(line);
        // free(arguments);

    } while (status);

    exitMessage();
}