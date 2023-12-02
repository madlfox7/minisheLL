
#ifndef LIB_FOR_MINISHELL_H
# define LIB_FOR_MINISHELL_H

#include <stdio.h> // readline();
#include <stdlib.h> // exit();
#include <readline/readline.h>// readline();
#include <readline/history.h> // readline();
#include <unistd.h> // execve();
#include <termios.h> // for signals ???
# include <fcntl.h> // open();

# define START 100
# define WHITESPACES " \t\r\n\v\f"
# define WHITESPACES_RL "\t\r\n\v\f" // without space
# define END_OF_DOLLAR_SIGN "~!@#%%^*-=+[]{}:,./\'?"
# define NOT_WORD_CHARS " \t\r\n\v\f\'\"<>|"
# define BUILTIN_EXIT 0
# define BUILTIN_RETURN 1
# define ONLY_ONE_BUILTIN 1
# define EXIT_ERROR_NO_FILE_OR_DIRECTORY 1
# define EXIT_ERROR_HEREDOC_QUANT 2
# define EXIT_ERROR_CMD_NOT_FOUND 127
# define EXIT_ERROR_SYNTAX 258
# define ERROR_REDIR "minishell"
# define ERROR_SYNTAX "minishell: syntax error near unexpected token `%s'\n"
# define ERROR_CMD_NOT_FOUND "minishell: %s: command not found\n"
# define ERROR_ENV "env: Too many arguments\n"
# define ERROR_HEREDOC_QUANT "minishell: maximum here-document count exceeded\n"  //(exit amboghj bashic)

int exit_status_msh;

typedef enum s_type_of_token
{
    SEP, //0
    Q_SINGLE, //1
    Q_DOUBLE, //2
    REDIR_INT, //3
    REDIR_OUT, //4
    REDIR_APPEND, //5
    HEREDOC, //6
    PIPE, //7
    WORD, //8
    // AND,
    // OR,
    // PAR_LEFT,
    // PAR_RIGHT,
} t_type_of_token;

typedef struct s_environment_list
{
    int envp_flag;
    char **name_and_value;
    struct s_environment_list *next;
} t_environment_list;

typedef struct s_token_list
{
    int type;
    char *value;
    struct s_token_list *next;
} t_token_list;

typedef struct s_for_prog
{
    t_token_list *redir_list;
    char **envp_for_execve;
    char **path_arr;
    char ***argv_for_execve;
    int fd_quant_heredoc;
    int fd_quant_pipe;
    int **fd_arr_pipe;
    int **fd_arr_heredoc;
    int *pid_arr;
} t_for_prog;

typedef struct s_for_fork
{
    pid_t   pid;
    int     fd_out;
    int     fd_redir[3];
    char    **prog_paths;
} t_for_fork;

//libft
void	*ft_memmove(void	*dst, const void	*src, size_t	len);
int     ft_memcmp(const void	*s1, const void	*s2, size_t	n);
size_t	ft_strlen(const	char *s);
size_t	ft_strncmp(const char	*s1, const char	*s2, size_t	n);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	**ft_split(char const	*s, char c);
char	*ft_strchr(const char	*s, int c);
char	*ft_strjoin(char const	*s1, char const	*s2);
int     ft_isdigit(int c);
int	    ft_atoi(const char	*str);
long long	ft_longlong_atoi_for_minishell(const char *str);
char	*ft_itoa(int n);
char	*ft_strdup(const char	*s1);
char    *ft_strdup_quant(const char	*str, size_t quant);
void	ft_str_to_lowercase(char *str);
//size_t	ft_strl_spc(const	char *s);
//char	*ft_strjoin_space(char const	*s1, char const	*s2);

//for_main
void   ft_loop(t_token_list *token_list, t_environment_list *envp_list);

//readline
char *ft_readline(void);

//environment list
t_environment_list   *ft_list_creat_environment(char *envp[]);
t_environment_list	*ft_list_last_for_environment(t_environment_list	*list);
void	             ft_list_add_back_for_environment(t_environment_list	**list, t_environment_list	*list_for_add);
int                  ft_list_length_for_environment(t_environment_list *list);
void                 ft_change_shlvl_of_environment(t_environment_list **start_of_list);

//token list
t_token_list        *ft_list_creat_token(void);
t_token_list	    *ft_list_last_for_token(t_token_list	*list);
void	            ft_list_add_back_for_token(t_token_list	**list, t_token_list	*new_list);
void                ft_list_free_for_token(t_token_list **list);
int                 ft_list_length_for_token(t_token_list *list);

//lexer
void ft_lexer(char *rl, t_token_list *token_list);
void ft_is_token_sep(int *i, char *input_str, t_token_list *token_list);
void ft_is_token_single_quote(int *i, char *input_str, t_token_list *token_list);
void ft_is_token_double_quote(int *i, char *input_str, t_token_list *token_list);
void ft_is_token_redir_int_heredoc(int *i, char *input_str, t_token_list *token_list);
void ft_is_token_redir_out_append(int *i, char *input_str, t_token_list *token_list);
void ft_is_token_pipe(int *i, char *input_str, t_token_list *token_list);
void ft_is_token_word(int *i, char *input_str, t_token_list *token_list);

//parser
void ft_parser(t_token_list **token_list, t_environment_list *envp_list);
void ft_parser_first_change_dollar(t_token_list **list, t_environment_list *envp_list);
void ft_parser_second_change_dollar(t_token_list **list, t_environment_list *envp_list);
void ft_parser_third_change_quotes_to_word(t_token_list **list, t_environment_list *envp_list);
void ft_parser_fourth_join_w(t_token_list **list, t_environment_list *envp_list);
void ft_parser_fifth_change_redir_value(t_token_list **list, t_environment_list *envp_list);
void ft_parser_remove_sep_from_list(t_token_list **list, t_environment_list *envp_list);

