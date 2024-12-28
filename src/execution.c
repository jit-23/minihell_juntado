/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 04:05:04 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/12/28 08:33:39 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	run_tree(t_shell *sh, t_cmd *root)
{
	if (!root)
		return ;
	if (root->type == _EXEC)
		run_cmd(sh, (t_exec *)root);
	else if (root->type == _REDIR)
		run_redir(sh, (t_redir *)root);
	else if (root->type == _PIPE)
		run_pipe(sh, (t_pipe *)root);
}

void	parent_duty(t_shell *sh, int pid, int status)
{
	update_signal();
	if (waitpid(pid, &status, 0) != -1)
	{
		if (WIFEXITED(status))
			g_sign = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_sign = 128 + WTERMSIG(status);
	}
	delete_hiden_files(sh);
}

void	start_tree_run(t_shell *sh)
{
	if (sh->root)
		run_tree(sh, sh->root);
	delete_all(sh);
	if (sh->ev)
		delete_env_lst(sh->ev, lst_size_env(sh->ev));
	exit(g_sign);
}

void	_handle_execution(t_shell *sh)
{
	int	pid;
	int	wstatus;

	pid = 0;
	wstatus = 0;
	if (!sh->rl->official_head || !sh->root)
	{
		g_sign = 0;
		return ;
	}
	if (sh->root->type == _EXEC)
	{
		run_tree(sh, sh->root);
		delete_hiden_files(sh);
		return ;
	}
	pid = fork();
	if (pid == 0)
		start_tree_run(sh);
	else
		parent_duty(sh, pid, wstatus);
}
