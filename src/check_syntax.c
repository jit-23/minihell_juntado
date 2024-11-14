/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 03:30:16 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/11/13 14:16:11 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_pipe_sequence(t_token *token)
{
	while (token)
	{
		if ((token->type == PIPE && !token->next) || (token->type == PIPE
				&& !token->prev) || (token->type == PIPE && (token->next
					&& token->next->type == PIPE)))
		{
			ft_putstr_fd(2, "syntax error near unexpected token '|'\n");
			return (1);
		}
		token = token->next;
	}
	return (0);
}

int	check_redir_sequence(t_token *token)
{
	while (token)
	{
		if ((token->type == REDIR_IN && !token->next) ||
				(token->type == REDIR_IN && (token->next
					&& token->next->type == REDIR_IN)))
		{
			ft_putstr_fd(2, "syntax error near unexpected token `newline'\n");
			return (1);
		}
		else if ((token->type == REDIR_OUT && !token->next) ||
				(token->type == REDIR_OUT && (token->next
					&& token->next->type == REDIR_OUT)))
		{
			ft_putstr_fd(2, "syntax error near unexpected token `newline'\n");
			return (1);
		}
		token = token->next;
	}
	return (0);
}

int	check_syntax(t_shell *sh)
{
	t_token	*tmp;

	tmp = sh->token_list->official_head;
	if (check_pipe_sequence(tmp))
		return (1);
	tmp = sh->token_list->official_head;
	if (check_redir_sequence(tmp))
		return(1);
	return 0;
}
