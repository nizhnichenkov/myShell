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

/**
 * creates child processes and executes
 * commands such as : pwd, ls, cat, etc.
 * using " execvp() "
 */
int use_fork(char **args)
{

    pid_t pid = fork(); // create a new process
    int status;

    if (pid == -1) // if forking was unsuccessful
    {
        printf("Forking failed\n");
    }

    else if (pid == 0)
    {


        // execute command
        if (execvp(args[0], args) == -1)
        {
            signal(SIGINT, SIG_DFL); // set signal to default
            printf("shell: command not found: %s\n", args[0]);
            exit(EXIT_FAILURE); // exit child process
        }
    }

    else
    {   // catch signal
        signal(SIGINT, signal_handler);
        // parent waits until child completes
        wait(&status);

        signal(SIGINT, signal_handler);
    }


    return 1;
}
