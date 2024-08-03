/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_token_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 16:13:49 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/08/02 16:30:24 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_env_str(char *cmdl, int i)
{
	int		count;
	int		j;
	int		k;
	char	*env_var;

	j = i + 1;
	k = 0;
	count = 1;
	while (cmdl[j] && !special_char(cmdl[j]) && !is_space(cmdl[j]))
	{
		count++;
		j++;
	}
	env_var = s_malloc(sizeof(char) * (count));
	while (k < count)
		env_var[k++] = cmdl[i++];
	env_var[k] = '\0';
	return (env_var);
}

int	valid_env(char *env_var, t_env *env_head)
{
	t_env	*head;

	env_var = &env_var[1];
	head = env_head;
	while (head)
	{
		if (ft_strncmp(env_var, head->env_name, ft_strlen(env_var)) == 0)
			return (1);
		head = head->next;
	}
	return (0);
}

char	*expand_env_var(char *env_var, t_env *head)
{
	t_env	*tmp;
	char	*str;

	str = env_var;
	tmp = head;
	env_var++;
	while (tmp)
	{
		if (ft_strncmp(env_var, tmp->env_name, ft_strlen(env_var)) == 0)
			return (ft_strdup(tmp->env_value));
		tmp = tmp->next;
	}
	return (str);
}
