/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_through_tokens.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 16:11:41 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/10/15 08:56:11 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* funcao obsuleta(FO), deixei aqui por se acaso aka : F(funcao)O(obsuleta) */
t_token	*jump_token(t_token *token, int action)
{
	if (action == 1)
	{
		while (peek_token(token, 2, " ", "\t") == 1)
			token = token->next;
	}
	else if (action == 2)
	{
		token = token->next;
		while (peek_token(token, 2, " ", "\t") == 1)
			token = token->next;
	}
	return (token);
}

int	peek_token(t_token *checker, int var_nbr, ...)
{
	va_list	ptr;
	int		flag;
	int		i;
	char	*token;

	i = 0;
	flag = 1;
	if (!checker)
		return (0);
	token = checker->token;
	va_start(ptr, var_nbr);
	while (i < var_nbr)
	{
		flag = ft_strncmp(token, va_arg(ptr, char *), ft_strlen(token));
		if (flag == 0)
			return (1);
		i++;
	}
	va_end(ptr);
	return (0);
}

int	peek_future_tokens_type(t_token *head, t_type type)
{
	t_token	*tmp;

	tmp = head;
	while (tmp)
	{
		if (tmp->type == type)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
