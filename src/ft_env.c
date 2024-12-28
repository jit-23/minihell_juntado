/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 21:42:16 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/12/28 00:47:55 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_env(t_shell *sh)
{
	t_env	*ptr;

	ptr = sh->ev;
	while (sh->ev)
	{
		ft_putstr_fd(1, sh->ev->env_name);
		ft_putstr_fd(1, "=");
		ft_putstr_fd(1, sh->ev->env_value);
		ft_putstr_fd(1, "\n");
		sh->ev = sh->ev->next;
	}
	sh->ev = ptr;
	g_sign = 0;
}
