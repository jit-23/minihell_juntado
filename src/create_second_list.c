/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_second_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 04:46:05 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/11/26 00:36:56 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_token(t_shell *sh, char *token)
{
	char	*to_send;

	to_send = ft_strdup(token);
	/*	if (sh->token_list->head->placing == 0)
		printf("INSQ\n");
	if (sh->token_list->head->placing == 1)
		printf("INDQ\n"); */
	add_to_refined_list(sh->rl, to_send, sh->token_list->head->type, sh->token_list->head->placing);
	sh->token_list->head = sh->token_list->head->next;
}

void	add_to_refined_list(t_lexer *token_refined, char *word, t_type type, t_placing placing)
{
	t_token	*head;
	t_token	*prev;
	t_token	*last;
	char	*s;

	s = strdup(word);
	if (!token_refined->head)
	{
		token_refined->head = new_node(s, type, placing);
		token_refined->head->prev = NULL;
		token_refined->head->placing = placing;
		token_refined->official_head = token_refined->head;
		free(word);
		return ;
	}
	last = ft_lstlast(token_refined->head);
	last->next = new_node(s, type, placing);
	prev = last;
	last->placing = placing;
	last = last->next;
	last->prev = prev;
	free(word);
}

void	handle_word_token(t_shell *sh)
{
	char	*w;
	char	*a;
	t_token	*og;

	og = sh->token_list->head;
	a = NULL;
	w = ft_strdup("");
	while (sh->token_list->head && (sh->token_list->head->type == ENV
			|| sh->token_list->head->type == WORD
			|| sh->token_list->head->type == S_QUOTE
			|| sh->token_list->head->type == D_QUOTE))
	{
		if (sh->token_list->head->type == ENV
			|| sh->token_list->head->type == WORD)
		{
			a = ft_strjoin(w, sh->token_list->head->token);
			free(w);
			w = a;
		}
		sh->token_list->head = sh->token_list->head->next;
	}
	add_to_refined_list(sh->rl, w, og->type, og->placing);
}

void	refine_token_list(t_shell *sh)
{
	while (sh->token_list->head)
	{
		if (sh->token_list->head->type == WORD)
			handle_word_token(sh);
		else if (sh->token_list->head->type == SPACE_BAR)
			handle_token(sh, " ");
		else if (sh->token_list->head->type == ENV)
			handle_word_token(sh);
		else if (sh->token_list->head->type == S_QUOTE
			|| sh->token_list->head->type == D_QUOTE)
			sh->token_list->head = sh->token_list->head->next;
		else if (sh->token_list->head->type == PIPE)
			handle_token(sh, "|");
		else if (sh->token_list->head->type == REDIR_IN)
			handle_token(sh, "<");
		else if (sh->token_list->head->type == REDIR_OUT)
			handle_token(sh, ">");
		else if (sh->token_list->head->type == HEREDOC)
			handle_token(sh, "<<");
		else if (sh->token_list->head->type == _APPEND)
			handle_token(sh, ">>");
		else if (sh->token_list->head->type == EQUAL)
			handle_token(sh, "=");
	}
}
