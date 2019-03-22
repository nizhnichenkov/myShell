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
#include "functions.h"
#define BUFFSIZE 1024

int decider(char **arguments, int count)
{
    // ERROR HANDLING:
    // if no command was entered
    if (arguments[0] == NULL)
    {
        return 1;
    }

    //TODO: when redirection is used, program stops after completing it
    // catch redirect " > "
    for (int i = 0; i < count; i++)
    {
        if (strcmp(arguments[i], ">") == 0)
        {
            // save file name
            char *fileName = arguments[i + 1];

            // call redirect function with
            // parsed arguments, filename and count
            return redirection(arguments, fileName, i);
        }
    }


    // if "cd" is encountered,
    // change directory
    if (strcmp(arguments[0], "cd") == 0)
    {
        return change_directory(arguments);
    }
    else
    { // execute command normally
        return use_fork(arguments);
    }

    return 1;
}