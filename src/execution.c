#include "../includes/minishell.h"

//void	construct_runcmd(t_shell *sh);
void	prepare_execution(t_exec *exec,t_shell *sh);
char **get_absolute_paths(char **path, char *cmd);
char *allocate_static_block(char *block);
char *create_path_copy();


char *allocate_static_block(char *block)
{
	int block_l;
	char *allocated_block;
	
	block_l = ft_strlen(block);
	allocated_block = (char *)malloc(sizeof(char) * block_l);
	ft_strlcpy(allocated_block, block, ft_strlen(block));
	return (allocated_block);
}

char **get_absolute_paths(char **paths, char *cmd)
{
	int i;
	char *path_coppy;
	cmd = ft_strjoin("/", cmd);

}


void prepare_execution(t_exec *exec, t_shell *sh)
{
	char *cmd;
	char **cmd_paths;

	cmd = allocate_static_block(exec->args[0]); // tenho dps que dar free a este cmd.
	cmd_paths = get_absolute_paths(sh->path, cmd);
	
}

//void	construct_runcmd(t_shell *sh)
//{
//	sh->
//}

void runcmd(t_shell *sh, t_cmd *root)
{

	if (root->type == _EXEC)
		prepare_execution((t_exec*)root, sh);
	else if  (root->type == _REDIR)
		printf(".\n");//execute(); // redireciona as portas, depois execute
	else if (root->type == _PIPE)
		runpipe(sh, (t_pipe*)sh->root);
}

void runpipe(t_shell *sh,t_pipe *root)
{
	int fd[2];

	pid_t first_child; // left;
	pid_t second_child; // right;

	first_child = fork();
		if (first_child == 0)
			runcmd(sh, sh->root);
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
		{
			//construct_runcmd(sh);
			runcmd(sh, sh->root);//execute_line(sh);
		}
		exit(errno);	
	}
	update_signal();
	waitpid(pid, &wstatus, 0);
	wait_child(wstatus, sh);
}
