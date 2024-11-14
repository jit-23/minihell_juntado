/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 19:02:49 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/11/07 02:26:26 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <signal.h>
int g_status_exit_val;

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

void update_signal()
{
	struct sigaction pa;

	ft_memset(&pa, 0, sizeof(pa));
	pa.sa_handler = SIG_IGN;
	sigaction(SIGINT, &pa, NULL);
}

void wait_child(int wstatus, t_shell  *shell)
{
	if (WIFSIGNALED(wstatus))
	{
		if (WCOREDUMP(wstatus))
		{
			write(1,"_Quit (core dumped)\n",20);
			delete_all(shell);
			shell->exitcode = 127;
		}
		else if (WTERMSIG(wstatus) == SIGINT)
		{
			write(1,"\n",1);
			delete_all(shell);
			shell->exitcode = 130;
		}
	}
			// shell->exitcode = 131/
	//else
		// shell->exitcode = wstatus /256
}
