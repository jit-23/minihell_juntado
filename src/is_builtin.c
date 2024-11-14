/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 23:39:38 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/11/13 18:45:22 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
void delete_var(t_shell *sh, char *env_var);


/*				pwd				*/

void ft_pwd(t_shell *sh)
{
	char *dir;

	dir = NULL;
	dir = getcwd(dir, 100);
	ft_putstr_fd(1, dir);
	ft_putstr_fd(1, "\n");
	free(dir);
	sh->exitcode = 0;
}
/*			env					*/
void ft_env(t_shell *sh)
{
	t_env *ptr;

	ptr = sh->ev;
	while(sh->ev)
	{
		ft_putstr_fd(1,sh->ev->env_name);
		ft_putstr_fd(1,"=");
		ft_putstr_fd(1,sh->ev->env_value);
		ft_putstr_fd(1,"\n");		
		sh->ev = sh->ev->next;
	}
	sh->ev = ptr;
}

/*			export */

void display_exported_envs(t_shell *sh)
{
	t_env *ptr;

	ptr = sh->ev;
	while(sh->ev)
	{
		ft_putstr_fd(1, "declare -x ");
		ft_putstr_fd(1,sh->ev->env_name);
		ft_putstr_fd(1,"=");
		ft_putstr_fd(1,sh->ev->env_value);
		ft_putstr_fd(1,"\n");		
		sh->ev = sh->ev->next;
	}
	sh->ev = ptr;
	delete_all(sh);
	
}

static void insert_var(t_shell *sh, t_exec *ex)
{
	t_env *new;
	t_env *last;

	new = sh->ev;
	while(new->next)
		new = new->next;
	last = new;
	new->next = malloc(sizeof(t_env));
	new = new->next;
	new->env_name = ft_strdup(ex->args[1]);
	if (!ex->args[3])
		new->env_value = ft_strdup("");
	else
		new->env_value = ft_strdup(ex->args[3]);
	new->next = NULL;
	new->prev = last;
}

static int search_var(t_shell *sh, char *var)
{
	t_env *tmp;

	tmp = sh->ev;

	while(tmp)
	{
		if (ft_strncmp(var, sh->ev->env_name, ft_strlen(sh->ev->env_name)))
			return 1;
	}
	return 0;
}

static void manage_var(t_shell *sh, t_exec *exec)
{
	if (search_var(sh, exec->args[1]))
		delete_var(sh, exec->args[1]);
	insert_var(sh, exec);	
}

void ft_export(t_shell *sh, t_exec *ex)
{
	if (!ex->args[1])
		display_exported_envs(sh);
	if (!ex->args[2] || (ex->args[2] && ft_strncmp(ex->args[2], "=", 1)))
		return ;
	else
		manage_var(sh, ex);

}

/* 				unset			 */
t_env *search_env_var(t_shell *sh, char *env_var)
{
	t_env *search;

	search = sh->ev;
	printf("start\n");
	while(search && strncmp(search->env_name, env_var, ft_strlen(search->env_name)))
		search = search->next;
	printf("done\n");
	if (search)
		printf("search = %s\n", search->env_name);
	if (!search)
	{
		printf("noooo\n");
		return (NULL);
	}
	return (search);
}

void delete_var(t_shell *sh, char *env_var)
{
	t_env *target;
	t_env *prev;
	t_env *next;

	target = search_env_var(sh, env_var);
	if (!target)
		return ;
	prev = target->prev;

	next = target->next;
	prev->next = next;
	next->prev = prev;
	free(target->env_name);
	free(target->env_value);
	free(target);
	t_env *a = sh->ev;
	/* while(a)
	{
		printf("%s = %s\n", a->env_name, a->env_value);
		a=a->next;
	} */
}

void ft_unset(t_shell *sh, t_exec *ex)
{
	if (ex->args[1])
	{
		delete_var(sh, ex->args[1]);
		//delete_all(sh);
	}
	
}

/* 					echo		 */
/* check flag return 0 if there is an invalid -n flag*/
int check_flag(t_shell *sh, t_exec *ex)
{
	char *a;
	int i;

	i = 0;
	a = ex->args[1];
	while(a[i])
	{
		if (i == 0)
		{
			if (a[i] != '-')
				return (0);
		}
		else
		{
			if (a[i] != 'n')
				return (0);
		}
		i++;
	}
	return (1);
}

void print_echo_flags(t_shell *sh, t_exec *ex, int i)
{
	int start;

	start = i;
	while(ex->args[i])
	{
		if (ex->args[i][0] == '$' || ex->args[i][0] == '?') /*  isto pode  estar mal porque e possivel q o  analise.c modifique "$?" na sua conversao a token   */
			ft_putnbr_fd(sh->exitcode, 1);	
		ft_putstr_fd(1,ex->args[i]);
		if (ex->args[i + 1])
			ft_putstr_fd(1," ");
		i++;
	}
	if (start == 1)
		ft_putstr_fd(1,"\n");
}

void ft_echo(t_shell *sh, t_exec *ex)
{
	if (!ex->args[1])
		ft_putstr_fd(1, "\n");
	else
	{
		if (check_flag(sh, ex) == 1)
			print_echo_flags(sh, ex, 2);
		else
			print_echo_flags(sh, ex, 1);
	}
	sh->exitcode = 0;
	return ;
}
/* ft_cd.c */

void ft_cd(t_shell *sh, t_exec *ex)
{
	if (ex->args[2])
	{
		ft_putstr_fd(2, "too many arguments\n");
		sh->exitcode = 1;
	}
	//else if (!ex->args[1] || !ft_strncmp(ex->args[1], "/home/$USER", ft_strlen(ex->args[1])))
	//	go_to_home_dir(sh, ex);
		
		
}

int is_builtin(char *cmd)
{
	if (!strncmp(cmd, "pwd", ft_strlen(cmd)))
		return (1);
	else if (!strncmp(cmd, "exit", ft_strlen(cmd)))
		return (1);
	else if (!strncmp(cmd, "cd", ft_strlen(cmd)))
		return (1);
	else if (!strncmp(cmd, "echo", ft_strlen(cmd)))
		return (1);
	else if (!strncmp(cmd, "export", ft_strlen(cmd)))
		return (1);
	else if (!strncmp(cmd, "unset", ft_strlen(cmd)))
		return (1);
	else if (!strncmp(cmd, "env", ft_strlen(cmd)))
		return (1);
	return (0);
}

void execute_builtin(t_exec *ex, char *cmd,t_shell *sh)
{
	if (!strncmp(cmd, "pwd", ft_strlen(cmd)))
		ft_pwd(sh);
	else if (!strncmp(cmd, "env", ft_strlen(cmd)))
		ft_env(sh);
	else if (!strncmp(cmd, "export", ft_strlen(cmd)))
		ft_export(sh, ex);/* ?como guardar vars no env com export se a cada iteracao do minishell precisamos livrar a mem toda? */
	else if (!strncmp(cmd, "unset", ft_strlen(cmd)))
		ft_unset(sh, ex);
	else if (!strncmp(cmd, "echo", ft_strlen(cmd)))
		ft_echo(sh, ex);
	else if (!strncmp(cmd, "echo", ft_strlen(cmd)))
		ft_cd(sh, ex);
}
