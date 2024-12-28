/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 23:42:14 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/12/28 08:04:59 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	create_execute_tree(t_shell *sh, char *cmdl_line)
{
	analise_terminal_input(sh, cmdl_line);
	_handle_execution(sh);
	delete_all(sh);
}

void	default_values(t_shell *sh, char **ev)
{
	handle_signal();
	init_shell(sh, ev);
	get_prompt(sh);
}

void	end_loop(t_shell *sh)
{
	delete_all(sh);
	if (sh->ev)
		delete_env_lst(sh->ev, lst_size_env(sh->ev));
	ft_putstr_fd(1, "exit\n");
	exit (0);
}

void	delete_path(char **path, int i)
{
	while (path[i])
		free(path[i++]);
	free(path);
}

void	core_values(t_shell *sh, char **ev)
{
	g_sign = 0;
	if (!(*ev))
		sh->ev = NULL;
	else
		sh->ev = expand_env(ev);
}
