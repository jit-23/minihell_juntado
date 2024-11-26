/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 21:51:14 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/11/25 21:17:27 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void ft_unset(t_shell *sh, t_exec *ex)
{
	if (ex->args[1])
		delete_var(sh, ex->args[1]);
	sh->exitcode = 0;
}

t_env *search_env_var(t_shell *sh, char *env_var)
{
	t_env *search;

	search = sh->ev;
	//printf("search  - .%s.\n", search->env_name);
	//printf("env_var - .%s.\n", env_var);
	while(search && strncmp(env_var, search->env_name, ft_strlen(env_var)))
		search = search->next;
	
	if (!search)
	{
		printf("empty\n");
		return (NULL);
	}
	
	return (search);
}

void delete_var(t_shell *sh, char *env_var)
{
	t_env *target;
	t_env *prev;
	t_env *next;

	target = search_env_var(sh, env_var);
	if (!target)
		return ;

	prev = target->prev;
	next = target->next;
	prev->next = next;
	if (next)
		next->prev = prev;
	free(target->env_name);
	free(target->env_value);
	free(target);
	//t_env *a = sh->ev;
}