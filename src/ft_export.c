/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 21:30:54 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/12/28 00:47:55 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	insert_var(t_shell *sh, char *a, char *c)
{
	t_env	*new;
	t_env	*last;

	new = sh->ev;
	while (new->next)
		new = new->next;
	last = new;
	new->next = malloc(sizeof(t_env));
	new = new->next;
	new->env_name = ft_strdup(a);
	if (!c)
		new->env_value = ft_strdup("");
	else
		new->env_value = ft_strdup(c);
	new->next = NULL;
	new->prev = last;
	new->index = -1;
	new->displayed = 0;
}

static int	check_export_str(char *str)
{
	int	i;

	i = -1;
	if (ft_isdigit(str[0]))
		return (1);
	while (str[++i])
		if (str[i] == '-' || str[i] == '+' || str[i] == '=')
			return (1);
	return (0);
}

void	manage_var(t_shell *sh, char *name, char *value)
{
	if (search_var(sh, name))
		delete_var(sh, name);
	insert_var(sh, name, value);
}

void	ft_export_error_msg(t_shell *sh, char *msg)
{
	ft_putstr_fd(2, "export: ");
	ft_putstr_fd(2, msg);
	ft_putstr_fd(2, " : not a valid identifier\n");
	g_sign = 1;
}

int	ft_export(t_shell *sh, t_exec *ex)
{
	int	i;

	i = 1;
	if (!ex->args[1])
		return (organized_export(sh), 0);
	while (ex->args[i])
	{
		if (check_export_str(ex->args[i]))
			return (ft_export_error_msg(sh, ex->args[i]), 1);
		if (ex->args[i] && (ex->args[i + 1] && ex->args[i + 1][0] == '='))
		{
			manage_var(sh, ex->args[i], ex->args[i + 2]);
			if (ex->args[2])
				i += 3;
			else
				break ;
		}
		else if (ex->args[i])
		{
			manage_var(sh, ex->args[i], ex->args[i + 2]);
			i++;
		}
	}
	return (0);
}
