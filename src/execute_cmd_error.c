/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd_error.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 07:35:35 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/12/29 15:38:24 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	run_cmd_exit_msg(t_shell *sh, char *cmd)
{
	ft_putstr_fd(2, cmd);
	ft_putstr_fd(2, ": command not found\n");
	delete_all(sh);
	if (sh->ev)
		delete_env_lst(sh->ev, lst_size_env(sh->ev));
	g_sign = 127;
	exit(g_sign);
}
