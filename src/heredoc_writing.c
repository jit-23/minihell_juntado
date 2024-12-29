/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_writing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 16:54:28 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/12/29 17:41:06 by fde-jesu         ###   ########.fr       */
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

/* ;;;;;;;;;;;;;;;;;;;;;;;;; */

t_env	*search_hdc_var(t_shell *sh, char *env_var)
{
	t_env	*search;
	char	*str;

	str = &env_var[1];
	search = sh->ev;
	while (search && ft_strcmp(str, search->env_name))
		search = search->next;
	if (!search)
		return (NULL);
	return (search);
}

static void	write_dollar(t_shell *sh, char *line, int fd)
{
	int		i;
	char	*s;

	s = NULL;
	i = 0;
	while (line[i] == '$' && line[i + 1] == '$')
	{
		ft_putnbr_fd((int)getpid(), fd);
		i += 2;
	}
	s = &line[i];
	ft_putstr_fd(fd, s);
	ft_putstr_fd(fd, "\n");
}

void	write_line(t_shell *sh, char *line, int fd)
{
	t_env	*t_str;
	char	*str;

	str = NULL;
	t_str = search_hdc_var(sh, line);
	if (line[0] == '$' && line[1] != '\0')
	{
		if (line[i] == '$' && line[i + 1] == '$')
			write_dollar(sh, line, fd);
		else
		{
			if (t_str)
				str = t_str->env_value;
			if (!str)
				ft_putstr_fd(fd, "");
			else
				ft_putstr_fd(fd, str);
			ft_putstr_fd(fd, "\n");
		}
		return ;
	}
	ft_putstr_fd(fd, line);
	ft_putstr_fd(fd, "\n");
}
