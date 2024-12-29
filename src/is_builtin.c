/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 23:39:38 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/12/29 14:11:38 by fde-jesu         ###   ########.fr       */
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
	if (!ft_strcmp(cmd, "pwd"))
		return (1);
	else if (!ft_strcmp(cmd, "exit"))
		return (1);
	else if (!ft_strcmp(cmd, "env"))
		return (1);
	else if (!ft_strcmp(cmd, "cd"))
		return (1);
	else if (!ft_strcmp(cmd, "echo"))
		return (1);
	else if (!ft_strcmp(cmd, "export"))
		return (1);
	else if (!ft_strcmp(cmd, "unset"))
		return (1);
	return (0);
}

void	execute_builtin(t_exec *ex, char *cmd, t_shell *sh)
{
	if (!ft_strcmp(cmd, "pwd"))
		ft_pwd(sh);
	if (!ft_strcmp(cmd, "env"))
		ft_env(sh);
	else if (!ft_strcmp(cmd, "export"))
		ft_export(sh, ex);
	else if (!ft_strcmp(cmd, "unset"))
		ft_unset(sh, ex);
	else if (!ft_strcmp(cmd, "echo"))
		ft_echo(sh, ex);
	else if (!ft_strcmp(cmd, "cd"))
		ft_cd(sh, ex);
	else if (!ft_strcmp(cmd, "exit"))
		ft_exit(sh, ex);
}
