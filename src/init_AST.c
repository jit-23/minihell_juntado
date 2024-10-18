/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_AST.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 00:11:53 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/10/19 00:41:23 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
/* t_cmd	*pipe_parse(t_shell *sh, t_cmd *right)
{
	t_pipe	*pipe_struct;
                              
	pipe_struct = init_pipe();
	//pipe_struct->left = left;
	pipe_struct->right = right;
	sh->root = (t_cmd *)pipe_struct;
	if (sh->rl->head->next)
		sh->rl->head = sh->rl->head->next;
	if (peek_future_tokens_type(sh->rl->head, PIPE))
	{                            
		pipe_struct->right = exec_parse(sh, init_exec());
		pipe_parse(sh, (t_cmd *)sh->root);
	}                              
	else if (peek_future_tokens_type(sh->rl->head, WORD))
		pipe_struct->right = exec_parse(sh, init_exec());
	return ((t_cmd *)pipe_struct);
} */

static t_pipe *last_pipe(t_pipe *root)
{
	t_pipe *last_p;
	t_exec *e;
	last_p = root;
	while(last_p && last_p->type == _PIPE)
	{
		e = (t_exec *)last_p->left;
		printf("cmd - %s\n", e->args[0]);
		printf("\titerations\n");
		if (last_p->right && last_p->right->type == _PIPE)
			last_p = (t_pipe *)last_p->right;
		else
			break ;
	}
	return (last_p);
}

static int one_pipe_token(t_token *head, t_type type)
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

// t_cmd *pipe_parse(t_shell *sh)
// {
// 	t_pipe *pp = init_pipe();
// 	t_pipe *lp;

// 	lp = NULL;
// 	printf("\t\t\t\t\tsh->rl->head - .%s.\n", sh->rl->head->token);
// 	if (sh->rl->head && sh->rl->head->type == PIPE)
// 		sh->rl->head = sh->rl->head->next;
// 	printf("\t\t\t\t\t(post)sh->rl->head - .%s.\n", sh->rl->head->next->token);
// 	if (sh->root->type == _EXEC)
// 	{
// 		//printf("1\n");
// 		pp->left = sh->root;
// 		sh->root = (t_cmd *)pp;
// 		printf("token in the first iteration: %s\n", sh->rl->head->token);
// 		if (peek_future_tokens_type(sh->rl->head, PIPE))
// 		{
// 			pipe_parse(sh);
// 		}
// 		else
// 			pp->right = exec_parse(sh, init_exec());
// 	}
// 	else if (sh->root->type == _PIPE)
// 	{
// 		lp = last_pipe((t_pipe *)sh->root);
// 		if (one_pipe_token(sh->rl->head, PIPE))
// 		{
// 			free(pp);
// 			lp->right = exec_parse(sh, init_exec());
// 			return (NULL);
// 		}
// 		/* aqui decido o que fazer, (analiso se est e o ultimo pipe) se 
// 		houver mais continua, caso contrario luda de forma simples */
// 		lp->right = (t_cmd *)pp;
// 		pp->left = exec_parse(sh, init_exec());
// 		if (peek_future_tokens_type(sh->rl->head, PIPE))
// 		{
// 			pipe_parse(sh);
// 		}
// 		else
// 		{
// 			pp->right = (t_cmd *)exec_parse(sh, init_exec());  //pk e que este pp nao functiona? nao existe>?
// 		}
// 	}
// 	return ((t_cmd *)pp);
// }

/*

t_cmd	*pipe_parse(t_shell *sh, t_cmd *left)
{
	t_pipe	*pipe_struct;

	pipe_struct = init_pipe();
	pipe_struct->left = left;
	sh->root = (t_cmd *)pipe_struct;
	if (sh->refined_list->head->next)
		sh->refined_list->head = sh->refined_list->head->next;
	if (peek_future_tokens_type(sh->refined_list->head, PIPE))
	{
		pipe_struct->right = exec_parse(sh, init_exec());
		pipe_parse(sh, (t_cmd *)sh->root);
	}
	else if (peek_future_tokens_type(sh->refined_list->head, WORD))
		pipe_struct->right = exec_parse(sh, init_exec());
	return ((t_cmd *)pipe_struct);
}  */

// t_cmd	*pipe_parse(t_shell *sh/* , t_cmd *left */)
// {
// 	t_pipe	*lp; // last_pipe;
// 	t_pipe	*pipe_struct;

// 	pipe_struct = init_pipe();
// 	if (sh->rl->head->next)
// 		sh->rl->head = sh->rl->head->next;
// 	if (peek_future_tokens_type(sh->rl->head, PIPE))
// 	{
// 		lp = last_pipe((t_pipe *)sh->root);
// 		lp->right = pipe_struct;
// 		pipe_struct->left = exec_parse(sh, init_exec());
// 		pipe_parse(sh);
// 	}
// 	return ((t_cmd *)pipe_struct);
// }

