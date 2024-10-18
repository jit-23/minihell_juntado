/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analise.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 20:01:30 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/07/30 04:37:04 by fde-jesu         ###   ########.fr       */
/*									                                          */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_tree(t_cmd *root)
{
	static int	j;
	int			i;
	t_exec		*ex;
	t_redir		*redir;
	t_pipe		*pp;

	i = -1;
	if (root == NULL)
		return ;
	//printf("type of root - %d\n", root->type);
	if (root->type == _EXEC)
	{
		ex = (t_exec *)root;
		while (ex->args[++i])		
			printf("%d - args - %s\n", j, ex->args[i]);	
		j++;
		printf("\n");
	}
	else if (root->type == _REDIR)
	{
		redir = (t_redir *)root;
		print_tree((t_cmd *)redir->cmd);
		printf("redir mode(%d)\nfile %s\n", redir->mode, redir->file);
	}
	else if (root->type == _PIPE)
	{
		pp = (t_pipe *)root;
		printf("%d pipe - | \n", j);
		j++;
		print_tree((t_cmd *)pp->left);
		print_tree((t_cmd *)pp->right);
	}
}

void	parse_tokens(t_shell *shell, char *cmdl)
{
	t_placing	place;

	place = DEFAULT;
	shell->heredoc_flag = 0;
	analise_cmdl(shell, place, 0, shell->cmd_line);
	//printf("OUT OF ANALISE\n");
	//sleep(1);
	refine_token_list(shell);
}

void	analise_terminal_input(t_shell *shell, char *cmdline)
{
	t_placing	place;
	t_token		*head;

	shell->cmd_line = ft_strtrim(shell->cmd_line, " \t");
	if (!cmdline)
		return ;
	place = DEFAULT;
	parse_tokens(shell, cmdline);
	if (check_syntax(shell))
	{
		printf("syntax error\n");
		return ;
	}
	head = shell->rl->official_head;
	//while (head)
	//{
	//	printf("===================\n");
	//	printf("address = .%p.\n", head);
	//	printf("token   = .%s.\n", head->token);
	//	printf("Placing = .%u.\n", head->placing);
	//	printf("Type    = .%d.\n", head->type);
	////	printf("hrdcF   = .%d.\n", );
	//	head = head->next;
	//} 
	init_ast(shell);
	printf("\n\n\n\n\n");
	//print_tree(shell->root);

	//	t_redir *w;
	//	w = (t_redir *)shell->root;
	
	//t_pipe *pp;
	//t_pipe *pp2;
	//t_exec *ex;
//
	//pp = (t_pipe *)shell->root;
	//pp2 = (t_pipe *)pp->right;
	//ex = (t_exec *)pp->left;
	//if (ex)
	//	printf("exist\n");
	//printf("first cmd = %s\n", ex->args[0]);
	//if (pp2)
	//	printf("pp2 exist\n");
	//ex = (t_exec *)pp2->left;
	//printf("second cmd = %s\n", ex->args[0]);
	//ex = (t_exec *)pp2->right;
	//printf("third cmd = %s\n", ex->args[0]);

	print_tree(shell->root);
	return ;
}

int	get_new_line(t_shell *sh, t_placing place)
{
	char	*newl;

	newl = ft_strdup("\n");
	add_to_list(sh->token_list, newl, NEW_LINE, place);
	return (1);
}


/* ambito cultural el corte ingles */
/* r externas - gaia el corte ingles */