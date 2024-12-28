/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 21:01:05 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/12/28 08:56:07 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	setcs(void)
{
	signal(SIGINT, signal_child_handler);
	signal(SIGQUIT, signal_child_handler);
}

void	wait_child(int pid, int status, t_shell *shell)
{
	if (waitpid(pid, &status, 0) != -1)
	{
		if (WIFEXITED(status))
			g_sign = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_sign = 128 + WTERMSIG(status);
	}
}

void	signal_parent_handler(int sign)
{
	if (sign == SIGINT)
	{
		g_sign = 130;
		write(1, "\n", 1);
	}
}

void	update_signal_parent(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	run_cmd(t_shell *sh, t_exec *ex)
{
	pid_t	pid1;
	int		status;

	status = 0;
	pid1 = 0;
	if (ex->args[0] == NULL)
		return ;
	if (is_builtin(ex->args[0]))
	{
		execute_builtin(ex, ex->args[0], sh);
		return ;
	}
	pid1 = fork();
	if (pid1 == 0)
	{
		setcs();
		if (execve(ex->args[0], ex->args, sh->env) == -1)
			run_cmd_exit_msg(sh, ex->args[0]);
	}
	else
	{
		handle_parent_signal();
		wait_child(pid1, status, sh);
	}
}
