/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_first_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 04:17:33 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/10/02 17:49:14 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* mudanca para heredoc */
static int confirm_env_location( char *cmdl, int i, t_shell *shell, t_placing place )
{
	if (shell->heredoc_flag == 1) // is a heredoc flag
	{
	//	printf("1\n");
		return (get_word(cmdl, i, shell, place));
	}
	//printf("2\n");
	return (get_env_var(cmdl, i, shell, place));
}
/* mudanca para heredoc */

void	analise_cmdl(t_shell *shell, t_placing place, int i, char *cmdl)
{
	while (cmdl[i])
	{
		if (cmdl[i] == '\'')
			i += handle_single_quotes_type(39, shell, &place);
		else if (cmdl[i] == '\"')
			i += handle_double_quotes_type(34, shell, &place);
		else if (cmdl[i] && is_space(cmdl[i]))
			i += get_space(cmdl, i, shell, place);
		else if (cmdl[i] && cmdl[i] == '$')
		{
			printf("-------------\n");
			//i += get_env_var(cmdl, i, shell, place);
			//printf("___%d___\n", shell->heredoc_flag);
			//i += confirm_env_location(cmdl, i, shell, place);
			if (shell->heredoc_flag == 1)
			{
				printf("heredoc_flag - 1\n");
			//	sleep(1);
				printf("i = %d\n", i);
				i += get_word(cmdl, i, shell, place);
				printf("post get word _i = %d\n", i);
				
			}				
			else if (shell->heredoc_flag == 0)
			{
				printf("heredoc_flag - 0\n");
				i += get_env_var(cmdl, i, shell, place);
			}
		}
		else if (cmdl[i] && cmdl[i] == '|')
			i += get_pipe(shell, place);
		else if (cmdl[i] && cmdl[i] == '>' || cmdl[i] == '<')
			i += get_redirect_var(cmdl, i, shell, place);
		else if (cmdl[i] && !special_char(cmdl[i]) && !is_space(cmdl[i]))
			i += get_word(cmdl, i, shell, place);
		else if (cmdl[i] && cmdl[i] == '\n')
			i += get_new_line(shell, place);
		//printf(".%s.\n", &cmdl[i]);
		//printf("heredoc_flag = %d\n", shell->heredoc_flag);
	}
}
