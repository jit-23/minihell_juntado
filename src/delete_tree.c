/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 06:13:01 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/12/28 06:57:48 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	delete_exec(t_exec *ex)
{
	int	i;

	i = 1;
	if (!ex->args[0])
	{
		free(ex);
		return ;
	}
	if (ex->first_cmd == 1 || is_builtin(ex->args[0]) || \
		is_possible_path(ex->args[0]) || access(ex->args[0], X_OK) != 0 || \
		ex->args[0][0] == '.')
		free(ex->args[0]);
	while (ex->args[i])
		free(ex->args[i++]);
	ft_memset((void *)ex->args, 0, sizeof(ex->args));
	free(ex);
}

void	delete_pipe(t_pipe *pp)
{
	free(pp);
}

void	delete_redir(t_redir *redir)
{
	if (redir->mode == 3)
	{
		printf("rd\n");
		free(redir->file);
	}
	free(redir);
}

void	delete_tree(t_cmd *root)
{
	t_redir	*redir;
	t_pipe	*pp;

	if (root == NULL)
		return ;
	if (root->type == _EXEC)
		delete_exec((t_exec *)root);
	else if (root->type == _REDIR)
	{
		redir = (t_redir *)root;
		delete_tree((t_cmd *)redir->cmd);
		delete_redir(redir);
	}
	else if (root->type == _PIPE)
	{
		pp = (t_pipe *)root;
		delete_tree((t_cmd *)pp->left);
		delete_tree((t_cmd *)pp->right);
		delete_pipe(pp);
	}
}
