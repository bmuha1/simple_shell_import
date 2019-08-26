#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

extern char **environ;
/**
 * struct list_s - linked list that hold a name with value per node
 * @var: variable in the notation "name=value"
 * @next: points to the next node
 */
typedef struct list_s
{
	char *var;
	struct list_s *next;
} list_t;
list_t *set_env_list(void);
size_t print_list(const list_t *h);
list_t *add_node_end(list_t **head, char *var);
list_t *add_node_at_index(list_t **head, int idx, char *var);
int delete_node_at_index(list_t **head, size_t index);
int find_var_index(char *name, list_t *h);
char *_getenv(char *name, list_t *h);
char *_getenv_value(char *name, list_t *h);
void _unsetenv(char *name, list_t **head);
void _setenv(char *name, char *value, list_t **head);
void free_list(list_t *h);

void remove_comments(char *line);
int only_delims(char *line);
void handle_sigint(int sig);

/* see if program exists in path directories */
void search_path(char **args, list_t *env);
void replace_dollars(char **args, list_t *env);

int execute(char **args, list_t *env);
void print_error(char **args, list_t *env, char *message);

char **strtow(char *str, char *delim);
int count_words(char *str, char *delim);
int _strlen(const char *s);
char *_strstr(char *haystack, const char *needle);
char *_strchr(char *s, char c);
int _strcmp(char *s1, char *s2);
int _atoi(char *s);
char *str_concat(char *s1, char *s2);
char *_strdup(char *str);
int _strpbrk(char *s, char accept);
void _ntoa_rev(int n, char *s);
void rev_string(char *s);

/**
 * struct cmd_s - used to identify a built-in to execute
 * @type: an existing built-in function
 * @exec_built_in: directs to built-in function for execution
 */
typedef struct cmd_s
{
	char *type;
	int (*exec_built_in)(char **args, list_t *env);
} cmd_t;
int (*get_built_in(char *cmd))(char **args, list_t *env);
int simple_exit(char **args, list_t *env);
int simple_env(char **args, list_t *env);
int simple_unsetenv(char **args, list_t *env);
int simple_setenv(char **args, list_t *env);
int simple_history(char **args, list_t *env);
int simple_help(char **args, list_t *env);
void which_help(char *command);
int simple_cd(char **args, list_t *env);
int not_built_in(char **args, list_t *env);

#endif /* SHELL_H */
