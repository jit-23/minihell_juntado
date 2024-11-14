/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:07:57 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/11/13 16:25:28 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* clear linked list for the env vars. */
#include "../includes/minishell.h"

void delete_hiden_files(t_shell *sh)
{
	int i;
	char *file_name;
	i = 65;

	while(i < sh->heredoc_tmp_file)
	{
		file_name = malloc(sizeof(char) * 3);
		file_name[0] = '.';
		file_name[1] = i++;
		file_name[2] = '\0';
		printf("deleting .%s.\n", file_name);
		unlink(file_name);
		free(file_name);
	}
}



void	delete_all(t_shell *shell)
{
	if (shell->cmd_line)
		free(shell->cmd_line);
	if (shell->prompt[0] != '\0')
		free(shell->prompt);
	if (shell->token_list)
		delete_token_lst(shell->token_list->official_head, \
			lst_size_tokens(shell->token_list->official_head));
	if (shell->rl)
		delete_token_lst(shell->rl->official_head, \
			lst_size_tokens(shell->rl->official_head));
	if (shell->rl)
		free(shell->rl);
	if (shell->token_list)
		free(shell->token_list);
	if (shell->root)
		delete_tree(shell->root);
	//if (shell->ev)
	//	delete_env_lst(shell->ev, lst_size_env(shell->ev));
	//if (shell->path)
	//	delete_path(shell->path, 0);
	//delete_hiden_files(shell);
	//ft_bzero((void *)shell, sizeof(shell));
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
		{
			//printf("DELETING %s\n", head->token);
			free(head->token);
			
		}
		if (head)
		{
			free(head);
			(head) = del;
		}
	}
}
