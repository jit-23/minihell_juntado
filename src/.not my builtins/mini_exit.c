/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 18:22:23 by eescalei          #+#    #+#             */
/*   Updated: 2024/08/07 19:00:25 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	mini_exit(t_shell *shell)
{
	shell->stop_iteration = true;
}


/* temo que ver se o exit e o arg[0], caso contrario, ignora se */
void	mini_exit_nando(int mode, t_shell *shell, t_exec *exec)
{
	if (ft_memcmp(exec->args[0], "exit\0", 5) == 1)
		return ;
	delete_all(shell);
	if (mode == 1) // exit builtin
		exit(EXIT_SUCCESS);
	else if (mode == 0) /* outro exit, assim o valor da ultima acao fica ai */
		exit(g_status_exit_val);
}