/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 21:57:09 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/11/24 21:57:27 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int search_var(t_shell *sh, char *var)
{
	t_env *tmp;

	tmp = sh->ev;

	while(tmp)
	{
		if (ft_strncmp(var, sh->ev->env_name, ft_strlen(sh->ev->env_name)))
			return 1;
	}
	return 0;
}
