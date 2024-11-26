#include "../includes/minishell.h"

//void	construct_runcmd(t_shell *sh);
void	prepare_execution(t_exec *exec,t_shell *sh);
char **get_absolute_paths(char **path, char *cmd);
char *allocate_static_block(char *block);
char *create_path_copy();
void print(char *s);

void	set_signals(void);
void	sigint_handler(int signo);


void print(char *a)
{
	for (int i = 0; a[i]; i++)
		write(2,&a[i],1);
	/*estou a meter 2 no write pk e o fd
	para erro, como so estou a mexer com o output, o erro fd
	esta intacto, dps tenho que lidar com ele tmb  */	
}



void	set_signals()
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}
void	sigint_handler(int signo)
{
	if (signo == SIGINT)
	{
		//g_signo = 130;
		write(2, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}


/*  */
void run_left_branch(t_shell *sh, t_pipe *branch ,int pipe[2]);
void run_right_branch(t_shell *sh, t_pipe *branch ,int pipe[2]);
void run_pipe(t_shell *sh, t_pipe *pp);
void run_cmd(t_shell *sh, t_exec *ex);
void run_tree(t_shell *sh, t_cmd *root);

/*  */
int	lstsize(t_env *lst);
/*  */

void run_left_branch(t_shell *sh, t_pipe *branch ,int pipe[2])
{
	dup2(pipe[1], 1);
	close(pipe[0]);
	close(pipe[1]);
	run_tree(sh, (t_cmd *)branch->left);
}

void run_right_branch(t_shell *sh, t_pipe *branch ,int pipe[2])
{
	dup2(pipe[0], 0);
	close(pipe[0]);
	close(pipe[1]);
	run_tree(sh, (t_cmd *)branch->right);
}

void get_exit_code(int status, t_shell *sh)
{
	if(WIFEXITED(status) != 0)
		sh->exitcode = WEXITSTATUS(status);
	//delete_all(sh);
}

void run_pipe(t_shell *sh, t_pipe *pp)
{
	int fd[2];
	int status;
	pid_t left;
	pid_t right;

	pipe(fd);
	left = fork();
	if (left == 0)
		run_left_branch(sh, (t_pipe *)pp, fd);
	right = fork();
	if (right == 0)
		run_right_branch(sh, (t_pipe *)pp, fd);
	close(fd[0]);
	close(fd[1]);
	waitpid(left, &status, 0);
	waitpid(right, &status, 0);
	get_exit_code(status, sh);
	exit(1);
}

static void	sigint_child_handler(int signo)
{
	if (signo == SIGINT)
	{
		write(2, "_", 1);
		write(2, "\n", 1);
		rl_replace_line("", 0);
		rl_redisplay();
		exit(1);
	}
	else if (signo == SIGQUIT)
	{
		write(2, "Quit (core dumped)\n", 19);
		exit(1);
	}
}

static void	set_child_signals(void)
{
	signal(SIGINT, sigint_child_handler);
	signal(SIGQUIT, sigint_child_handler);
}

void run_cmd(t_shell *sh, t_exec *ex)
{
	pid_t pid1;
	int status;

	if (ex->args[0] == NULL)
		return ;
	perror("run_cmd\n");
	if (is_builtin(ex->args[0]))
	{
		execute_builtin(ex, ex->args[0], sh);
		return ;
	}
	pid1 = fork();
	if (pid1 == 0)
	{
		perror("inside \n");
		if (execve(ex->args[0], ex->args, sh->env) == -1)
		{
			ft_putstr_fd(2, ex->args[0]);
			ft_putstr_fd(2, ": command not found\n");
			delete_all(sh);
			exit(127);
		}
	}
	else
	{
		waitpid(pid1, &status, 0);
		if (WIFEXITED(status))
			sh->exitcode = WEXITSTATUS(status);
	}
}

int get_file(t_shell *sh, t_redir *redir)
{
	int fd;
	
	
	if (redir->mode == 0) // < redirection of input
	{
		fd = open(redir->file, O_RDONLY, 0664);
		if (fd < 0)
			ft_putstr_fd(2, "bash: FILE: Permission denied");
		dup2(fd, STDIN_FILENO);
		return (fd);
	}
	else if (redir->mode == 1) //> redirection of output 
	{
		//close(STDOUT_FILENO);
		fd = open(redir->file, O_CREAT | O_WRONLY | O_TRUNC, 0664);
		if (fd < 0)
			ft_putstr_fd(2, "bash: FILE: Permission denied"); // troca isto
		dup2(fd, STDOUT_FILENO);
		return (fd);
	}
	else  if (redir->mode == 2) // >>
	{
		printf("redir->file - %s\n", redir->file);
		fd = open(redir->file,  O_CREAT | O_APPEND | O_WRONLY, 0664);
		if (fd < 0)
			ft_putstr_fd(2, "bash: FILE: Permission denied");
		dup2(fd, STDOUT_FILENO);
		return (fd);
	}
	else if (redir->mode == 3) // <<
	{
		fd = open(redir->file, O_RDWR, 0664);
		if (fd < 0)
			ft_putstr_fd(2, "bash: FILE: Permission denied");
		dup2(fd, STDIN_FILENO);
		return (fd);
	}
	return (-42);
}

void run_redir(t_shell *sh, t_redir *redir)
{
	int file;
	t_exec *e;

	printf("run_redir\n");
	e = NULL;
	file = get_file(sh, redir);
	perror("run_redir1\n");
	if (file < 0)
		perror("redir error\n");
	if (redir->cmd)
	{
	perror("run_redir3\n");
		e = (t_exec *)redir->cmd;
		if (!e->args[0])
			run_tree(sh, NULL);
		run_tree(sh, (t_cmd *)redir->cmd);
	}
}

void run_tree(t_shell *sh, t_cmd *root)
{
	int	pid;
	if (!root)
		return ;
	if (root->type == _EXEC)
		run_cmd(sh, (t_exec *)root);
	else if (root->type == _REDIR)
		run_redir(sh, (t_redir *)root);
	else if (root->type == _PIPE)
	{
		pid = fork();
		if (pid == 0)
			run_pipe(sh, (t_pipe*)root);
		else
			waitpid(-1, NULL, 0);
	}
	ft_putstr_fd(2,"assadassafdfdsdsferrrrwrewrerew\n");
}

int	lstsize(t_env *lst)
{
	t_env	*temp;
	int		count;

	count = 0;
	temp = lst;
	if (!lst)
		return (0);
	while (temp != NULL)
	{
		temp = temp->next;
		count++;
	}
	return (count);
}

void _handle_execution(t_shell *sh)	
{
	int pid;
	int wstatus;
	
	wstatus = 0;
	/* pid = fork();

	if (pid == 0)
	{
		if (sh->root)
			run_tree(sh, sh->root);
		delete_all(sh);	
		exit(errno);
		exit(1);
	} */
	if (sh->root)
		run_tree(sh, sh->root);

	//update_signal();
	//waitpid(pid, &wstatus, 0);
	//wait_child(wstatus, sh);

	delete_hiden_files(sh);
	ft_putstr_fd(2, "here?\n");
	return ;
//	printf("size of ll - %d\n", lstsize(sh->ev));
}
