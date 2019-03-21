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

/**
 * creates child processes and and executes 
 * commands such as : pwd, ls, cat, etc.
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
            printf("shell: command not found: %s\n", args[0]);
        }
    }

    else
    {
        // parent waits until child completes
        waitpid(pid, &status, 0);
    }

    return 1;
}
