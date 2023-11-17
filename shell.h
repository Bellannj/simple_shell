#ifndef _SHELL_H_
#define _SHELL_H_

#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>


#define END_OF_FILE -2
#define EXIT -3


/* Global history counter */
int list;
/* Global environemnt */
extern char **environ;
/* Global program name */
char *name;



typedef struct list_s
{
	char *dir;
	struct list_s *next;
} list_t;


typedef struct builtin_s
{
	char *name;
	int (*f)(char **argv, char **front);
} builtin_t;


typedef struct alias_s
{
	char *name;
	char *value;
	struct alias_s *next;
} alias_t;

/* Global aliases linked list */
alias_t *aliases;

/* Input Helpers */
int handle_args(int *exe_ret);
int run_args(char **args, char **front, int *exe_ret);
void _handle_line(char **line, ssize_t read);
char **replace_aliases(char **args);
char *get_args(char *line, int *exe_ret);
int call_args(char **args, char **front, int *exe_ret);
void var_rep(char **args, int *exe_ret);
void free_arg_1(char **args, char **front);
int _check_arg(char **args);


/* Main Helpers */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **_strtok(char *line, char *delim);
char *get_location(char *cmd);
list_t *get_path_dir(char *path);
int execute(char **args, char **front);
void _list1(list_t *head);
char *_itoa(int num);





/* Builtins */
int shellby_env(char **args, char __attribute__((__unused__)) **front);
int (*get_builtin(char *cmd))(char **args, char **front);
int shellby_exit(char **args, char **front);
int shellby_cd(char **args, char __attribute__((__unused__)) **front);
int shellby_alias(char **args, char __attribute__((__unused__)) **front);
int _shellby_help(char **args, char __attribute__((__unused__)) **front);
int shellby_setenv(char **args, char __attribute__((__unused__)) **front);
int _shellby_unsetenv(char **args, char __attribute__((__unused__)) **front);

/* Strings */
int _strlen(const char *s);
int _strspn(char *s, char *accept);
int _strcmp(char *s1, char *s2);
char *_strncat(char *dest, const char *src, size_t n);
char *_strcat(char *dest, const char *src);
char *_strcpy(char *dest, const char *src);
char *_strchr(char *s, char c);
int _strncmp(const char *s1, const char *s2, size_t n);

/*error*/

char *error_enva(char **args);
char *error_3_syntax(char **args);
int _error_creat(char **args, int err);
char *error_126(char **args);
char *error_0(char **args);
char *error_1_exit(char **args);
char *error_2_cd(char **args);
char *error_127(char **args);



char **copeyenv(void);
void free_envaro(void);
char **_getenva(const char *var);


void help_2(void);
void help_env_1(void);
void help1(void);
void _alias_1(void);
void _cd_1(void);
void _history(void);
void _exit_1(void);
void _unsetenv(void);
void _setenv(void);

/* Linkedlist Helpers */
alias_t *add_alias_end(alias_t **head, char *name, char *value);
void alias_list(alias_t *head);
list_t *add_node_at_end(list_t **head, char *dir);
void _list1(list_t *head);


int _file_cmd(char *file_path, int *exe_ret);
#endif /* _SHELL_H_ */
