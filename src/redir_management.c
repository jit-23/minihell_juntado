/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 06:43:53 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/08/02 16:52:16 by fde-jesu         ###   ########.fr       */
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
	if (strncmp(redir_type, ">", redir_type_len) == 0)
		red = fill_redir(">", 1, sh);
	else if (strncmp(redir_type, "<", redir_type_len) == 0)
		red = fill_redir("<", 0, sh);
	else if (strncmp(redir_type, ">>", redir_type_len) == 0)
		red = fill_redir("<", 2, sh);
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

t_redir	*fill_redir(char *s, int mode, t_shell *sh)
{
	t_redir	*red;
	t_token	*tmp;

	red = init_redir();
	while (sh->rl->head && sh->rl->head->type != WORD)
		sh->rl->head = sh->rl->head->next;
	red->file = sh->rl->head->token;
	printf("token in fill_redir - .%s.\n", sh->rl->head->token);
	printf("file in fill_redir - .%s.\n", red->file);
	red->mode = mode;
	return (red);
}
