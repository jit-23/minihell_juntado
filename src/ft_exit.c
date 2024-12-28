/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 21:58:20 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/12/28 00:47:55 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	has_letter(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '+' || str[0] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

static void	handle_exit(t_shell *sh, t_exec *ex)
{
	if (!ex->args[2])
	{
		ft_putstr_fd(2, "exit: ");
		ft_putstr_fd(2, ex->args[1]);
		ft_putstr_fd(2, ": numeric argument required\n");
		g_sign = 1;
		delete_all(sh);
		exit(1);
	}
	if (has_letter(ex->args[2]))
	{
		ft_putstr_fd(2, "exit: ");
		ft_putstr_fd(2, ex->args[2]);
		ft_putstr_fd(2, ": numeric argument required\n");
		g_sign = 2;
		delete_all(sh);
		exit(2);
	}
	delete_all(sh);
	g_sign = ft_atoi(ex->args[2]);
	exit(g_sign);
}

void	exit_clean(t_shell *sh, int _exit)
{
	delete_all(sh);
	if (sh->ev)
		delete_env_lst(sh->ev, ft_listsize(sh->ev));
	exit(_exit);
}

void	ft_exit(t_shell *sh, t_exec *ex)
{
	if (!ex->args[1])
		exit_clean(sh, 0);
	if ((ex->args[1][0] == '+' || ex->args[1][0] == '-')
		&& ex->args[1][1] == '\0')
		handle_exit(sh, ex);
	if (ex->args[2])
	{
		ft_putstr_fd(2, " too many arguments\n");
		g_sign = 1;
		exit_clean(sh, 1);
	}
	if (has_letter(ex->args[1]))
	{
		ft_putstr_fd(2, "exit: ");
		ft_putstr_fd(2, ex->args[1]);
		ft_putstr_fd(2, ": numeric argument required\n");
		g_sign = 2;
		exit_clean(sh, 2);
	}
	g_sign = ft_atoi(ex->args[1]);
	exit_clean(sh, g_sign);
}
