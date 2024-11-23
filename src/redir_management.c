/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 06:43:53 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/11/14 17:46:57 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_redir	*handle_redir_type(t_shell *sh)
{
	char	*redir_type;
	int		redir_type_len;
	t_redir	*red;

	redir_type = sh->rl->head->token;
	redir_type_len = ft_strlen(redir_type);
	if (strncmp(redir_type, "<", redir_type_len) == 0)
		red = fill_redir("<", 0, sh);
	else if (strncmp(redir_type, ">", redir_type_len) == 0)
		red = fill_redir(">", 1, sh);
	else if (strncmp(redir_type, ">>", redir_type_len) == 0)
		red = fill_redir(">>", 2, sh);
	else if (strncmp(redir_type, "<<", redir_type_len) == 0)
		red = fill_redir("<<", 3, sh);/* red = fill_heredoc(3, sh); */
	return (red);
}

t_redir	*get_last_redir(t_cmd *sub_root)
{
	t_redir	*tmp;

	tmp = (t_redir *)sub_root;
	while (tmp->cmd && tmp->cmd->type == _REDIR)
		tmp = (t_redir *)tmp->cmd;
	return (tmp);
}

static char *execute_heredoc(t_redir *red, t_shell *sh)
{
	char *a;
	char *file_name;
	int fd;
	pid_t pid;
	int status;

	a = " ";
	file_name = malloc(sizeof(char) * 3);
	file_name[0] = '.';
	file_name[1] = sh->heredoc_tmp_file++;
	file_name[2] = '\0';
	fd = open(file_name, O_CREAT | O_WRONLY, 0777);
	if (fd < 0)
		perror("ERROR\n");
	pid = fork();
	if (pid == 0)
	{
		while(a)
		{
			a = get_next_line(1);
			if (a)
			{
				if (ft_strncmp(a, red->file, ft_strlen(red->file)) == 0)
				{
					free(a);
					delete_all(sh);
					exit(0);
				}
				ft_putstr_fd(fd, a);
			}
		}
		if (a)
			free(a);
		delete_all(sh);
	}
	else
	/* atualizar o signal do pai, para ignorar cntrl + c */
		waitpid(pid, &status, 0);// exit code also
	return (file_name);
}

t_redir	*fill_redir(char *s, int mode, t_shell *sh)
{
	t_redir	*red;
	t_token	*tmp;

	red = init_redir();
	while (sh->rl->head && sh->rl->head->type != WORD)
		sh->rl->head = sh->rl->head->next;
	if (!sh->rl->head)
	{
		ft_putstr_fd(2, " syntax error near unexpected token `newline'\n");
		//delete_all(sh);
		return(NULL);
	}
	red->file = sh->rl->head->token;
	red->mode = mode;
	if (mode == 3)
		red->file = execute_heredoc(red, sh);
	return (red);
}
