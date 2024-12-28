/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 20:59:29 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/12/28 09:01:46 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	run_left_branch(t_shell *sh, t_pipe *branch, int pipe[2])
{
	dup2(pipe[1], 1);
	close(pipe[0]);
	close(pipe[1]);
	run_tree(sh, (t_cmd *)branch->left);
}

void	run_right_branch(t_shell *sh, t_pipe *branch, int pipe[2])
{
	dup2(pipe[0], 0);
	close(pipe[0]);
	close(pipe[1]);
	run_tree(sh, (t_cmd *)branch->right);
}

void	get_exit_code(int status, t_shell *sh)
{
	if (WIFEXITED(status) != 0)
		g_sign = WEXITSTATUS(status);
	delete_all(sh);
	if (sh->ev)
		delete_env_lst(sh->ev, lst_size_env(sh->ev));
	exit(g_sign);
}

void	run_pipe_aux(t_shell *sh, int fd[2], t_pipe *pp, int r_l)
{
	if (r_l == 1)
		run_left_branch(sh, pp, fd);
	else
		run_right_branch(sh, pp, fd);
	delete_all(sh);
	if (sh->ev)
		delete_env_lst(sh->ev, lst_size_env(sh->ev));
	exit(g_sign);
}

void	run_pipe(t_shell *sh, t_pipe *pp)
{
	int		fd[2];
	int		status;
	pid_t	left;
	pid_t	right;

	pipe(fd);
	left = fork();
	if (left == 0)
		run_pipe_aux(sh, fd, pp, 1);
	right = fork();
	if (right == 0)
		run_pipe_aux(sh, fd, pp, 2);
	update_signal();
	close(fd[0]);
	close(fd[1]);
	waitpid(left, &status, 0);
	waitpid(right, &status, 0);
	get_exit_code(status, sh);
}
