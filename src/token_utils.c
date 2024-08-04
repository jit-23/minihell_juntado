/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 23:00:04 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/08/04 00:25:24 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* put all the fill_list functions on a file named "fill_list_utils.c" */
/*								|
								V 										*/

void	organize_reddir_type(t_shell *sh, char *token, t_placing placing)
{
	if (!ft_strncmp(token, ">>", ft_strlen(">>")))
		add_to_list(sh->token_list, token, _APPEND, placing);
	else if (!ft_strncmp(token, "<<", ft_strlen("<<")))
		add_to_list(sh->token_list, token, HEREDOC, placing);
	else if (!ft_strncmp(token, "<", ft_strlen("<")))
		add_to_list(sh->token_list, token, REDIR_IN, placing);
	else if (!ft_strncmp(token, ">", ft_strlen(">")))
		add_to_list(sh->token_list, token, REDIR_OUT, placing);
	else
		perror("ERROR ON '<' OR '>' parsing");
}

/* to maintain the same character if there is
	more than one. otherwise we stop and go to the next. */
int	get_redirect_var(char *cmdl, int i, t_shell *sh, t_placing placing)
{
	int		j;
	int		k;
	char	var;
	char	*token;

	j = 0;
	k = i;
	var = cmdl[i];
	while (cmdl[k++] == var)
		j++;
	k = 0;
	token = (char *)ft_calloc(j + 1, (sizeof(char) * j + 1));
	while (k < j)
		token[k++] = cmdl[i++];
	token[k] = '\0';
	organize_reddir_type(sh, token, placing);
	return (ft_strlen(token));
}
