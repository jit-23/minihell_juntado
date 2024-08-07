/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 19:02:49 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/08/07 19:49:53 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


void signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		g_status_exit_val = SIGINT;
		rl_replace_line("", 1);
		write(1,"\n",1);
		rl_on_new_line();
		rl_redisplay();
	}			
}

void handle_signal(void)
{
	struct sigaction signal;
	struct sigaction signal_ign;

	ft_memset(&signal, 0, sizeof(signal));
	ft_memset(&signal_ign, 0, sizeof(signal_ign));

	signal_ign.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &signal_ign, NULL);
	signal.sa_handler = signal_handler;
	sigaction(SIGINT, &signal, NULL);
}