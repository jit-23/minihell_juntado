/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 19:02:49 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/12/29 14:45:21 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <signal.h>

int		g_sign;

void	handle_signal(void)
{
	struct sigaction	signal;
	struct sigaction	signal_ign;

	ft_memset(&signal, 0, sizeof(signal));
	ft_memset(&signal_ign, 0, sizeof(signal_ign));
	signal_ign.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &signal_ign, NULL);
	signal.sa_handler = signal_handler;
	sigaction(SIGINT, &signal, NULL);
}

void	signal_handler(int sign)
{
	if (sign == SIGINT)
	{
		g_sign = 130;
		write(1, "\n", 2);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	update_signal(void)
{
	struct sigaction	pa;

	ft_memset(&pa, 0, sizeof(pa));
	pa.sa_handler = SIG_IGN;
	sigaction(SIGINT, &pa, NULL);
}

void	signal_child_handler(int sign)
{
	if (sign == SIGINT)
	{
		g_sign = 130;
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_redisplay();
		exit(g_sign);
	}
	if (sign == SIGQUIT)
	{
		g_sign = 128 + SIGQUIT;
		ft_putstr_fd(2, "Quit (core dumped)\n");
		exit(g_sign);
	}
}

void	handle_parent_signal(void)
{
	signal(SIGINT, signal_parent_handler);
	signal(SIGQUIT, SIG_IGN);
}
