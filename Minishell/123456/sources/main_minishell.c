
#include "lib_for_minishell.h"



int	ft_strncmp_k(const char *s1, const char *s2, size_t	n)
{
	size_t	i;

	i = 0;
    if (!s1 || !s2)
        return 1;
	while ((s1[i] || s2[i]) && (i < n))
	{
		if (s1[i] != s2[i])
		{
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		}
		i++;
	}
	return (0);
}


int     unclosed_quotes(char *input)
{
        int             i;
        int             S_quote;
        int             D_quote;

        i = 0;
        S_quote = 0;
        D_quote = 0;
        while (input[i])
        {
                if (input[i] == '\'' && !D_quote)
                        S_quote = !S_quote;
                else if (input[i] == '\"' && !S_quote)
                        D_quote = !D_quote;
                i++;
        }
        if (S_quote || D_quote)
        {
            printf("Error: Unclosed quote\n");
                return 1;
        }
        return 0;
}



void pwd(void)
{
    char *pwd = NULL;

    pwd = getcwd(pwd, 1024); //second max size of path..
    if (pwd == NULL) //pwd check
      perror("getcwd() error");
    printf("%s\n", pwd);
    free(pwd);
  //  free(pwd); getcwd causes memory leaks if not freed ???
}
void ft_lstiter(t_token_list *token_list)
{
    t_token_list *tmp;

    if (!token_list)
        return;
    tmp = token_list;
    while (tmp != NULL)
    {
        if (tmp != NULL && ft_strncmp(tmp->value, "pwd", 3) == 0)
        {
            printf("PWWWWWWDDDD\n");
            pwd();
            printf("PWD builtin CALLED\n");
        }
        tmp = tmp->next;
    }
    return;
}


int main(int argc, char *arg[], char *envp[])
{
    char *input_str;
    char **path_arr;
    char **argv;
    pid_t pid;
    t_token_list token_list;
    int i;

    //token_list = malloc(sizeof(token_list));
    token_list.type = 100;
    token_list.value = NULL;
    token_list.next = NULL;
    (void)arg;
    i = argc;
    path_arr = ft_make_path_arr(envp);
    // i = 0;
    // while(path_arr[i] != NULL)
    // {
    //     printf("%s\n", path_arr[i]);
    //     i++;
    // }
    // (void)pid;  ///test
    // (void)argv;  //test
    while(1)
    {
        input_str = ft_readline();
        if (!unclosed_quotes(input_str))
    {
        ft_lexer(input_str, &token_list);
        ft_lstiter(&token_list);
        ft_lstiter_printf(&token_list, printf);

        argv = ft_split(input_str, ' ');
        printf("PRINTF(%s)\n", argv[0]);
        free(input_str);
        pid = fork();
        if (pid == 0)
        {
            ft_execve_firstfork(path_arr, argv, envp);
            exit(EXIT_SUCCESS);
        }
        i = 0;
        while(argv[i] != NULL)
        {
            free(argv[i]);
            i++;
        }
        free(argv);
        //system("leaks minishell");
        wait(NULL);
     }
    }
    // perror("EXECVE ERROR:::");
    // system("leaks minishell");
    exit(EXIT_SUCCESS);

}
