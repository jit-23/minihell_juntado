NAME:= minishell
CFLAGS:= -g #-Wall -Werror -Wextra

HEADER = includes/minishell.h
GREEN:= \033[0;32m
RED:=\033[0;31m 
BLUE=\033[0;34m
default_colour=\033[0m

SRC_FILES:=  main.c \
					analise.c\
					check_syntax.c\
					signals.c\
					create_first_list_utils_1.c\
					create_first_list_utils_2.c\
					create_first_list.c\
					create_second_list.c\
					list_utils.c\
					delete_tree.c\
					destroy_all.c\
					destroy_utils.c\
					env_expand.c\
					env_token_functions.c\
					init_AST.c\
					init_AST_structs.c\
					init_AST_exec_struct.c\
					init_AST_utils.c\
					init_AST_pipe_struct.c\
					lexer_utils.c\
					redir_management.c\
					search_through_tokens.c\
					token_utils.c\
					execution.c\
					ft_pwd.c\
					ft_env.c\
					ft_export.c\
					ft_unset.c\
					ft_echo.c\
					ft_cd.c\
					ft_exit.c\
					is_builtin.c\
					heredoc_execution.c\
					execute_redir.c\
					execute_pipe.c\
					execute_cmd.c\
					ft_export_utils.c\
					main_utils.c \
					init_AST_exec_struct_utils.c\
					execute_cmd_error.c
MAKE:= make -C
LIBFT_DIR:= includes/libft
LIBFT:= includes/libft/libft.a

OBJ_FILES:= $(patsubst %.c, %.o, $(SRC_FILES))

SRC_PATH:= src/
OBJ_PATH:= obj/

SRC = $(addprefix $(SRC_PATH), $(SRC_FILES))
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_FILES))

all: ${NAME}

${COMP_LIB}:
		echo "${RED}DONE${default_colour}"
#		${MAKE} ${LIBFT_DIR}

$(OBJ_PATH)%.o : $(SRC_PATH)%.c
		${COMP_LIB}
		@mkdir -p ${OBJ_PATH}
		cc   ${CFLAGS}  -c $< -o $@

${NAME}:  ${OBJ} 
#		${MAKE} ${LIBFT_DIR}
		cc  -I. ${CFLAGS} ${OBJ} ${LIBFT} -o ${NAME} -lreadline
		@echo "${GREEN}executable file: ./${NAME}${default_colour}\n"

clean:
#		${MAKE} ${LIBFT_DIR} clean
		@rm -fr ${OBJ_PATH}
		@echo "${RED}object files and directory deleted:${default_colour}"

fclean: clean
#		${MAKE} ${LIBFT_DIR} fclean
		@rm -f ${NAME}
		@echo "${RED}executable deleted:$(default_colour)"
		@echo "${RED}deleted all:$(default_colour)\n"

re : fclean all

.PHONY: all re clean fclean normi
.SIELNT:


