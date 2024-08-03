/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_first_list_utils_1.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 16:22:12 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/08/02 16:30:38 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_space(char *cmdl, int i, t_shell *sh, t_placing placing)
{
	char	*space;

	space = ft_strdup(" ");
	add_to_list(sh->token_list, space, SPACE_BAR, placing);
	return (1);
}

int	handle_double_quotes_type(int quote_type, t_shell *sh, t_placing *placing)
{
	if (*placing == DEFAULT)
	{
		get_quote(sh, placing, quote_type);
		*placing = IN_DQ;
	}
	else if (*placing == IN_DQ)
	{
		*placing = DEFAULT;
		get_quote(sh, placing, quote_type);
	}
	else if (*placing == IN_SQ)
		get_quote(sh, placing, quote_type);
	return (1);
}

int	handle_single_quotes_type(int quote_type, t_shell *sh, t_placing *placing)
{
	if (*placing == DEFAULT)
	{
		get_quote(sh, placing, quote_type);
		*placing = IN_SQ;
	}
	else if (*placing == IN_SQ)
	{
		*placing = DEFAULT;
		get_quote(sh, placing, quote_type);
	}
	else if (*placing == IN_DQ)
		get_quote(sh, placing, quote_type);
	return (1);
}

int	get_quote(t_shell *sh, t_placing *placing, char quote_type)
{
	char	*quote_token;
	char	*s_quote;
	char	*d_quote;

	if (quote_type == '\'')
	{
		s_quote = strdup("\''");
		add_to_list(sh->token_list, s_quote, S_QUOTE, *placing);
	}
	else if (quote_type == '\"')
	{
		d_quote = strdup("\"");
		add_to_list(sh->token_list, d_quote, D_QUOTE, *placing);
	}
	return (1);
}
