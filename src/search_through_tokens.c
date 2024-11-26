/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_through_tokens.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 16:11:41 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/11/26 00:55:07 by fde-jesu         ###   ########.fr       */
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


/* VERIFICAR O PLACING DA 2 LISTA, NAO ESTA A SER BEM ANALISADA. */
int	peek_token(t_token *checker,int var_nbr, ...)
{
	va_list	ptr;
	int		flag;
	int		i;
	char	*token;

	i = -1;
	flag = 1;
	if (!checker)
		return (0);
	token = checker->token;
	va_start(ptr, var_nbr);
	while (++i < var_nbr)
	{
		flag = ft_strncmp(token, va_arg(ptr, char *), ft_strlen(token));
		//printf("flag = %d\t\n", flag);
		//printf("token - .%s.\n", token);
		//printf("checker->placing  = %d\t\n", checker->placing);
		//
		printf("checker->placing - %d\n", checker->placing);
		printf("flag = %d\n", flag);
		if (flag == 0 && (checker->placing == DEFAULT))
			return (1);
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
