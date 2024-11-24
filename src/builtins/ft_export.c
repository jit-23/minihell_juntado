/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 21:30:54 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/11/24 21:56:34 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void display_it(t_env *display)
{
	if (display->env_name[0] == '_')
		return ;
	ft_putstr_fd(1, "declare -x ");
	ft_putstr_fd(1, display->env_name);
	ft_putstr_fd(1, "=");
	ft_putstr_fd(1, display->env_value);
	ft_putstr_fd(1, "\n");
}

void display_sorted_exported_envs(t_shell *sh)
{
	static int  index = 1;
	t_env *a = sh->ev;
	t_env *b = sh->ev->next;
	t_env *ptr;
	ptr = a;
	while(b)
	{
		if (aux(&ptr, &b, 1) == 1)
			break;
		if (aux(&ptr, &b, 2) == 1)
			break;
		if (strncmp(ptr->env_name, b->env_name, ft_strlen(ptr->env_name)) > 0)
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
	ptr->index = index++;
}

static void organized_export(t_shell *sh)
{
	int		flag;
	int		i;
	t_env	*a;

	a = sh->ev;
	i = -1;
	while(++i < ft_listsize(a))
		display_sorted_exported_envs(sh);
}

void manage_var(t_shell *sh, t_exec *exec)
{
	if (search_var(sh, exec->args[1]))
		delete_var(sh, exec->args[1]);
	insert_var(sh, exec->args[1], exec->args[3]);
}

void insert_var(t_shell *sh, char *a, char *c)
{
	t_env *new;
	t_env *last;

	new = sh->ev;
	while(new->next)
		new = new->next;
	last = new;
	new->next = malloc(sizeof(t_env));
	new = new->next;
	new->env_name = ft_strdup(a);
	if (c)
		new->env_value = ft_strdup("");
	else
		new->env_value = ft_strdup(c);
	new->next = NULL;
	new->prev = last;
}

void ft_export(t_shell *sh, t_exec *ex)
{
	if (!ex->args[1]) // export sozinho.
		organized_export(sh);
	else if (ex->args[1])
	{
		if (!ex->args[2]) // export "name"
			manage_var(sh,ex);
		else if (ex->args[2][0] != '=')
			perror("adsasdasddas\n");
		else if(ex->args[2][0] == '=' && !ex->args[3]) // export "name" "="  
			manage_var(sh, ex);
		else if (ex->args[2][0] == '=' && ex->args[3] && !ex->args[4])
			manage_var(sh, ex);
		else
			perror("invalid number of args\n");
	}
	else
		manage_var(sh, ex);
}