//change dollar in word
char *ft_change_dollar_sign_in_word(char *string, t_environment_list *envp_list);
int  ft_char_find(char c, char const	*string);
char **ft_creat_splitted_dollar(char *string);
int  ft_symbol_quant_in_string(char *string, char symbol);
void ft_creat_string_dollar_in_splitted(int i, char *string, char **splitted_dollar);
void ft_join_splitted_after_change(char **joined_str, char **first_part, char **splitted_dollar);
char *ft_creat_first_part_of_word(char *string, char *symbols);
void ft_change_splitted_dollar(char ***splitted_dollar, t_environment_list **envp_list);
void ft_change_dollar_in_string_of_splitted(t_environment_list *tmp_env, char **string_from_splitted);
char *ft_change_dollar_sign_in_string(char **string, char **name_and_value, int num_for_last, int *result);
void ft_creat_before_after_strings(int i, char **tmp_str, char **before_end_symb, char **after_end_symb);
char *ft_change_dollar_sign_in_before_end_symb(char **before_end_symb, char **name_and_value, int num_for_last, int *result);
char *ft_creat_last_part_of_word(char *string, char *symbols);
void ft_additional_for_else_if(char **str_for_dup, char **tmp_str, char **exit_status_msh_str, int *result);

//change dollar in qdoub
char *ft_change_dollar_sign_in_qdoub(char *string, t_environment_list *envp_list);
void ft_change_dollar_in_splitted_qdoub(char ***splitted_str, t_environment_list *envp_list);
int  ft_count_spaces_for_joined_after_change(char *string);
int  ft_count_chars_for_joined_after_change(char **splitted_str);
char *ft_creat_joined_after_change(char *string, char **splitted_str, int quant);
void ft_additional_for_creat_joined_first(int *i, int *k, char *string, char *joined_after_change);
void ft_additional_for_creat_joined_second(int *j, int *k, char **splitted_str, char *joined_after_change);

//syntax_error; heredoc_error
void ft_syntax_error(t_token_list **list, int *error_num);
void ft_heredoc_quant_error(t_token_list **list);

//program
void ft_program(t_token_list *token_list, t_environment_list **envp_list);
void ft_creat_for_program(t_for_prog *prog, t_token_list *token_list, t_environment_list **envp_list);
char **ft_creat_envp_for_execve(t_environment_list *envp_list);
char **ft_creat_path_argv_for_execve(char	**envp);
t_token_list *ft_creat_redir_list_for_execve(t_token_list *token_list);
char ***ft_creat_argv_for_execve(t_token_list *token_list, int fd_quant_pipe);
void ft_waitpid_for_prog(t_for_prog *prog);
void ft_free_for_prog(t_for_prog *prog);

//pipe
int ft_fd_quant(t_token_list *token_list, int type);
int	**ft_creat_and_open_pipes(int fd_quant_pipe);
void ft_input_to_heredoc(t_token_list *token_list, int **fd_arr_heredoc);
void ft_close_pipe_fd(int **fd, int fd_quant_pipe);

//execve
void ft_running_program(t_for_prog *prog, t_environment_list **envp_list);
void ft_change_stdin_stdout_fd_pipe(int **fd_arr, int fd_quant_pipe, int i);
int ft_change_stdin_stdout_fd_redir(t_token_list *redir_list, int *fd_redir, int **heredoc_pipe, int only_one_builtint);

//free
void ft_free_double_pointer_array(char ***array);
void ft_free_double_pointer_int(int ***array, int fd_quant_pipe);
void ft_free_triple_pointer_array(char ****array);

//printf
void ft_list_iter_printf_token(t_token_list	*list,	int (f)(const char *, ...));
void ft_list_iter_printf_environment(t_environment_list	*list, int (f)(const char *, ...));
void ft_printf_double_arr(char **double_arr);
void ft_printf_triple_arr(char ***triple_arr);

//builtin
void ft_env(char **str, t_environment_list *envp, int fd_out, int exit_num);
int ft_export(char **str, t_environment_list **envp, int exit_num);
void ft_unset(char **array_of_strings, t_environment_list **envp, int exit_num);
size_t streq(char *s1, char *s2);
int ft_wrong_name(char *name, char *str);
void ft_if_only_one_builtin(t_token_list *tmp_redir_list, t_environment_list **envp_list, t_for_prog *prog, int *check);
void ft_running_builtin(char **array, t_environment_list **envp_list, int fd_num, int exit_num);
char	*ft_strnstr(char *str, char *to_find, size_t len);;
//echo
void ft_echo(char **str, int exit_num);
int n_set(char *str, int *suppress_nl);

//cd
t_environment_list *find_node_by_name(t_environment_list *envp,  char *name) ;
void ft_cd(char **str, t_environment_list **envp, int exit_num) ;
t_environment_list *ft_list_new_for_export(char *name, char *value);


//exit
void ft_exit(char **str, t_environment_list **envp, int exit_num) ;
long int atoi_limit(const char *str, int *limit) ;
void exit_builtin(t_environment_list **env_list, int exit_status) ;
int parse_error(char *str, int *exit_status) ;
int ft_isdigit(int c);
int get_exit_status(long res);


//pwd
void    ft_pwd(char **str, t_environment_list **envp, int exit_num);
t_environment_list *set_last_node(t_environment_list **envp, int flag);


//signals
void	inthandle(int sig);

#endif