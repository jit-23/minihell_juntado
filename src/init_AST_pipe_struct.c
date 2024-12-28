/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_AST_pipe_struct.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 01:49:05 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/12/08 01:57:13 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_pipe	*last_pipe(t_pipe *root)
{
	t_pipe	*last_p;

	last_p = root;
	while (last_p && last_p->type == _PIPE)
	{
		if (last_p->right && last_p->right->type == _PIPE)
			last_p = (t_pipe *)last_p->right;
		else
			break ;
	}
	return (last_p);
}

int	one_pipe_token(t_token *head, t_type type)
{
	t_token	*tmp;
	int		counter;

	counter = 0;
	tmp = head;
	while (tmp)
	{
		if (tmp->type == type)
			counter++;
		tmp = tmp->next;
	}
	if (counter == 1)
		return (1);
	return (0);
}
