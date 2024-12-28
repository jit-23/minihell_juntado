/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_AST.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 00:11:53 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/12/28 07:28:02 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmd	*exec_parse(t_shell *sh, t_exec *exec_struct)
{
	int		i;
	t_cmd	*branch_root;
	t_token	*prev;

	i = 0;
	prev = get_prev(sh);
	branch_root = (t_cmd *)exec_struct;
	if (sh->rl->head->type == '|')
		sh->rl->head = sh->rl->head->next;
	while (sh->rl->head && peek_token(sh->rl->head, 1, "|") == 0)
	{
		branch_root = parse_redir((t_cmd *)branch_root, sh);
		if (!sh->rl->head)
			break ;
		if (sh->rl->head && (sh->rl->head->type == WORD
				|| sh->rl->head->type == ENV || sh->rl->head->type == HEREDOC
				|| sh->rl->head->type == EQUAL))
			i += get_tkn(i, exec_struct, branch_root, sh);
		else if (sh->rl->head->type == ' ')
			sh->rl->head = sh->rl->head->next;
	}
	exec_struct->args[i] = NULL;
	if (prev == NULL)
		sh->root = (t_cmd *)branch_root;
	return ((t_cmd *)branch_root);
}

t_cmd	*parse_redir(t_cmd *branch_root, t_shell *sh)
{
	t_redir	*ret;
	t_redir	*tmp;
	t_redir	*tmp2;

	init_var(&ret, &tmp, &tmp2);
	ret = (t_redir *)branch_root;
	while (peek_token(sh->rl->head, 3, ">", ">>", "<"))
	{
		tmp = handle_redir_type(sh);
		if (!tmp)
			break ;
		if (ret && ret->type == _EXEC)
		{
			tmp->cmd = (t_cmd *)ret;
			ret = tmp;
		}
		else if (ret && ret->type == _REDIR)
		{
			tmp2 = get_last_redir((t_cmd *)ret);
			tmp->cmd = (t_cmd *)tmp2->cmd;
			tmp2->cmd = (t_cmd *)tmp;
		}
		sh->rl->head = sh->rl->head->next;
	}
	return ((t_cmd *)ret);
}

void	handle_branch(t_shell *sh, t_pipe *pp)
{
	pp = init_pipe();
	pp->left = sh->root;
	sh->root = (t_cmd *)pp;
	if (peek_future_tokens_type(sh->rl->head, PIPE))
		pipe_parse(sh);
	else
		pp->right = exec_parse(sh, init_exec());
}

t_cmd	*pipe_parse(t_shell *sh)
{
	t_pipe	*pp;
	t_pipe	*lp;

	lp = NULL;
	pp = NULL;
	if (sh->rl->head && sh->rl->head->type == _PIPE)
		sh->rl->head = sh->rl->head->next;
	if (sh->root->type == _EXEC || sh->root->type == _REDIR)
		handle_branch(sh, pp);
	else if (sh->root->type == _PIPE)
	{
		lp = last_pipe((t_pipe *)sh->root);
		if (one_pipe_token(sh->rl->head, PIPE))
		{
			lp->right = exec_parse(sh, init_exec());
			return (NULL);
		}
		pp = init_pipe();
		lp->right = (t_cmd *)pp;
		pp->left = exec_parse(sh, init_exec());
		if (peek_future_tokens_type(sh->rl->head, PIPE))
			return (pipe_parse(sh), NULL);
	}
	return ((t_cmd *)pp);
}

void	init_ast(t_shell *sh)
{
	exec_parse(sh, init_exec());
	if (!sh->rl->head)
		return ;
	pipe_parse(sh);
}
