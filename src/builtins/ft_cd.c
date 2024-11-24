/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 21:52:23 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/11/24 21:53:22 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void execute_cd(t_shell *sh, t_exec *ex)
{
	char *name;
	char *value;
	char *old_pwd;
	
	old_pwd = NULL;
	name = NULL;
	value = NULL;
	old_pwd = getcwd(old_pwd, 100);
	if (chdir(ex->args[1]) == -1)
	{
		ft_putstr_fd(2, "cd : ");
		ft_putstr_fd(2, ex->args[1]);
		ft_putstr_fd(2, ": No such file or directory\n");
		return ;
	}
	update_pwds(sh, old_pwd);
	free(old_pwd);
}

void go_back(t_shell *sh)
{
	char *olddir;
	t_env *target;
	char *dir;

	dir = NULL;
	dir = getcwd(dir, 100);
	target = search_env_var(sh, "OLDPWD");
	olddir = target->env_value;
	chdir(olddir);
	update_pwds(sh, dir);
	free(dir);
}

void go_home(t_shell *sh)
{
	t_env *target;
	char *home;
	char *old_pwd;

	old_pwd = NULL;
	old_pwd = getcwd(old_pwd, 100);
	target = search_env_var(sh, "HOME");
	home = target->env_value;
	if (chdir(home) != 0)
	{
		ft_putstr_fd(2, "cd : ");
		ft_putstr_fd(2, home);
		ft_putstr_fd(2, ": No such file or directory\n");
		return ;
	}
	update_pwds(sh, old_pwd);
	free(old_pwd);
}

void ft_cd(t_shell *sh, t_exec *ex)
{
	if (!ex->args[1])
		go_home(sh);
	else if (ex->args[2])
	{
		ft_putstr_fd(2, "too many arguments\n");
		sh->exitcode = 1;
	}
	else if (ex->args[1] && !ex->args[2])
	{
		if (!ft_strncmp(ex->args[1], "..", 2))
			go_back(sh);
		else
			execute_cd(sh,ex);
	}
	sh->exitcode = 0;
}