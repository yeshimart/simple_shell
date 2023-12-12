#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUF_SIZE 3072
#define WRITE_BUF_SIZE 3072
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	6144

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_xyz;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_xyz *);
} builtin_table;


/* my_xyz_shloop.c */
int ysh(info_xyz *, char **);
int require_builtin(info_xyz *);
void findCommand(info_xyz *);
void copy_cmd(info_xyz *);

/* my_xyz_parser.c */
int checkCommandExistence(info_xyz *, char *);
char *dup_chars(char *, int, int);
char *look_path(info_xyz *, char *, char *);

/* my_xyz_errors.c */
void sys_eputs(char *);
int eput_char(char);
int _placefd(char c, int fd);
int _ptsfd(char *str, int fd);

/* my_xyz_string.c */
int str_leng(char *);
int stringCompare(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* my_xyz_string1.c */
char *_strcopie(char *, char *);
char *dup_strd(const char *);
void outputString(char *);
int outputCharacter(char);

/* my_xyz_exits.c */
char *copie_strn(char *, char *, int);
char *cat_strn(char *, char *, int);
char *findCharacter(char *, char);

/* my_xyz_tokenizer.c */
char **strtoword(char *, char *);
char **strtow(char *, char);

/* my_xyz_realloc.c */
char *fillMemory(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* my_xyz_memory.c */
int freeMemory(void **);

/* my_xyz_atoi.c */
int interactive(info_xyz *);
int checkDelimiter(char, char *);
int isAlphabetic(int);
int convertToInt(char *);

/* my_xyz_errors1.c */
int con_atoi(char *);
void puts_error(info_xyz *, char *);
int print_des(int, int);
char *con_number(long int, int, int);
void remove_comments(char *);

/* my_xyz_builtin.c */
int program_exit(info_xyz *);
int shel_cd(info_xyz *);
int program_help(info_xyz *);

/* my_xyz_builtin1.c */
int shel_history(info_xyz *);
int shel_alias(info_xyz *);

/*my_xyz_getline.c */
ssize_t get_input(info_xyz *);
int getLineFromInfo(info_xyz *, char **, size_t *);
void sigintHandler(int);

/* my_xyz_getinfo.c */
void clear_info(info_xyz *);
void setInfoFromArguments(info_xyz *, char **);
void releaseInfo(info_xyz *, int);

/* my_xyz_environ.c */
char *_getenv(info_xyz *, const char *);
int system_env(info_xyz *);
int program_setenv(info_xyz *);
int system_unsetenv(info_xyz *);
int initializeEnvList(info_xyz *);

/* my_xyz_getenv.c */
char **getEnviron(info_xyz *);
int unsetEnvironmentVariable(info_xyz *, char *);
int updateEnvironment(info_xyz *, char *, char *);

/* my_xyz_history.c */
char *getHistoryFile(info_xyz *info);
int writeInfoHistory(info_xyz *info);
int read_history(info_xyz *info);
int createHistoryList(info_xyz *info, char *buf, int linecount);
int renumber_history(info_xyz *info);

/* my_xyz_lists.c */
list_t *addN(list_t **, const char *, int);
list_t *appendNode(list_t **, const char *, int);
size_t printStringListElements(const list_t *);
int removeAtIndex(list_t **, unsigned int);
void freeLinkedList(list_t **);

/* my_xyz_lists1.c */
size_t countListElements(const list_t *);
char **listToStringArray(list_t *);
size_t printListSize(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/* my_xyz_vars.c */
int is_chain(info_xyz *info, char *buf, size_t *p);
void check_chain(info_xyz *info, char *buf, size_t *p, size_t i, size_t len);
int replace_alias(info_xyz *info);
int replace_vars(info_xyz *info);
int subst_string(char **old, char *new);
#endif

