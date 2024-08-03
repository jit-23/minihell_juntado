/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_first_list_utils_2.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 16:22:12 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/08/02 16:31:58 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_rid_off(char *alloced_mem)
{
	int	len;

	len = ft_strlen(alloced_mem);
	free(alloced_mem);
	return (len);
}

int	get_word(char *cmdl, int i, t_shell *sh, t_placing placing)
{
	int		j;
	int		count;
	char	*token;

	count = 0;
	j = -1;
	count = count_word_size(cmdl, i, count, placing);
	token = ft_calloc(count, sizeof(char) * (count + 1));
	while (++j < count)
		token[j] = cmdl[i + j];
	token[j] = '\0';
	add_to_list(sh->token_list, token, WORD, placing);
	return (count);
}

int	get_env_var(char *cmdl, int i, t_shell *sh, t_placing placing)
{
	char	*env_var;
	char	*expanded_var;

	env_var = get_env_str(cmdl, i);
	if (valid_env(env_var, sh->ev) == 1)
	{
		if (placing == IN_SQ)
		{
			expanded_var = strdup(env_var);
			add_to_list(sh->token_list, expanded_var, WORD, IN_SQ);
		}
		else
		{
			expanded_var = expand_env_var(env_var, sh->ev);
			add_to_list(sh->token_list, expanded_var, WORD, DEFAULT);
		}
		return (get_rid_off(env_var));
	}
	if (placing == IN_SQ)
	{
		expanded_var = ft_strdup(env_var);
		add_to_list(sh->token_list, expanded_var, WORD, IN_SQ);
	}
	return (get_rid_off(env_var));
}

int	get_pipe(t_shell *sh, t_placing placing)
{
	char	*pipe_var;

	pipe_var = (char *)s_malloc(sizeof(sizeof(char) * 2));
	pipe_var[1] = '\0';
	pipe_var[0] = '|';
	add_to_list(sh->token_list, pipe_var, PIPE, placing);
	return (1);
}
