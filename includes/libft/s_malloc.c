/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_malloc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 22:46:13 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/08/03 05:28:36 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*s_malloc(size_t bt)
{
	void	*a;

	a = malloc(sizeof(bt));
	if (!a)
	{
		ft_putstr_fd(2, "error with malloc\n");
		exit(1);
	}
	return (a);
}
