/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 04:03:22 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/09/20 02:31:43 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* 
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
			write(1,"Quit (core dumped)\n",19);
			// shell->exitcode = 131/
		}
		else if (WTERMSIG(wstatus) == SIGINT)
		{
			write(1,"\n",1);
			// shell->exitcode = 130/
		}
	}
			// shell->exitcode = 131/
	//else
		// shell->exitcode = wstatus /256
}

void handle_execution(t_shell *sh)	
{
	int pid;
	int wstatus;
	
	wstatus = 0;
	pid = fork();
	if (pid == 0)
	{
		if (sh->root)
			execute_line(sh);
		exit(errno);	
	}
	update_signal();
	waitpid(pid, &wstatus, 0);
	wait_child(wstatus, sh);
 */