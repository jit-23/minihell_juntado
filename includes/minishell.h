/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 05:59:56 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/08/04 06:57:35 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/history.h>
# include <readline/readline.h>
# include "libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <sys/wait.h>
# include <unistd.h>
# include <curses.h>
# include <term.h>
# include <stdarg.h>
# include <errno.h>
# include <limits.h>
# include <linux/limits.h>
# include <signal.h>

# define SKIP_SPACES 1
# define JUMP_TOKEN 2
# define ANSI_COLOR_RED     "\x1b[31m"
# define ANSI_COLOR_GREEN   "\x1b[32m"
# define ANSI_COLOR_YELLOW  "\x1b[33m"
# define ANSI_COLOR_BLUE    "\x1b[34m"
# define ANSI_COLOR_MAGENTA "\x1b[35m"
# define ANSI_COLOR_CYAN    "\x1b[36m"
# define ANSI_COLOR_RESET   "\x1b[0m"

/* file descriptors */
# define STDIN	0
# define STDOUT	1
# define STDERR	2

/* return values */
# define ERROR	1
# define SUCCESS	0

# define _EMPTY	0
# define _PIPE	1
# define _EXEC	2
# define _REDIR	3
# define _INPUT	4
# define _APPEND	5
# define _TRUNC	6
# define _END	7

# define NONE 0
# define LEFT 1
# define RIGHT 2

# define BUFF_SIZE 4096
# define EXPANSION -36
# define IS_DIRECTORY 126
# define UNKNOWN_COMMAND 127


typedef struct s_token	t_token;
typedef struct s_cmd	t_cmd;
typedef struct s_exec	t_exec;
typedef struct s_pipe	t_pipe;
typedef struct s_redir	t_redir;

typedef struct s_env	t_env;
typedef struct s_shell	t_shell;

struct	s_env
{
	char	*env_name;
	char	*env_value;
	t_env	*next;
	t_env	*prev;
};

struct	s_cmd
{
	int	type;
};

struct	s_exec
{
	int		type;
	char	*args[200];
};

struct	s_pipe
{
	int		type;
	int		fd[2];
	t_cmd	*left;
	t_cmd	*right;
};

struct	s_redir
{
	int		type;
	t_cmd	*cmd;
	char	*file;
	int		mode;
	int		fd;
};

typedef enum e_placing
{
	IN_SQ,
	IN_DQ,
	DEFAULT,
}	t_placing;

/*  im using neg numbers bcs this are not single chars,
	and like this they do not mix up with ramdom ascii values */
typedef enum e_type
{
	WORD = -1,
	HEREDOC = -2,
	DREDIREC = -3,
	REDIR_IN = '<',
	REDIR_OUT = '>',
	SPACE_BAR = ' ',
	NEW_LINE = '\n',
	S_QUOTE = '\'',
	D_QUOTE = '\"',
	SCAPE = '\\',
	ENV = '$',
	PIPE = '|',
}t_type;

typedef struct s_token
{
	char		*token;
	t_type		type;
	int			len;
	t_placing	placing;
	t_token		*next;
	t_token		*prev;
}t_token;

typedef struct s_lexer
{
	t_token	*head;
	t_token	*official_head;
	t_token	*tail;
	int		size;
}t_lexer;

typedef struct s_shell
{
	char *cmd_line;
	char *prompt;
	char **env;
	char **paths;
	char	**path;
	t_lexer *token_list;
	t_lexer *rl;
	t_env *ev;
	t_cmd *root;
	int		in;
	int		out;
	int		fdin;
	int		fdout;
	t_pipe	*current_pipe;	
	t_pipe	*prev_pipe;
	int		last_status;
	int		pid;
	int		charge;	// need innitialization
	int		parent;	// need innitialization
	int		last;	// need innitialization
	int		ret;	// need innitialization
	int		no_exec;

	bool stop_iteration;
}t_shell;

/* MAIN. */
// void print_loop(char **s);
int		get_rid_off(char *alloced_mem);
int		count_word_size(char *cmdl, int i, int count, t_placing placing);
/* ANALISE.C */
void	analise_terminal_input(t_shell *shell, char *cmdline);
void	parse_tokens(t_shell *shell, char *cmdl);
void	print_tree(t_cmd *root);
void	delete_tree(t_cmd *root);
int		get_new_line(t_shell *sh, t_placing place);
void	refine_token_list(t_shell *sh);
void	handle_word_token(t_shell *sh);
void	handle_token(t_shell *sh, char *token);
void	add_to_refined_list(t_lexer *token_refined, char *word,
			t_type type);
