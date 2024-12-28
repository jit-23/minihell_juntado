/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 06:43:53 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/12/28 05:49:08 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_redir	*handle_redir_type(t_shell *sh)
{
	char	*redir_type;
	t_redir	*red;

	redir_type = sh->rl->head->token;
	if (ft_strncmp(redir_type, "<", ft_strlen("<")) == 0)
		red = fill_redir(0, sh);
	else if (ft_strncmp(redir_type, ">", ft_strlen(">")) == 0)
		red = fill_redir(1, sh);
	else if (ft_strncmp(redir_type, ">>", ft_strlen(">>")) == 0)
		red = fill_redir(2, sh);
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

int	ft_strcmp(char *s1, const char *s2)
{
	unsigned char	*str1;
	unsigned char	*str2;
	int				n;
	int				n1;

	n = ft_strlen(s2);
	n1 = ft_strlen(s1);
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	if (n <= 0)
		return (-1);
	while (n1 > 0 && n > 0 && *str1 == *str2 && \
		*str1 != '\0' && *str2 != '\0')
	{
		str1++;
		str2++;
		n1--;
		n--;
	}
	if (n == 0 && n1 == 0)
		return (0);
	return (*str1 - *str2);
}

t_redir	*fill_redir(int mode, t_shell *sh)
{
	t_redir	*red;

	red = init_redir();
	while (sh->rl->head && sh->rl->head->type != WORD)
		sh->rl->head = sh->rl->head->next;
	if (!sh->rl->head)
	{
		ft_putstr_fd(2, " syntax error near unexpected token `newline'\n");
		return (NULL);
	}
	red->file = sh->rl->head->token;
	red->mode = mode;
	return (red);
}
