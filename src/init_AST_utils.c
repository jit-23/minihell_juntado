/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_AST_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 01:50:19 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/12/28 07:27:57 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	delete_all_paths(char **path, int i)
{
	while (path[i])
		free(path[i++]);
	free(path);
}

void	init_var(t_redir **ret, t_redir **tmp, t_redir **tmp2)
{
	(*ret) = NULL;
	(*tmp) = NULL;
	(*tmp2) = NULL;
}

t_token	*get_prev(t_shell *sh)
{
	t_token	*prev;

	if (sh->rl->head->prev)
		prev = sh->rl->head->prev;
	else
		prev = NULL;
	return (prev);
}
