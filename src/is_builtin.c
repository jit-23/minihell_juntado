/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 23:39:38 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/12/14 00:59:35 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_listsize(t_env *ev)
{
	t_env	*temp;
	int		count;

	count = 0;
	temp = ev;
	if (!ev)
		return (0);
	while (temp != NULL)
	{
		temp = temp->next;
		count++;
	}
	return (count);
}

int	is_builtin(char *cmd)
{
	if (!ft_strncmp(cmd, "pwd", ft_strlen("pwd")))
		return (1);
	else if (!ft_strncmp(cmd, "exit", ft_strlen("exit")))
		return (1);
	else if (!ft_strncmp(cmd, "env", ft_strlen("env")))
		return (1);
	else if (!ft_strncmp(cmd, "cd", ft_strlen("cd")))
		return (1);
	else if (!ft_strncmp(cmd, "echo", ft_strlen("echo")))
		return (1);
	else if (!ft_strncmp(cmd, "export", ft_strlen("export")))
		return (1);
	else if (!ft_strncmp(cmd, "unset", ft_strlen("unset")))
		return (1);
	return (0);
}

void	execute_builtin(t_exec *ex, char *cmd, t_shell *sh)
{
	if (!ft_strncmp(cmd, "pwd", ft_strlen("pwd")))
		ft_pwd(sh);
	if (!ft_strncmp(cmd, "env", ft_strlen("env")))
		ft_env(sh);
	else if (!ft_strncmp(cmd, "export", ft_strlen("export")))
		ft_export(sh, ex);
	else if (!ft_strncmp(cmd, "unset", ft_strlen("unset")))
		ft_unset(sh, ex);
	else if (!ft_strncmp(cmd, "echo", ft_strlen("echo")))
		ft_echo(sh, ex);
	else if (!ft_strncmp(cmd, "cd", ft_strlen("cd")))
		ft_cd(sh, ex);
	else if (!ft_strncmp(cmd, "exit", ft_strlen("exit")))
		ft_exit(sh, ex);
}
