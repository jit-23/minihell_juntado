/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 23:43:38 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/12/28 00:47:55 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	display_it(t_env *display)
{
	if (display->env_name[0] == '_' && display->env_name[1] == '\0')
		return ;
	ft_putstr_fd(1, "declare -x ");
	ft_putstr_fd(1, display->env_name);
	ft_putstr_fd(1, "=");
	ft_putstr_fd(1, "\"");
	ft_putstr_fd(1, display->env_value);
	ft_putstr_fd(1, "\"");
	ft_putstr_fd(1, "\n");
}

void	display_sorted_exported_envs(t_shell *sh)
{
	t_env	*b;
	t_env	*ptr;

	b = sh->ev->next;
	ptr = sh->ev;
	while (b)
	{
		if (aux(&ptr, &b, 1) == 1)
			break ;
		if (aux(&ptr, &b, 2) == 1)
			break ;
		if (ft_strncmp(ptr->env_name, b->env_name, \
		ft_strlen(ptr->env_name)) > 0)
		{
			if (ptr->displayed == 0)
				ptr = b;
			b = b->next;
		}
		else
			b = b->next;
	}
	display_it(ptr);
	ptr->displayed = 1;
}

void	organized_export(t_shell *sh)
{
	int		i;
	t_env	*a;

	a = sh->ev;
	i = -1;
	while (++i < ft_listsize(a))
		display_sorted_exported_envs(sh);
	i = -1;
	while (a)
	{
		a->displayed = 0;
		a = a->next;
	}
	g_sign = 0;
}

int	search_var(t_shell *sh, char *var)
{
	t_env	*tmp;

	tmp = sh->ev;
	while (tmp)
	{
		if (0 == ft_strcmp(var, tmp->env_name))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
