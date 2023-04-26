#ifndef SHELL_H
#define SHELL_H

#include <stdio.h> /* for printf*/
#include <unistd.h> /* for fork, execve*/
#include <stdlib.h>
#include <string.h> /* for strtok*/
#include <stddef.h>
#include <errno.h> /* for errno and perror */
#include <sys/types.h> /* for type pid */
#include <sys/wait.h> /* for wait */
#include <sys/stat.h> /* for use of stat function */
#include <signal.h> /* for signal management */
#include <fcntl.h> /* for open files*/

/************* EXEC NAME **************/

#include "exec_name.h" /* for msg help and prompt */

/************* STRUCTURES **************/

/**
 * struct info- struct for the program's data
 * @program_name: the name of the executable
 * @input_line: pointer to the input read for _getline
 * @command_name: pointer to the first command typed by the user
 * @exec_counter: number of excecuted comands
 * @file_descriptor: file descriptor to the input of commands
 * @tokens: pointer to array of tokenized input
 * @env: copy of the environ
 * @alias_list: array of pointers with aliases.
 */

typedef struct info
{
	char *program_name;
	char *input_line;
	char *command_name;
	int exec_counter;
	int file_descriptor;
	char **tokens;
	char **env;
	char **alias_list;
} data_of_program;

/**
 * struct builtins - struct for the builtins
 * @builtin: the name of the builtin
 * @function: the associated function to be called for each builtin
 */

typedef struct builtins
{
	char *builtin;
	int (*function)(data_of_program *data);
} builtins;


/************* MAIN FUNCTIONS *************/


/*========  shell.c  ========*/

/* Inicialize the struct with the info of the program */
void inicialize_data(data_of_program *data, int arc, char *argv[], char **env);

/* Makes the infinite loop that shows the prompt*/
void sisifo(char *prompt, data_of_program *data);

/* Print the prompt in a new line */
void handle_ctrl_c(int opr UNUSED);


/*======== Getline_array.c ========*/

/* Read a single line of the standard input*/
int Getline_array(data_of_program *data);

/*======== Buffer_size.c ========*/

/* expand the buffer size  variables */
<<<<<<< HEAD
void Expand_buffsize(data_of_program *data);
=======
void expand_Buffsize(data_of_program *data);
>>>>>>> 5b2e2a42bda66ecc96e2a4bc8b9ab6e0291162be

/* expand aliases of the data */
void expand_alias(data_of_program *data);

/* the string to the end of the buffer is appended */
int buffer_add(char *buffer, char *str_to_add);


/*======== delim_strtok.c ========*/

/* Separate the string in tokens using a designed delimiter */
void tokenize(data_of_program *data);

/* Creates a pointer to a part of a string */
char *_strtok(char *line, char *delim);


/*======== command_exec.c ========*/

/*The command on its entire path is executed */
int command_exec(data_of_program *data);


/*======== list_builtins.c ========*/

/* It execute the programme that matches the builtin */

int list_builtins(data_of_program *data);


/*========shell_path.c ========*/

/*It Searches for program in it path */
int find_progpath(data_of_program *data);

/*An array of the path directories is created */
char **tokenize_path(data_of_program *data);


/************** HELPERS FOR MEMORY MANAGEMENT **************/


/*======== free_array.c ========*/

/* Frees the memory for directories */
void free_array_f_pointers(char **directories);

/* Free the fields needed each loop */
void free_recurrent_data(data_of_program *data);

/* Free all field of the data */
void free_all_data(data_of_program *data);


/************** BUILTINS **************/


/*======== builtin_exit.c========*/

/*It closes and exit the shell */
int builtin_exit(data_of_program *data);

/*it  Changes  the current directory */
int builtin_cd(data_of_program *data);

/*it sets the work directory */
int set_work_directory(data_of_program *data, char *new_dir);

/* It displays the help information */
int builtin_help(data_of_program *data);

/*It sets, unsets and shows alias */
int builtin_alias(data_of_program *data);


/*======== env_builtins.c ========*/

/*It shows the environment where the shell runs */
int builtin_env(data_of_program *data);

/* create or override a variable of environment */
int builtin_set_env(data_of_program *data);

/* delete a variable of environment */
int builtin_unset_env(data_of_program *data);


/************** HELPERS FOR ENVIRONMENT VARIABLES MANAGEMENT **************/


/*======== Env_variable.c ========*/

/* It gets the value of an environment variable */
char *env_get_key(char *name, data_of_program *data);

/* the value of the environment variable is overwritten */
int env_set_key(char *key, char *value, data_of_program *data);

/*It removes a key from the environment */
int env_remove_key(char *key, data_of_program *data);

/*It prints the current environ */
void print_environ(data_of_program *data);


/************** HELPERS FOR PRINTING **************/


/*======== str_duplicate.c ========*/

/* Prints a string in the standar output */
int _print(char *string);

/* Prints a string in the standar error */
int _printe(char *string);

/* Prints a string in the standar error */
int _print_error(int errorcode, data_of_program *data);


/************** HELPERS FOR STRINGS MANAGEMENT **************/


/*======== str_length.c ========*/

/* Counts the number of characters of a string */
int str_length(char *string);

/* Duplicates an string */
char *str_duplicate(char *string);

/* Compares two strings */
int str_compare(char *string1, char *string2, int number);

/* Concatenates two strings */
char *str_concat(char *string1, char *string2);

/* Reverse a string */
void str_reverse(char *string);


/*======== str_convert.c ========*/

/* Cast from int to string */
void long_to_string(long number, char *string, int base);

/* convert an string in to a number */
int _atoi(char *s);

/* count the coincidences of character in string */
int count_characters(char *string, char *character);


/*======== alias_list.c ========*/

/* print the list of alias */
int print_alias(data_of_program *data, char *alias);

/* get the alias name */
char *get_alias(data_of_program *data, char *alias);

/* set the alias name */
int set_alias(char *alias_string, data_of_program *data);


#endif /* SHELL_H */
