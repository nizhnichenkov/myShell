/**
 * @author          Svetoslav Nizhnichenkov 
 * @StudentID       17712081
 * @email           svetoslav.nizhnichenkov@ucdconnect.ie
 * 
 */
// remove newline character
void trim(char *s);

// split string into tokens
void split(char *inputStr, char **str, int *count);

// shell
void shell_loop(void);

// signal handler
void signal_handler(int signo);

// get local date and time
void console_prompt();

// change directory
int changeDir(char *command);

// creates child processes using fork()
// and executes commands ( not builtin )
// such as : pwd, cat, ls, clear, etc.
int use_fork(char **args);

// changes directory
int change_directory(char **arguments);

// deals with redirection command " > "
int redirection(char **arguments, char *fileName, int count);

// decides which function to call
// depending on arguments passed
int decider(char **arguments, int count);

// print message to let user know program has exited 
void exitMessage();