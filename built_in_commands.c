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
 * changes directory by user-specified one 
 */
int change_directory(char **arguments)
{

    // if no arguments followed by "cd" command
    // change directory to HOME
    if (arguments[1] == NULL)
    {
        char *home = getenv("HOME");
        strcat(home, "/");
        chdir(home);
    }
    else
    { // change directory to user-specified location
        if (chdir(arguments[1]) != 0)
        { // if directory not found...
            printf("cd: no such file or directory: %s\n", arguments[1]);
        }
    }

    // cleanup
    // free(arguments);

    return 1;
}

/**
 * saves user's command output in a file 
 */
int redirection(char **arguments, char *fileName, int count)
{

    pid_t pid = fork(); // create a new process
    int status;

    if (pid == -1)
    {
        printf("forking failed\n");
    }

    else if (pid == 0)
    {
        int fd;
        int ret;

        // store file name
        char *file = fileName;

        // open a file for reading/writing
        fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0666);

        // set arguments after ">" to NULL so that
        // when passed to execvp(), no error would occur
        // assuming there are no commands after file name
        arguments[count] = NULL;     // remove " > "
        arguments[count + 1] = NULL; // remove file name

        //TODO: fix fd2
        // fd2 = open("error.txt", O_CREAT | O_RDWR, 0666);

        if (fd < 0)
        {
            perror("open");
            exit(1);
        }

        ret = dup2(fd, 1);

        if (ret < 0)
        {
            perror("dup2");
            exit(1);
        }

        // execute command and save it in a file
        execvp(arguments[0], arguments);

        close(fd); // close file descriptor
    }

    else
    { // parent waits until child completes
        waitpid(pid, &status, 0);
    }

    return 1;
}
