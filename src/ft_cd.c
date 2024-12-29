/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 21:52:23 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/12/29 16:00:51 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute_cd(t_shell *sh, t_exec *ex)
{
	char	old_pwd[1000];

	getcwd(old_pwd, 1000);
	if (chdir(ex->args[1]) == -1)
	{
		ft_putstr_fd(2, "cd : ");
		ft_putstr_fd(2, ex->args[1]);
		ft_putstr_fd(2, ": No such file or directory\n");
		g_sign = 1;
		return ;
	}
	update_pwds(sh, old_pwd);
	g_sign = 0;
}

void	go_home(t_shell *sh)
{
	t_env	*target;
	char	*home;
	char	*old_pwd;

	old_pwd = NULL;
	old_pwd = getcwd(old_pwd, 100);
	target = search_env_var(sh, "HOME");
	home = target->env_value;
	if (chdir(home) != 0)
	{
		ft_putstr_fd(2, "cd : ");
		ft_putstr_fd(2, home);
		ft_putstr_fd(2, ": No such file or directory\n");
		g_sign = 1;
		free(old_pwd);
		return ;
	}
	g_sign = 0;
	update_pwds(sh, old_pwd);
	free(old_pwd);
}

void	ft_cd(t_shell *sh, t_exec *ex)
{
	if (!ex->args[1])
		go_home(sh);
	else if (ex->args[2])
	{
		ft_putstr_fd(2, " too many arguments\n");
		g_sign = 1;
		return ;
	}
	else if (ex->args[1] && !ex->args[2])
		execute_cd(sh, ex);
}
