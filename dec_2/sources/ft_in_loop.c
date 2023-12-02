#include "lib_for_minishell.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>

void sigint_handler(int signum) 
{
    (void)signum;
  
    printf("\n");
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}


void sigterm_handler(int signum)
 {
   
    (void)signum;
    exit(EXIT_SUCCESS);
}



void handle_term() {
    struct termios term;
   if(tcgetattr(0, &term))
   {
    perror("minishell: tcgetattr\n");
   }
    term.c_lflag &= ~ECHOCTL; 
   if (tcsetattr(0, TCSANOW, &term))
   {
     perror("minishell: tcsettatr\n");
   }
}


void sigquit_handler(int signum)
{
   (void)signum;

}

void ft_signal() {
    handle_term();

    struct sigaction sa_int;
    struct sigaction sa_quit;
    struct sigaction sa_term;

    sa_int.sa_handler = sigint_handler;
    sa_int.sa_flags = 0;
    sigemptyset(&sa_int.sa_mask);

    if (sigaction(SIGINT, &sa_int, NULL) == -1) {
        perror("sigaction SIGINT");
        exit(EXIT_FAILURE);
    }

    sa_quit.sa_handler = sigquit_handler;
    sa_quit.sa_flags = 0;
    sigemptyset(&sa_quit.sa_mask);

    if (sigaction(SIGQUIT, &sa_quit, NULL) == -1) {
        perror("sigaction SIGQUIT");
        exit(EXIT_FAILURE);
    }

    sa_term.sa_handler = sigterm_handler;
    sa_term.sa_flags = 0;
    sigemptyset(&sa_term.sa_mask);

    if (sigaction(SIGTERM, &sa_term, NULL) == -1)
     {
        perror("sigaction  SIGTERM");
        exit(EXIT_FAILURE);
    }
}



void ft_loop(t_token_list *token_list, t_environment_list *envp_list) {
    char *input_str = NULL;
    int error_num;

//    ft_signals();
   ft_signal();
    while (1) {
        input_str = ft_readline();
    signal(SIGQUIT, SIG_DFL);
        ft_lexer(input_str, token_list);
        ft_parser(&token_list, envp_list);
        ft_syntax_error(&token_list->next, &error_num);
        ft_heredoc_quant_error(&token_list->next);
        if (error_num != EXIT_ERROR_SYNTAX && token_list->next != NULL)
            ft_program(token_list, &envp_list);
        if (error_num == EXIT_ERROR_SYNTAX)
            exit_status_msh = EXIT_ERROR_SYNTAX;
        free(input_str);
        ft_list_free_for_token(&token_list->next);
    }
    return;
}
