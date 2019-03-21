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
#include <dirent.h>

#define BUFFSIZE 1024
#define size 100

// /**
//  * function to trim trailing '\n'
//  */
void trim(char *s)
{
    int len = strlen(s); // get the length of the string

    // remove newline character
    if (s[len - 1] == '\n')
    {
        s[len - 1] = '\0';
    }
}

// /**
//  * split a string into tokens
//  * takes 3 arguments as input:
//  *  1. the string to be parsed
//  *  2. pointer to empty char array
//  *  3. integer to count the number of arguments
//  */
void split(char *userInput, char **arguments, int *count)
{
    int i = 0;
    char *temp = strtok(userInput, " ");

    while (temp != NULL)
    {
        arguments[i] = temp;
        trim(arguments[i]);
        i++;
        //arguments = realloc(arguments, BUFFSIZE * sizeof(char *));
        temp = strtok(NULL, " ");
    }

    *count = i;
}

/**
 * signal handler : 
 * catches whenever ( Ctrl + C ) / ( Ctrl + D ) is eneted
 * and does appropriate action 
 */
void signal_handler(int signo)
{
    // catches ( Ctrl + C ) / ( Ctrl + D )
    signal(signo, signal_handler);

    console_prompt(); // call prompt() again

    fflush(stdout); // flush stdout 
}

/**
 * function that gets local date and time
 * and saves it in a character array 
 * that is passed back to the caller
 */
void console_prompt()
{
    char buff[size];

    time_t t = time(0);

    struct tm *tmp;

    time(&t);

    tmp = localtime(&t);

    strftime(buff, size, "[%d/%m %H:%M]", tmp);
    printf("\n%s # ", buff);
}


/**
 * prints exit message 
 */
void exitMessage(){
    printf("Program terminated.\n"); 
}