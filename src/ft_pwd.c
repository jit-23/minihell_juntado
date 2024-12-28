/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 21:43:26 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/12/28 00:47:55 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_pwd(t_shell *sh)
{
	char	*dir;

	dir = NULL;
	dir = getcwd(dir, 100);
	ft_putstr_fd(1, dir);
	ft_putstr_fd(1, "\n");
	free(dir);
	g_sign = 0;
}

int	aux(t_env **ptr, t_env **b, int option)
{
	if (option == 1)
	{
		while ((*ptr)->displayed == 1)
		{
			(*ptr) = (*ptr)->next;
			if (!(*b)->next)
				return (1);
			(*b) = (*b)->next;
		}
	}
	else
	{
		while ((*b)->displayed == 1)
		{
			if ((*b)->next)
				(*b) = (*b)->next;
			else
				return (1);
		}
	}
	return (0);
}

void	update_pwds(t_shell *sh, char *old_pwd)
{
	t_env	*pwds;
	char	*dir;

	dir = NULL;
	dir = getcwd(dir, 100);
	pwds = search_env_var(sh, "OLDPWD");
	free(pwds->env_value);
	pwds->env_value = ft_strdup(old_pwd);
	pwds = search_env_var(sh, "PWD");
	free(pwds->env_value);
	pwds->env_value = ft_strdup(dir);
	free(dir);
}
