/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 21:58:20 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/11/25 01:09:40 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void ft_exit(t_shell *sh, t_exec *ex)
{
	int	i;

	i = 0;
	if (!ex->args[1])
		exit(0);
	else if (ex->args[3])
			perror("handle msg error (exit)\n");
	if (ex->args[1][0] == '+')
	{
		if (!ex->args[2])
			perror("handle msg error (exit)\n");
		if (ex->args[2])
		{
			if(!ft_isdigit(ex->args[2][0]))
				perror("handle msg error (exit)\n");
			else
				sh->exitcode = ft_atoi(ex->args[2]);
		}
	}
}