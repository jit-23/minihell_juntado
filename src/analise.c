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
	refine_token_list(shell);
}

void	analise_terminal_input(t_shell *shell, char *cmdline)
{
	t_placing	place;
	t_token		*head;

	shell->cmd_line = ft_strtrim(shell->cmd_line, " ");
	if (cmdline[0] == '\0')
		return ;
	place = DEFAULT;
	parse_tokens(shell, cmdline);
	if (check_syntax(shell))
	{
		printf("syntax error\n");
		return ;
	}
	t_token *a;
	a = shell->rl->official_head;
	while(a)
	{
		printf("token - .%s.\t",a->token);
		printf("placing - .%d.\n",a->placing);
		a = a->next;
	}
	init_ast(shell);
	return ;
}

int	get_equal(t_shell *sh, t_placing place)
{
	char	*equal;

	equal = ft_strdup("=");
	add_to_list(sh->token_list, equal, EQUAL, place);
	return (1);
}


/* ambito cultural el corte ingles */
/* r externas - gaia el corte ingles */