t_cmd	*parse_redir(t_cmd *branch_root, t_shell *sh)
{
	t_redir	*ret;
	t_redir	*tmp;
	t_redir	*tmp2;

	ret = (t_redir *)branch_root;
	while (peek_token(sh->rl->head, 4, ">", "<<", ">>", "<"))
	{
		tmp = handle_redir_type(sh);
		if (ret->type == _EXEC)
		{
			tmp->cmd = (t_cmd *)ret;
			ret = tmp;
		}
		else if (ret->type == _REDIR)
		{
			tmp2 = get_last_redir((t_cmd *)ret);
			tmp->cmd = (t_cmd *)tmp2->cmd;
			tmp2->cmd = (t_cmd *)tmp;
		}
		if (sh->rl->head->next->type != '|')
			sh->rl->head = sh->rl->head->next;
	}
	return ((t_cmd *)ret);
}

static char *check_access(char **all_paths)
{
	int i;
	char *executable;

	i = -1;
	printf("%s\n", all_paths[0]);
	while(all_paths[++i])
		if (access(all_paths[i], X_OK) == 0)
		{
			executable = ft_strdup(all_paths[i]);
			printf("\t\t\t\texecutable - %s\n", executable);
			return (executable);
		}
	return (NULL);
}

static char *get_right_path(char *token, t_shell *sh)
{
	char **all_possible_path;
	char *cmd;
	char *new_tkn;
	int i;
	int j;

	i = -1;
	j = -1;
	printf("INICIO\n");
	cmd = ft_strjoin("/", token);
	while(sh->path[++j]);
	all_possible_path =  (char **)malloc(sizeof(char *) * (j + 1));
	if (!all_possible_path)
		printf("ERRORRRRR\n");
	printf("INICIO1\n");
	while(sh->path[++i])
	{
		all_possible_path[i] = ft_strjoin(sh->path[i], cmd);
	}
	printf("INICIO2\n");
	all_possible_path[i] = NULL;
	printf("AFTER check access\n");
	new_tkn = check_access(all_possible_path);
	printf("BEOFRE check access\n");
	if (!new_tkn)
		return (token);
	return (new_tkn);
}

static int get_tkn(int i, t_exec *exec ,char *token, t_shell *sh)
{
	if (i != 0)
		exec->args[i] = ft_strdup(token);
	if (i == 0)
	{
		exec->args[i] = get_right_path(token, sh);
		printf("exec->args[%d] - %s\n", i, exec->args[i]);
	}
	return (1);
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
			|| sh->rl->head->type == ENV)
		{
			//exec_struct->args[i] = get_tkn(i, sh->rl->head->token, sh);
			//i += get_tkn(i,exec_struct , sh->rl->head->token, sh);
			exec_struct->args[i++] = ft_strdup(sh->rl->head->token);
			sh->rl->head = sh->rl->head->next;
		}
		else
			sh->rl->head = sh->rl->head->next;
	}
	exec_struct->args[i] = NULL;
	if (prev == NULL)
		sh->root = (t_cmd *)branch_root;
	return ((t_cmd *)branch_root);
}

void	init_ast(t_shell *sh)
{
	exec_parse(sh, init_exec());
	if (!sh->rl->head)
		return ;
	pipe_parse(sh/* , sh->root */);
}

t_cmd *pipe_parse(t_shell *sh)
{
	t_pipe *pp = init_pipe();
	t_pipe *lp;

	lp = NULL;
	if (sh->rl->head && sh->rl->head->type == _PIPE)
		sh->rl->head = sh->rl->head->next;
	if (sh->root->type == _EXEC)
	{
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
		lp->right = (t_cmd *)pp;
		pp->left = exec_parse(sh, init_exec());
		if (peek_future_tokens_type(sh->rl->head, PIPE))
			return (pipe_parse(sh), NULL);
	}
	return ((t_cmd *)pp);
}

/* t_cmd	*exec_parse(t_shell *sh, t_exec *exec_struct)
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
			|| sh->rl->head->type == ENV)
		{
			exec_struct->args[i++] = get_tkn(i, sh->rl->head->token, sh);
			//exec_struct->args[i++] = ft_strdup(sh->rl->head->token);
			//sh->rl->head = sh->rl->head->next;
		}
		else
			sh->rl->head = sh->rl->head->next;
	}
	exec_struct->args[i] = NULL;
	if (prev == NULL)
		sh->root = (t_cmd *)branch_root;
	return ((t_cmd *)branch_root);
} */