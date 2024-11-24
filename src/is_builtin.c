/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 23:39:38 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/11/24 21:58:17 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
void delete_var(t_shell *sh, char *env_var);
t_env *search_env_var(t_shell *sh, char *env_var);

/*				pwd				*/

/* void ft_pwd(t_shell *sh)
{
	char *dir;

	dir = NULL;
	dir = getcwd(dir, 100);
	ft_putstr_fd(1, dir);
	ft_putstr_fd(1, "\n");
	free(dir);
	sh->exitcode = 0;
} */
/*			env					*/
/* void ft_env(t_shell *sh)
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
} */

/*			export */

/* static t_env *alpha_order(t_shell *sh)
{
	t_env *a;
	t_env *b;
	t_env *lowest;
	char *name = sh->ev->env_name;
	//printf("name - .%s.\n", name);
	a = sh->ev;
	b = sh->ev;
	while (a)
	{
		if (a->prev == NULL)
			
		if (a->displayed == false)
		{
			if ((ft_strncmp(a->env_name, name, ft_strlen(name)) < 0 )) // a = 'a' || b = 'A';
				name = a->env_name;
		}
		a = a->next;
	}
	//printf("first one  - > .%s.\n", name);
	lowest = search_env_var(sh, name); 
	lowest->displayed = true;
	return (lowest);
} */

int ft_listsize(t_env *ev)
{
	t_env	*temp;
	int		count;

	count = 0;
	temp = ev;
	if (!ev)
		return (0);
	while (temp != NULL)
	{
		temp = temp->next;
		count++;
	}
	return (count);
}
/* 
int aux(t_env **ptr, t_env **b, int option)
{
	if (option == 1)
	{
		while ((*ptr)->displayed == 1)
		{
			(*ptr) = (*ptr)->next;
			if (!(*b)->next)
				return (1);
			(*b) = (*b)->next;
		}
	}
	else
	{
		while ((*b)->displayed == 1)
		{
			if ((*b)->next)
				(*b) = (*b)->next;
			else
				return (1);
		}
	}
	return (0);
} */
/* void display_it(t_env *display)
{
	if (display->env_name[0] == '_')
		return ;
	ft_putstr_fd(1, "declare -x ");
	ft_putstr_fd(1, display->env_name);
	ft_putstr_fd(1, "=");
	ft_putstr_fd(1, display->env_value);
	ft_putstr_fd(1, "\n");
}

void display_sorted_exported_envs(t_shell *sh)
{
	static int  index = 1;
	t_env *a = sh->ev;
	t_env *b = sh->ev->next;
	t_env *ptr;
	ptr = a;
	while(b)
	{
		if (aux(&ptr, &b, 1) == 1)
			break;
		if (aux(&ptr, &b, 2) == 1)
			break;
		if (strncmp(ptr->env_name, b->env_name, ft_strlen(ptr->env_name)) > 0)
		{
			if (ptr->displayed == 0)
				ptr = b;
			b = b->next;
		}
		else
			b = b->next;
	}
	display_it(ptr);
	ptr->displayed = 1;
	ptr->index = index++;
} */

/* static void organized_export(t_shell *sh)
{
	int		flag;
	int		i;
	t_env	*a;

	a = sh->ev;
	i = -1;
	while(++i < ft_listsize(a))
		display_sorted_exported_envs(sh);
}
 */

/* static void insert_var(t_shell *sh, char *a, char *c)
{
	t_env *new;
	t_env *last;

	new = sh->ev;
	while(new->next)
		new = new->next;
	last = new;
	new->next = malloc(sizeof(t_env));
	new = new->next;
	new->env_name = ft_strdup(a);
	if (c)
		new->env_value = ft_strdup("");
	else
		new->env_value = ft_strdup(c);
	new->next = NULL;
	new->prev = last;
} */

/* int search_var(t_shell *sh, char *var)
{
	t_env *tmp;

	tmp = sh->ev;

	while(tmp)
	{
		if (ft_strncmp(var, sh->ev->env_name, ft_strlen(sh->ev->env_name)))
			return 1;
	}
	return 0;
} */

/* static void manage_var(t_shell *sh, t_exec *exec)
{
	if (search_var(sh, exec->args[1]))
		delete_var(sh, exec->args[1]);
	insert_var(sh, exec->args[1], exec->args[3]);
} */



/* void ft_export(t_shell *sh, t_exec *ex)
{
	if (!ex->args[1]) // export sozinho.
	{
		printf("0\n");	
		organized_export(sh);
	}
	else if (ex->args[1])
	{
		if (!ex->args[2]) // export "name"
		{
			printf("1\n");
			manage_var(sh,ex);
		}
		else if (ex->args[2][0] != '=')
		{
			printf("2\n");
			perror("adsasdasddas\n");
		}
		else if(ex->args[2][0] == '=' && !ex->args[3]) // export "name" "="  
		{
			printf("3\n");
			manage_var(sh, ex);
		}
		else if (ex->args[2][0] == '=' && ex->args[3] && !ex->args[4])
		{
			printf("4\n");
			manage_var(sh, ex);
		}
		else
			perror("invalid number of args\n");
	}
	else
	{
			printf("5\n");
		manage_var(sh, ex);
	}

} */

