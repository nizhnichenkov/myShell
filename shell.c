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

// shell
void shell_loop(void)
{

    int status;

    do
    {
        int exitStatus = 0; 
        char *line = NULL;
        char **arguments = malloc(BUFFSIZE * sizeof(char *));
        size_t len = 0;
        int count = 0;

        // catch signal and display prompt for user input 
        signal(SIGINT, signal_handler);
        console_prompt();
        signal(SIGINT, signal_handler);

        exitStatus = getline(&line, &len, stdin); // get command entered by user

        // check for ( CRTL + D )
        if(exitStatus == -1){
            break;
        }
        else{

        trim(line); // remove newline character

        split(line, arguments, &count); // split string into tokens ( command + arguments )

        // decides which function to call
        // depending on arguments passed
        status = decider(arguments, count);
    }

    } while (status);

    exitMessage();
}