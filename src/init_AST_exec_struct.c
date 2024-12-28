/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_AST_exec_struct.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 01:44:38 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/12/28 07:26:51 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_tkn(int i, t_exec *exec, t_cmd *branch, t_shell *sh)
{
	char	*token;

	token = sh->rl->head->token;
	if (i != 0)
	{
		if (sh->rl->head->type == HEREDOC)
		{
			get_through_token(sh);
			exec->args[i] = execute_heredoc(branch, sh->rl->head->token, sh);
		}
		else
			exec->args[i] = ft_strdup(token);
	}
	if (i == 0)
	{
		if (sh->rl->head->type == HEREDOC)
			return (get_tkn_aux1(i, exec, branch, sh), 0);
		else if (is_builtin(token))
			exec->args[i] = ft_strdup(token);
		else if (is_possible_path(token))
			exec->args[i] = ft_strdup(token);
		else
			get_tkn_aux2(i, exec, token, sh);
	}
	return (get_tkn_aux3(sh), 1);
}

char	*get_right_path(char *token, t_shell *sh, t_exec *ex)
{
	char	**all_possible_path;
	char	*new_tkn;
	char	*cmd;
	int		i;
	int		j;

	i = -1;
	j = 0;
	cmd = ft_strjoin("/", token);
	while (sh->path[j])
		j++;
	all_possible_path = (char **)malloc(sizeof(char *) * (j + 1));
	if (!all_possible_path)
		ft_putstr_fd(2, ":cant handle malloc\n");
	while (sh->path[++i])
		all_possible_path[i] = ft_strjoin(sh->path[i], cmd);
	all_possible_path[i] = NULL;
	free(cmd);
	new_tkn = check_access(all_possible_path, ex);
	if (!new_tkn)
		return (ft_strdup(token));
	return (new_tkn);
}

char	*check_access(char **all_paths, t_exec *ex)
{
	int		i;
	char	*executable;

	i = -1;
	while (all_paths[++i])
	{
		if (access(all_paths[i], X_OK) == 0)
		{
			ex->first_cmd = 1;
			executable = ft_strdup(all_paths[i]);
			delete_all_paths(all_paths, 0);
			return (executable);
		}
	}
	delete_all_paths(all_paths, 0);
	return (NULL);
}
