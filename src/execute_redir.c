/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 20:57:42 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/12/28 08:12:41 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	openf(t_redir *redir, int i_o, int flags, int *fd)
{
	*fd = open(redir->file, flags, 0664);
	if (*fd < 0)
		return (-1);
	dup2(*fd, i_o);
	return (*fd);
}

int	get_file(t_shell *sh, t_redir *redir)
{
	int	fd;

	(void)sh;
	fd = -1;
	if (redir->mode == 0)
	{
		if (openf(redir, STDIN_FILENO, O_RDONLY, &fd) < 0)
			return (-1);
	}
	else if (redir->mode == 1)
	{
		if (openf(redir, STDOUT_FILENO, O_CREAT | O_WRONLY | O_TRUNC, &fd) < 0)
			return (-1);
	}
	else if (redir->mode == 2)
	{
		if (openf(redir, STDOUT_FILENO, O_CREAT | O_APPEND | O_WRONLY, &fd) < 0)
			return (-1);
	}
	else if (redir->mode == 3)
	{
		if (openf(redir, STDIN_FILENO, O_CREAT | O_APPEND | O_WRONLY, &fd) < 0)
			return (-1);
	}
	return (fd);
}

void	run_redir(t_shell *sh, t_redir *redir)
{
	int		file;
	t_exec	*e;

	e = NULL;
	file = get_file(sh, redir);
	if (file < 0)
	{
		ft_putstr_fd(2, "Permission denied:\n");
		delete_all(sh);
		g_sign = 1;
		exit(g_sign);
	}
	if (redir->cmd)
	{
		e = (t_exec *)redir->cmd;
		if (!e->args[0])
			run_tree(sh, NULL);
		run_tree(sh, (t_cmd *)redir->cmd);
	}
	else
		printf("NO\n");
}
