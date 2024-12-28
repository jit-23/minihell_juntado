/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_token_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 16:13:49 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/12/07 04:03:20 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*get_exit_code_var(int option)
{
	char	*dollar;

	if (option == 2)
	{
		dollar = (char *)malloc(sizeof(char) * 3);
		dollar[0] = '$';
		dollar[1] = '?';
		dollar[2] = '\0';
	}
	else if (option == 1)
	{
		dollar = (char *)malloc(sizeof(char) * 2);
		dollar[0] = '$';
		dollar[1] = '\0';
	}
	return (dollar);
}

char	*get_env_str(char *cmdl, int i)
{
	int		count;
	int		j;
	int		k;
	char	*env_var;

	j = i + 1;
	k = 0;
	count = 1;
	if (cmdl[i] == '$' && cmdl[i + 1] == '?')
		return (get_exit_code_var(2));
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
	if (!env_var)
		return (0);
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
