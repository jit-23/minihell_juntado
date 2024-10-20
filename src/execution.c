#include "../includes/minishell.h"

//void	construct_runcmd(t_shell *sh);
void	prepare_execution(t_exec *exec,t_shell *sh);
char **get_absolute_paths(char **path, char *cmd);
char *allocate_static_block(char *block);
char *create_path_copy();
void print(char *s);

void print(char *a)
{
	for (int i = 0; a[i]; i++)
		write(2,&a[i],1);
	/*estou a meter 2 no write pk e o fd
	para erro, como so estou a mexer com o output, o erro fd
	esta intacto, dps tenho que lidar com ele tmb  */	
}


/*  */
void run_left_branch(t_shell *sh, t_pipe *branch ,int pipe[2]);
void run_right_branch(t_shell *sh, t_pipe *branch ,int pipe[2]);
void run_pipe(t_shell *sh, t_pipe *pp);
void run_cmd(t_shell *sh, t_exec *ex);
void run_tree(t_shell *sh, t_cmd *root);

/*  */

void run_left_branch(t_shell *sh, t_pipe *branch ,int pipe[2])
{
	dup2(pipe[1], 1);
	close(pipe[0]);
	close(pipe[1]);
	t_exec *a;
	a = (t_exec *)branch->left;
	print("\t\t");
	print(a->args[0]);
	print("\n");
	run_tree(sh, (t_cmd *)branch->left);
}

void run_right_branch(t_shell *sh, t_pipe *branch ,int pipe[2])
{
	dup2(pipe[0], 0);
	close(pipe[0]);
	close(pipe[1]);
	run_tree(sh, (t_cmd *)branch->right);
}

void run_pipe(t_shell *sh, t_pipe *pp)
{
	int fd[2];
	//int status;
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
	waitpid(-1,0,0);
	waitpid(-1,0,0);
}

void run_cmd(t_shell *sh, t_exec *ex)
{
	if (execve(ex->args[0], ex->args, sh->env) == -1)
		perror("LOLOOOOLLOOL\n");
	
}

void run_tree(t_shell *sh, t_cmd *root)
{
	static int a;

	a++;
	printf("iteracao\n");
	if (!root)
		return ;
	if (a == 10)
		exit(1);
	if (root->type == _EXEC)
		run_cmd(sh, (t_exec *)root);
	else if (root->type == _REDIR)
		run_cmd(sh, (t_exec *)root);
	else if (root->type == _PIPE)
	{
	/* 	t_pipe *d;
		t_exec *e;

		d = (t_pipe *)root;
		e = (t_exec *)d->left;
		ft_putendl_fd( e->args[0],2); */
		run_pipe(sh, (t_pipe*)root);
	}
}

void _handle_execution(t_shell *sh)	
{
	int pid;
	int wstatus;
	
	wstatus = 0;
	pid = fork();
	if (pid == 0)
	{
		if (sh->root)
			run_tree(sh, sh->root);
		exit(errno);
	}
	update_signal();
	waitpid(pid, &wstatus, 0);
	wait_child(wstatus, sh);
}
