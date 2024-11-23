/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_AST.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 00:11:53 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/11/23 19:34:55 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		get_tkn(int i, t_exec *exec ,char *token, t_shell *sh);
t_pipe	*last_pipe(t_pipe *root);
int		one_pipe_token(t_token *head, t_type type);
char	*get_right_path(char *token, t_shell *sh,  t_exec *ex);
char	*check_access(char **all_paths, t_exec *ex);
int		is_possible_path(char *token);

int is_possible_path(char *token)
{
	int i;

	i = 0;
	if (ft_strnstr(token, "/bin", ft_strlen("/bin")) ||\
		ft_strnstr(token, "/usr/bin", ft_strlen("/usr/bin")) ||\
		ft_strnstr(token, "/sbin", ft_strlen("/sbin")) ||\
		ft_strnstr(token, "/usr/sbin", ft_strlen("/usr/sbin")))
			return (1);
	return (0);
}

int get_tkn(int i, t_exec *exec ,char *token, t_shell *sh)
{
	
	if (i != 0)
		exec->args[i] = ft_strdup(token);
	if (i == 0)
	{
		if (is_builtin(token))
			exec->args[i] = ft_strdup(token);
		else if (is_possible_path(token))
			exec->args[i] = ft_strdup(token);
		else
			exec->args[i] = get_right_path(token, sh, exec);
	}
	sh->rl->head = sh->rl->head->next;
	return (1);
}

t_pipe *last_pipe(t_pipe *root)
{
	t_pipe *last_p;
	t_exec *e;
	last_p = root;
	while(last_p && last_p->type == _PIPE)
	{
		e = (t_exec *)last_p->left;
		if (last_p->right && last_p->right->type == _PIPE)
			last_p = (t_pipe *)last_p->right;
		else
			break ;
	}
	return (last_p);
}

int one_pipe_token(t_token *head, t_type type)
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
	if (counter == 1) // there is only one pipe, therefore asign right and left to execs
		return (1);
	return (0);
}

t_cmd	*exec_parse(t_shell *sh, t_exec *exec_struct)
{
	int		i;
	t_cmd	*branch_root;
	t_token	*prev;

	i = 0;
	prev = sh->rl->head->prev;
	branch_root = (t_cmd *)exec_struct;
	if (sh->rl->head->type == '|')
		sh->rl->head = sh->rl->head->next;
	while (sh->rl->head && peek_token(sh->rl->head, 1, "|") == 0)
	{
		branch_root = parse_redir((t_cmd *)branch_root, sh);
		if (!sh->rl->head)
			break ;
		if (sh->rl->head && sh->rl->head->type == WORD 
			|| sh->rl->head->type == ENV || sh->rl->head->type == EQUAL)
			i += get_tkn(i, exec_struct, sh->rl->head->token, sh);
		else if (sh->rl->head->type == ' ')
			sh->rl->head = sh->rl->head->next;
	}
	exec_struct->args[i] = NULL;
	if (prev == NULL)
		sh->root = (t_cmd *)branch_root;
	return ((t_cmd *)branch_root);
}

static void *a(t_shell *sh, t_cmd *idk)
{
	t_exec *exec;

	exec = NULL;
	if (idk->type == 2)
		exec = (t_exec *)idk;
	if (!exec->args[0])
		return (NULL);
	return (exec);
}

t_cmd	*parse_redir(t_cmd *branch_root, t_shell *sh)
{
	t_redir	*ret = NULL;
	t_redir	*tmp = NULL;
	t_redir	*tmp2 = NULL;

	ret = (t_redir *)branch_root/* a(sh, branch_root) */; // este brach e um exec automaticamente.
	while (peek_token(sh->rl->head,  4, ">", "<<", ">>", "<"))
	{
		tmp = handle_redir_type(sh);
		if (!tmp)
			break ;
		if (ret && ret->type == _EXEC)
		{
			tmp->cmd = (t_cmd *)ret;
			ret = tmp;
		}
		else if (ret &&ret->type == _REDIR)
		{
			tmp2 = get_last_redir((t_cmd *)ret);
			tmp->cmd = (t_cmd *)tmp2->cmd;
			tmp2->cmd = (t_cmd *)tmp;
		}
		sh->rl->head = sh->rl->head->next;
	}
	return ((t_cmd *)ret);
}

void delete_all_paths(char **path, int i)
{
	while(path[i])
		free(path[i++]);
	free(path);
}

char *check_access(char **all_paths, t_exec *ex)
{
	int i;
	char *executable;

	i = -1;
	while(all_paths[++i])
		if (access(all_paths[i], X_OK) == 0)
		{
			ex->first_cmd = 1;
			executable = ft_strdup(all_paths[i]);
			delete_all_paths(all_paths, 0);
			return (executable);
		}
	delete_all_paths(all_paths, 0);
	return (NULL);
}

char *get_right_path(char *token, t_shell *sh, t_exec *ex)
{
	char **all_possible_path;
	char *cmd;
	char *new_tkn;
	int i;
	int j;

	i = -1;
	j = -1;
	cmd = ft_strjoin("/", token);
	while(sh->path[++j]);
	all_possible_path =  (char **)malloc(sizeof(char *) * (j + 1));
	if (!all_possible_path)
		printf("ERRORRRRR\n");
	while(sh->path[++i])
		all_possible_path[i] = ft_strjoin(sh->path[i], cmd);
	all_possible_path[i] = NULL;
	free(cmd);
	new_tkn = check_access(all_possible_path, ex);
	if (!new_tkn)
		return (token);
	return (new_tkn);
}



//t_cmd	*exec_parse(t_shell *sh, t_exec *exec_struct)
//{
//	int		i;
//	t_cmd	*branch_root;
//	t_token	*prev;
//
//	i = 0;
//	prev = sh->rl->head->prev;
//	branch_root = (t_cmd *)exec_struct;
//	if (sh->rl->head->type == '|')
//		sh->rl->head = sh->rl->head->next;
//	while (sh->rl->head && peek_token(sh->rl->head, 1, "|") == 0)
//	{
//		branch_root = parse_redir((t_cmd *)branch_root, sh);
//		if (!sh->rl->head)
//			break ;
//		if (sh->rl->head && sh->rl->head->type == WORD
//			|| sh->rl->head->type == ENV)
//		{
//			//exec_struct->args[i++] = get_tkn(i, sh->rl->head->token, sh);
//			exec_struct->args[i++] = ft_strdup(sh->rl->head->token);
//			sh->rl->head = sh->rl->head->next;
//		}
//		else
//			sh->rl->head = sh->rl->head->next;
//	}
//	exec_struct->args[i] = NULL;
//	if (prev == NULL)
//		sh->root = (t_cmd *)branch_root;
//	return ((t_cmd *)branch_root);
//}

void	init_ast(t_shell *sh)
{
	exec_parse(sh, init_exec());
	if (!sh->rl->head)
		return ;
	pipe_parse(sh);
}

t_cmd *pipe_parse(t_shell *sh)
{
	t_pipe *pp;
	t_pipe *lp;

	lp = NULL;
	pp = NULL;
	if (sh->rl->head && sh->rl->head->type == _PIPE)
		sh->rl->head = sh->rl->head->next;
	if (sh->root->type == _EXEC || sh->root->type == _REDIR)
	{
		pp = init_pipe();
		pp->left = sh->root;
		sh->root = (t_cmd *)pp;
		if (peek_future_tokens_type(sh->rl->head, PIPE))
			pipe_parse(sh);
		else
			pp->right = exec_parse(sh, init_exec());
	}
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

