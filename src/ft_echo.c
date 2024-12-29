/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 21:48:47 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/12/29 14:46:48 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_echo(t_shell *sh, t_exec *ex)
{
	if (!ex->args[1])
	{
		ft_putstr_fd(1, "\n");
		g_sign = 0;
		return ;
	}
	else
	{
		if (check_flag(ex) == 1)
			print_echo_flags(sh, ex, 2);
		else
			print_echo_flags(sh, ex, 1);
	}
	g_sign = 0;
	return ;
}

void	print_echo_flags(t_shell *sh, t_exec *ex, int i)
{
	int	start;

	(void)sh;
	start = i;
	while (ex->args[i])
	{
		if (ex->args[i][0] == '$' && ex->args[i][1] == '?' \
			&& ex->args[i][0] == '\0')
			ft_putnbr_fd(g_sign, 1);
		ft_putstr_fd(1, ex->args[i]);
		if (ex->args[i + 1])
			ft_putstr_fd(1, " ");
		i++;
	}
	if (start == 1)
		ft_putstr_fd(1, "\n");
}

int	check_flag(t_exec *ex)
{
	char	*a;
	int		i;

	i = 0;
	a = ex->args[1];
	while (a[i])
	{
		if (i == 0)
		{
			if (a[i] != '-')
				return (0);
		}
		else
		{
			if (a[i] != 'n')
				return (0);
		}
		i++;
	}
	return (1);
}