void	analise_cmdl(t_shell *shell, t_placing place, int i, char *cmdl);

/* PIPE UTILS */
void	set_pipe_fds(t_shell *shell, t_cmd *cmd);


/* DESTROY_UTILS_ALL.C */
void	delete_env_lst(t_env *head, int size);
int		lst_size_env(t_env *head);
void	delete_token_lst(t_token *head, int size);
int		lst_size_tokens(t_token *head);
void	delete_2d_array(char **a);

/* DESTROY_ALL.C */
void	delete_tree(t_cmd *root);
void	delete_all(t_shell *shell);
void	clean_for_next_loop(t_shell *sh);

/* LIST_UTILS.C */
t_token	*ft_lstlast(t_token *head);
t_token	*new_node(char *token, t_type type, t_placing placing);
void	delete_lst(t_token **head, int size);
int		lst_size(t_token **head);
void	add_to_list(t_lexer *token_list, char *word,
			t_type type, t_placing placing);

/* TOKEN_UTILS.C */
// int handle_token(t_shell *sh, t_exec *ex, int i);
int		get_word(char *cmdl, int i, t_shell *sh,
			t_placing placing);
int		get_space(char *cmdl, int i, t_shell *sh,
			t_placing placing);
int		get_quote(t_shell *sh, t_placing *placing,
			char quote_type);
int		get_env_var(char *cmdl, int i, t_shell *sh,
			t_placing placing);
char	*expand_env_var(char *env_var, t_env *head);
int		valid_env(char *env_var, t_env *env_head);
char	*get_env_str(char *cmdl, int i);
int		get_pipe(t_shell *sh, t_placing placing);
int		get_redirect_var(char *cmdl, int i, t_shell *sh,
			t_placing placing);
/* organize var type is a secundary funct for 
get_redirect_var (on another words its an extension)*/
// void		organize_var_type(t_shell *sh, char *token, t_placing placing);
int		special_char(char c);
int		is_space(int c);
t_token	*jump_token(t_token *token, int action);

int		handle_single_quotes_type(int quote_type, t_shell *sh,
			t_placing *placing);
int		handle_double_quotes_type(int quote_type, t_shell *sh,
			t_placing *placing);

/* validate tree.c */
void	validate_tree(t_cmd *root, t_shell *sh);
char	**get_absolute_executable(t_exec *executable,
			t_shell *sh);
void	validate_exec(t_exec *executable_node, t_shell *sh);
char	**get_path(t_shell *sh);
int		is_path_env(char *s);

/* INIT_AST.c */
void	init_ast(t_shell *sh);
t_redir	*get_last_redir(t_cmd *sub_root);
t_redir	*handle_redir_type(t_shell *sh);
t_redir	*fill_redir(char *s, int mode, t_shell *sh);
int		peek_future_tokens_type(t_token *head, t_type type);
t_cmd	*pipe_parse(t_shell *sh, t_cmd *left);
t_cmd	*exec_parse(t_shell *sh, t_exec *exec_struct);
t_pipe	*init_pipe(void);
t_exec	*init_exec(void);
int		peek_token(t_token *checker, int var_nbr, ...);
t_redir	*init_redir(void);
// t_redir *check_redir(t_shell *sh,  t_token *node);
t_cmd	*parse_redir(t_cmd *branch_root, t_shell *sh);

/* CHECK_SYNTAX.C */
int		check_syntax(t_shell *sh);
int		check_pipe_sequence(t_token *token);

/* env_expand.c */
t_env	*expand_env(t_shell *shell, char **env);
t_env	*new_env_node(char *env);
		// prev e definido na funcao na qual este e chamada
char	*get_name(char *env_var);
char	*get_env_value(char *env_var);

/* EXECUTE */
void	execute_line(t_shell *shell);
t_cmd	*next_run(t_shell *shell);

/* FD UTILS */
void	close_fd(int fd);
void	reset_st_fd(t_shell *shell);
void	close_fds(t_shell *shell);
void	reset_fd(t_shell *shell);

/* STRING UTILS */
int		ft_splitt(char ***strs, char *s, char c);

/* MANAGE_SIGNALS */

void	signal_handler(int signal);
void	main_signal_handler(int signal);


#endif
