/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_AST_exec_struct_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 07:24:54 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/12/29 15:16:48 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_possible_path(char *token)
{
	if (ft_strnstr(token, "/bin", ft_strlen("/bin")) || ft_strnstr(token,
			"/usr/bin", ft_strlen("/usr/bin")) || ft_strnstr(token, "/sbin",
			ft_strlen("/sbin")) || ft_strnstr(token, "/usr/sbin",
			ft_strlen("/usr/sbin")))
		return (1);
	return (0);
}

void	get_tkn_aux2(int i, t_exec *exec, char *token, t_shell *sh)
{
	if (sh->path)
		exec->args[i] = get_right_path(token, sh, exec);
	else
		exec->args[i] = ft_strdup(token);
}

void	get_tkn_aux1(t_cmd *branch, t_shell *sh)
{
	if (sh->rl->head->next)
		sh->rl->head = sh->rl->head->next;
	while (sh->rl->head && sh->rl->head->type == SPACE_BAR)
		sh->rl->head = sh->rl->head->next;
	free(execute_heredoc(branch, sh->rl->head->token, sh));
	sh->rl->head = sh->rl->head->next;
}

void	get_tkn_aux3(t_shell *sh)
{
	sh->rl->head = sh->rl->head->next;
}

void	get_through_token(t_shell *sh)
{
	if (sh->rl->head->next)
		sh->rl->head = sh->rl->head->next;
	while (sh->rl->head && sh->rl->head->type == SPACE_BAR)
		sh->rl->head = sh->rl->head->next;
}
