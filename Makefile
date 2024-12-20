NAME:= minishell
CFLAGS:= -g #-Wall -Werror -Wextra

HEADER = includes/minishell.h
GREEN:= \033[0;32m
RED:=\033[0;31m 
BLUE=\033[0;34m
default_colour=\033[0m

SRC_FILES:=  main.c \
					analise.c \
					check_syntax.c\
					signals.c\
					create_first_list_utils_1.c\
					create_first_list_utils_2.c\
					create_first_list.c\
					create_second_list.c\
					list_utils.c \
					delete_tree.c\
					destroy_all.c\
					destroy_utils.c\
					env_expand.c\
					env_token_functions.c\
					init_AST_structs.c\
					init_AST.c\
					lexer_utils.c\
					redir_management.c\
					search_through_tokens.c\
					token_utils.c\
					fd_utils.c\
					tree_encrementation.c\
					execution.c\
					ft_pwd.c\
					ft_env.c\
					ft_export.c\
					ft_unset.c\
					ft_echo.c\
					ft_cd.c\
					ft_exit.c\
					is_builtin.c\
#					exec.c\
#					pipe_utils.c \
	
#		mini_cd.c\
#		mini_echo.c\
#		mini_env.c\
#		mini_exit.c\
#		mini_export.c\
#		mini_pwd.c\
#		mini_unset.c\
					string_funcs.c
#					init_tree.c\
					tree_validation.c\

MAKE:= make -j  -C
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


