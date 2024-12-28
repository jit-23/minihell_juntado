/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 20:54:15 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/12/28 08:56:15 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_file_name(t_shell *sh)
{
	char	*file_n;

	file_n = (char *)ft_calloc(3, sizeof(char));
	file_n[0] = '.';
	file_n[1] = sh->heredoc_tmp_file++;
	file_n[2] = '\0';
	return (file_n);
}

int	open_hdoc_file(char *file_name, t_shell *sh)
{
	int	fd;

	fd = open(file_name, O_CREAT | O_WRONLY, 0777);
	if (fd < 0)
	{
		ft_putstr_fd(2, "Permission denied:\n");
		delete_all(sh);
		exit(126);
	}
	return (fd);
}

void	heredoc_loop(char *a, char *eof, t_shell *sh, int fd)
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
		ft_putstr_fd(fd, line);
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
	char	a[1024];
	char	*file_name;
	int		fd;
	pid_t	pid;
	int		status;

	file_name = get_file_name(sh);
	fd = open_hdoc_file(file_name, sh);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, h_signal_child_handler);
		heredoc_loop(a, eof, sh, fd);
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
