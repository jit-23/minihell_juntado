/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:08:42 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/11/14 17:28:58 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//int g_status_exit_val;


//#include "../includes/env.h"

//#define BLUE 			\033 [0;34m
//#define default_colour	\033 [0m

static void	get_prompt(t_shell *shell)
{
	char	*dir;

	dir = NULL;
	dir = getcwd(dir, 100);
	shell->prompt = ft_strjoin(dir, "$ ");
	shell->cmd_line = readline(shell->prompt);
	if (shell->cmd_line && shell->cmd_line[0] != 0)
		add_history(shell->cmd_line);
	free(dir);
}

static void	print_env(t_env *e, char **ev)
{
	int	i;

	i = 0;
	while (e)
	{
		printf(RED "%s\n", e->env_name);
		printf(CSET "%s\n", ev[i]);
		e = e->next;
		i++;
	}
}

static void	print_vals(t_env *e, char **ev)
{
	int	i;

	i = 0;
	while (e)
	{
		printf(RED ".%s.\n", e->env_value);
		printf(CSET "%s\n", ev[i]);
		e = e->next;
		i++;
	}
}

void get_path_env(t_shell *shell, char **envp)
{
	int	i;

	i = -1;
	shell->path = NULL;
	while(envp[++i] != NULL)
	{
		if(ft_strncmp(envp[i], "PATH=", 4) == 0)
		{
			shell->path = ft_split(&envp[i][5], ':');
			break ;
		}
	}
}

void  init_shell(t_shell *shell, char **ev)
{
	shell->env = ev;
	shell->root = NULL;
	get_path_env(shell, ev);
	shell->prompt = NULL;
	shell->cmd_line = NULL;
	shell->token_list = NULL;
	shell->stop_iteration = false;
	shell->token_list = (t_lexer *)malloc( sizeof(t_lexer));
	shell->rl = (t_lexer *)malloc( sizeof(t_lexer));
	shell->token_list->head = NULL;
	shell->token_list->official_head = NULL;
	shell->rl->head = NULL;
	shell->rl->official_head = NULL;
	shell->in = dup(STDIN);
	shell->out = dup(STDOUT);
	reset_fd(shell);
	shell->ret = 0;
	shell->heredoc_tmp_file = 65;
	shell->heredoc_flag = 0;
	shell->no_exec = 0;
}

void	delete_path(char **path, int i)
{
	while(path[i])
		free(path[i++]);
	free(path);
}

int main(int ac,char **av ,char **ev)
{
	t_shell shell;
	
	if (ac != 1)
		return (ft_putstr_fd(2, "invalid number of arguments:"),1);
	shell.exitcode = 0;
	shell.ev = expand_env(&shell, ev);	
	while (1)
	{
		init_shell(&shell, ev);
		handle_signal();
		get_prompt(&shell);
		if (shell.cmd_line)
		{
			analise_terminal_input(&shell, shell.cmd_line);
			_handle_execution(&shell);
			delete_all(&shell);
		}
		else
		{
			
			delete_all(&shell);
			
			if (shell.ev)
				delete_env_lst(shell.ev, lst_size_env(shell.ev));
			ft_putstr_fd(1, "exit\n");
			exit (1);
		}
	}	
	printf("end of minishell\n");
//	if (shell.ev)
//		delete_env_lst(shell.ev, lst_size_env(shell.ev));
	return 0;
}
