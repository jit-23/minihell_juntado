/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 20:54:15 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/12/29 16:55:06 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	heredoc_loop(char *eof, t_shell *sh, int fd)
{
	char	*line;

	line = ft_strdup("");
	while (1)
	{
		free(line);
		line = readline("> ");
		if (!line)
		{
			printf("bash: warning: here-document at line");
			printf(" delimited by end-of-file (wanted `%s')\n", eof);
			break ;
		}
		if (ft_strcmp(line, eof) == 0)
			break ;
		write_line(sh, line, fd);
	}
	if (sh->ev)
		delete_env_lst(sh->ev, ft_listsize(sh->ev));
	delete_all(sh);
	return ;
}

static void	h_signal_child_handler(int g_sign)
{
	if (g_sign == SIGINT)
	{
		g_sign = 130;
		ft_putstr_fd(1, "\n");
		exit(g_sign);
	}
}

char	*execute_heredoc(t_cmd *branch, char *eof, t_shell *sh)
{
	char	*file_name;
	int		fd;
	pid_t	pid;
	int		status;

	status = 0;
	file_name = get_file_name(sh);
	fd = open_hdoc_file(file_name, sh);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, h_signal_child_handler);
		heredoc_loop(eof, sh, fd);
		free(file_name);
		delete_exec((t_exec *)branch);
		exit(0);
	}
	else
	{
		update_signal();
		wait_child(pid, status, sh);
	}
	return (file_name);
}
