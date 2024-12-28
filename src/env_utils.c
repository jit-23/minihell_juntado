/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 20:46:31 by eescalei          #+#    #+#             */
/*   Updated: 2024/12/07 04:04:24 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(char **env, char *name, int len)
{
	int		i;
	int		j;
	int		s_alloc;
	char	*value;

	i = -1;
	j = len + 1;
	while (env[++i])
	{
		if (ft_strncmp(env[i], name, len) == 0)
		{
			s_alloc = ft_strlen(env[i]) - len;
			value = (char *)malloc(sizeof(char) * s_alloc);
			if (!value)
				return (NULL);
			while (env[i][j++])
				value[j - len] = env[i][j];
			return (value);
		}
	}
	return (NULL);
}
