/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 07:30:46 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/12/29 15:44:59 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_space(int c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

int	special_char(char c)
{
	if (c == '>' || c == '<' || c == '\n' || c == '\'' \
		|| c == '\"' || c == '$'
		|| c == '|' || c == '=')
		return (1);
	return (0);
}

void	count_word_size_aux(int *i, int *count)
{
	(*i)++;
	(*count)++;
}

int	count_word_size(char *cmdl, int i, t_shell *sh, t_placing placing)
{
	int	count;

	(void)sh;
	count = 0;
	if (placing == DEFAULT)
	{
		while (cmdl[i] && !is_space(cmdl[i]) && !special_char(cmdl[i]))
			count_word_size_aux(&i, &count);
	}
	else if (placing == IN_DQ)
	{
		while (cmdl[i] && cmdl[i] != '\"' && \
			cmdl[i] != '\'' && cmdl[i] != '$')
			count_word_size_aux(&i, &count);
	}
	else if (placing == IN_SQ)
	{
		while (cmdl[i] && cmdl[i] != '\'' && cmdl[i] != '\"')
			count_word_size_aux(&i, &count);
	}
	return (count);
}

int	count_word_size_heredoc(char *cmdl, int i, t_shell *sh, t_placing placing)
{
	int	count;

	(void)sh;
	count = 1;
	if (placing == DEFAULT)
	{
		while (cmdl[i] && !is_space(cmdl[i]) && !special_char(cmdl[i]))
			count_word_size_aux(&i, &count);
	}
	else if (placing == IN_DQ)
	{
		while (cmdl[i] && cmdl[i] != '\"' && cmdl[i] != '$')
			count_word_size_aux(&i, &count);
	}
	else if (placing == IN_SQ)
	{
		while (cmdl[i] && cmdl[i] != '\'')
			count_word_size_aux(&i, &count);
	}
	return (count);
}