/* 				unset			 */
/* t_env *search_env_var(t_shell *sh, char *env_var)
{
	t_env *search;

	search = sh->ev;
	while(search && strncmp(search->env_name, env_var, ft_strlen(search->env_name)))
		search = search->next;
	if (!search)
		return (NULL);
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
	t_env *a = sh->ev; */
	/* while(a)
	{
		printf("%s = %s\n", a->env_name, a->env_value);
		a=a->next;
	} */
//}

/* void ft_unset(t_shell *sh, t_exec *ex)
{
	if (ex->args[1])
		delete_var(sh, ex->args[1]);
	sh->exitcode = 0;
} */

/* 					echo		 */
/* check flag return 0 if there is an invalid -n flag*/
/* int check_flag(t_shell *sh, t_exec *ex)
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
} */

/* void print_echo_flags(t_shell *sh, t_exec *ex, int i)
{
	int start;

	start = i;
	while(ex->args[i])
	{
		if (ex->args[i][0] == '$' || ex->args[i][0] == '?') isto pode  estar mal porque e possivel q o  analise.c modifique "$?" na sua conversao a token 
			ft_putnbr_fd(sh->exitcode, 1);	
		ft_putstr_fd(1,ex->args[i]);
		if (ex->args[i + 1])
			ft_putstr_fd(1," ");
		i++;
	}
	if (start == 1)
		ft_putstr_fd(1,"\n");
} */

/* void ft_echo(t_shell *sh, t_exec *ex)
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
} */
/* ft_cd.c */
//cd: fff: No such file or directory

static void update_pwds(t_shell *sh, char *old_pwd)
{
	t_env *pwds;
	char *dir;

	dir = NULL;
	dir = getcwd(dir, 100);
	pwds = search_env_var(sh, "OLDPWD");
	free(pwds->env_value);
	pwds->env_value = ft_strdup(old_pwd/*  */);
	pwds = search_env_var(sh, "PWD");
	free(pwds->env_value);
	pwds->env_value = ft_strdup(dir);
	free(dir);

}

/* void execute_cd(t_shell *sh, t_exec *ex)
{
	char *name;
	char *value;
	char *old_pwd;
	
	old_pwd = NULL;
	name = NULL;
	value = NULL;
	old_pwd = getcwd(old_pwd, 100);
	if (chdir(ex->args[1]) == -1)
	{
		ft_putstr_fd(2, "cd : ");
		ft_putstr_fd(2, ex->args[1]);
		ft_putstr_fd(2, ": No such file or directory\n");
		return ;
	}
	update_pwds(sh, old_pwd);
	free(old_pwd);
} */
static void go_home(t_shell *sh)
{
	t_env *target;
	char *home;
	char *old_pwd;

	old_pwd = NULL;
	old_pwd = getcwd(old_pwd, 100);
	target = search_env_var(sh, "HOME");
	home = target->env_value;
	if (chdir(home) != 0)
	{
		ft_putstr_fd(2, "cd : ");
		ft_putstr_fd(2, home);
		ft_putstr_fd(2, ": No such file or directory\n");
		return ;
	}
	update_pwds(sh, old_pwd);
	free(old_pwd);
}

/* static void go_back(t_shell *sh)
{
	char *olddir;
	t_env *target;
	char *dir;

	dir = NULL;
	dir = getcwd(dir, 100);
	target = search_env_var(sh, "OLDPWD");
	olddir = target->env_value;
	chdir(olddir);
	update_pwds(sh, dir);
	free(dir);
} */

void ft_cd(t_shell *sh, t_exec *ex)
{
	if (!ex->args[1])
		go_home(sh);
	else if (ex->args[2])
	{
		ft_putstr_fd(2, "too many arguments\n");
		sh->exitcode = 1;
	}
	else if (ex->args[1] && !ex->args[2])
	{
		if (!ft_strncmp(ex->args[1], "..", 2))
			go_back(sh);
		else
			execute_cd(sh,ex);
	}
	sh->exitcode = 0;
}

/* static void ft_exit(t_shell *sh, t_exec *ex)
{
	int	i;

	i = 0;
	if (!ex->args[1])
		exit(0);
	else if (ex->args[3])
			perror("handle msg error (exit)\n");
	if (ex->args[1][0] == '+')
	{
		if (!ex->args[2])
			perror("handle msg error (exit)\n");
		if (ex->args[2])
		{
			if(!ft_isdigit(ex->args[2][0]))
				perror("handle msg error (exit)\n");
			else
				sh->exitcode = ft_atoi(ex->args[2]);
		}
	}
} */
	
	//while(ex->args[1][i])
	//{/* como eu lido com + como um token so, verifica separadamente se existe aqui ou nao. vai ser chato, mas olha
	//prefiro lidar com isso aqui do que no parser, este e o unico caso em que preciso lidar com isto */
	//	if (ft_isdigit(ex->args[1][i]) && (ex->args[1][i] != '-' && ex->args[1][i] != '+'))
	//}

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
	else if (!strncmp(cmd, "cd", ft_strlen(cmd)))
		ft_cd(sh, ex);
	else if(!strncmp(cmd, "exit", ft_strlen(cmd)))
		ft_exit(sh, ex);
}
