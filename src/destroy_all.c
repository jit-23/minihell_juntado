/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:07:57 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/08/07 17:42:58 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* clear linked list for the env vars. */
#include "../includes/minishell.h"

void		delete_all(t_shell *shell)
{
	if (shell->cmd_line)
		free(shell->cmd_line);
	if (shell->prompt)
		free(shell->prompt);
	if (shell->token_list)
		delete_token_lst(shell->token_list->official_head, \
			lst_size_tokens(shell->token_list->official_head));
	if (shell->rl)
		delete_token_lst(shell->rl->official_head, \
			lst_size_tokens(shell->rl->official_head));
	if (shell->root)
		delete_tree(shell->root);
	if (shell->token_list)
		free(shell->token_list);
	if (shell->rl)
		free(shell->rl);
	if (shell->ev)
		delete_env_lst(shell->ev, lst_size_env(shell->ev));
}
/* clean_for_next_loop = obsuleta  */
void	clean_for_next_loop(t_shell *sh)
{
	if (sh->cmd_line)
		free(sh->cmd_line);
	if (sh->prompt)
		free(sh->prompt);
	if (sh->token_list->head)
		delete_token_lst(sh->token_list->head, \
			lst_size_tokens(sh->token_list->head));
	if (sh->root)
		delete_tree(sh->root);
}

void	delete_token_lst(t_token *head, int size)
{
	t_token	*del;
	int		i;

	i = -1;
	del = (head);
	while (++i < size)
	{
		del = del->next;
		if (head->token)
			free(head->token);
		if (head)
		{
			free(head);
			(head) = del;
		}
	}
}
