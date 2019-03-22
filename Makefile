CC=gcc
CFLAGS=-Wall

all: myshell

myshell: main.o built_in_commands.o decider.o shell.o use_execvp.o user_input.o 
	$(CC) $(CFLAGS) -o myshell main.o built_in_commands.o decider.o shell.o use_execvp.o user_input.o 

main.o: main.c functions.h
	$(CC) $(CFLAGS) -c  main.c


built_in_commands.o: built_in_commands.c functions.h
	$(CC) $(CFLAGS) -c  built_in_commands.c


decider.o: decider.c functions.h
	$(CC) $(CFLAGS) -c  decider.c

shell.o: shell.c functions.h
	$(CC) $(CFLAGS) -c  shell.c

use_execvp.o: use_execvp.c functions.h
	$(CC) $(CFLAGS) -c  use_execvp.c

user_input.o: user_input.c functions.h
	$(CC) $(CFLAGS) -c  user_input.c


clean: 
	$(RM) myshell *.o *~
