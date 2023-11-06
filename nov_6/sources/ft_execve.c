
#include "lib_for_minishell.h"

int ft_fd_quant(t_token_list *token_list);
int	**ft_make_and_open_pipes(int fd_quant);
char ***ft_creat_argv_for_execve(t_token_list *token_list, int fd_quant);
t_token_list *ft_creat_redir_list_for_execve(t_token_list *token_list);
void ft_is_token_redir_for_execve(t_token_list *token_list, t_token_list *redir_list);

void ft_execve(t_token_list *token_list, t_environment_list *envp_list)
{
    char **envp_for_execve;
    char **path_arr;
    int fd_quant;
    int **fd_arr;
    t_token_list *redir_list;
    char ***argv_for_execve;
    
    envp_for_execve = ft_creat_envp_for_execve(envp_list);
    //ft_printf_double_arr(path_arr);
    path_arr = ft_make_path_argv_for_execve(envp_for_execve);
    //ft_printf_double_arr(path_arr);
    fd_quant = ft_fd_quant(token_list);
    fd_arr = ft_make_and_open_pipes(fd_quant);
    redir_list = ft_creat_redir_list_for_execve(token_list);
    argv_for_execve = ft_creat_argv_for_execve(token_list, fd_quant);
    //ft_printf_triple_arr(argv_for_execve);
    //ft_list_iter_printf_for_token(redir_list, printf);
   // ft_list_iter_printf_for_environment(envp_list, printf);
    ft_fork(path_arr, fd_arr, fd_quant, argv_for_execve, redir_list, envp_for_execve, envp_list);
   // printf("\n\n\n");
    //ft_list_iter_printf_for_environment(envp_list, printf);
    ft_fd_close(fd_arr, fd_quant);
    ft_free_double_pointer_array(&envp_for_execve);
    ft_free_double_pointer_array(&path_arr);
    ft_free_double_pointer_int(&fd_arr, fd_quant);
    ft_free_triple_pointer_array(&argv_for_execve);
    ft_list_free_for_token(&redir_list);
    return ;
}



int ft_fd_quant(t_token_list *token_list)
{
    int fd_quant;

    fd_quant = 0;
    while(token_list != NULL)
    {
        if (token_list->type == PIPE)
            fd_quant++;
        token_list = token_list->next;
    }
    return(fd_quant);
}



int	**ft_make_and_open_pipes(int fd_quant)
{
	int	i;
	int	**fd_arr;

    if (fd_quant == 0)
        return (NULL);
	i = 0;
	fd_arr = (int **)malloc(sizeof(int *) * (fd_quant));
	if (!fd_arr)
	{
		perror("Can't allocate memory in ft_make_and_open_pipes()");
		exit(EXIT_FAILURE);
	}
	while (i < fd_quant)
	{
		fd_arr[i] = (int *)malloc(sizeof(int) * 2);
		if (!fd_arr[i])
		{
			perror("Can't allocate memory in ft_make_and_open_pipes()");
			exit(EXIT_FAILURE);
		}
		if ((pipe(fd_arr[i]) < 0))
			perror("Can't create pipes");
		i++;
	}
	return (fd_arr);
}



char ***ft_creat_argv_for_execve(t_token_list *token_list, int fd_quant)
{   
    t_token_list *tmp_token_list;
    char ***argv_for_execve;
    int i;
    int j;
    int word_quant;

    tmp_token_list = token_list;
    argv_for_execve = (char ***)malloc(sizeof(char **) * (fd_quant + 2));
    i = 0;
    word_quant = 0;
    while(tmp_token_list != NULL)
    {
        if (tmp_token_list->type == WORD)
            word_quant++;
        if (tmp_token_list->type == PIPE || tmp_token_list->next == NULL)
        {
            argv_for_execve[i] = (char **)malloc(sizeof(char *) * (word_quant + 1));
            i++;
        }
        tmp_token_list = tmp_token_list->next;
    }
    tmp_token_list = token_list;
    i = 0;
    j = 0;
    while (tmp_token_list != NULL)
    {
        if (tmp_token_list->type == WORD)
        {
            argv_for_execve[i][j] = ft_strdup(tmp_token_list->value);
            j++;
        }
        if (tmp_token_list->type == PIPE || tmp_token_list->next == NULL)
        {
            argv_for_execve[i][j] = NULL;
            j = 0;
            i++;
        }
        tmp_token_list = tmp_token_list->next;
    }
    argv_for_execve[i] = NULL;
    return (argv_for_execve);
}



t_token_list *ft_creat_redir_list_for_execve(t_token_list *token_list)
{   
    t_token_list *redir_list;

    redir_list = (t_token_list *)malloc(sizeof(t_token_list));
    redir_list->type = START;
    redir_list->value = NULL;
    redir_list->next = NULL;
    while (token_list != NULL)
    {
        ft_is_token_redir_for_execve(token_list, redir_list);
        token_list = token_list->next;
    }
    return (redir_list);
}



void ft_is_token_redir_for_execve(t_token_list *token_list, t_token_list *redir_list)
{
    t_token_list *tmp;

    if (token_list->type == REDIR_INT)
    {
        tmp = (t_token_list *)malloc(sizeof(t_token_list));
        tmp->type = REDIR_INT;
        tmp->value = ft_strdup(token_list->value);
        tmp->next = NULL;
        ft_list_add_back_for_token(&redir_list, tmp);
    }
    else if (token_list->type == REDIR_OUT)
    {
        tmp = (t_token_list *)malloc(sizeof(t_token_list));
        tmp->type = REDIR_OUT;
        tmp->value = ft_strdup(token_list->value);
        tmp->next = NULL;
        ft_list_add_back_for_token(&redir_list, tmp);
    }
    else if (token_list->type == HEREDOC)
    {
        tmp = (t_token_list *)malloc(sizeof(t_token_list));
        tmp->type = HEREDOC;
        tmp->value = ft_strdup(token_list->value);
        tmp->next = NULL;
        ft_list_add_back_for_token(&redir_list, tmp);
    }
    else if (token_list->type == REDIR_APPEND)
    {
        tmp = (t_token_list *)malloc(sizeof(t_token_list));
        tmp->type = REDIR_APPEND;
        tmp->value = ft_strdup(token_list->value);
        tmp->next = NULL;
        ft_list_add_back_for_token(&redir_list, tmp);
    }
    else if (token_list->type == PIPE)
    {
        tmp = (t_token_list *)malloc(sizeof(t_token_list));
        tmp->type = START;
        tmp->value = NULL;
        tmp->next = NULL;
        ft_list_add_back_for_token(&redir_list, tmp);
    }
    return ;
}



void	ft_fd_close(int **fd, int fd_quant)
{
	int	i;

	i = 0;
	while (i < fd_quant)
	{
		close(fd[i][0]);
		close(fd[i][1]);
		i++;
	}
	return ;
}


