# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/23 21:29:48 by fde-jesu          #+#    #+#              #
#    Updated: 2024/08/03 05:27:54 by fde-jesu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
HEADER = libft.h
CFLAGS = -Wall -Werror -Wextra

#FUN = $(wildcard *.c)
FUN = ft_atoi.c\
		ft_bzero.c\
		ft_calloc.c\
		ft_check_specifier.c\
		ft_count.c\
		ft_find_chrs.c\
		ft_firstword.c\
		ft_hexa_p.c\
		ft_hexa_xs.c\
		ft_isalnum.c\
		ft_isalpha.c\
		ft_isascii.c\
		ft_isdigit.c\
		ft_isprint.c\
		ft_itoa.c\
		ft_lstclear.c\
		ft_lstdelone.c\
		ft_lstsize.c\
		ft_memchr.c\
		ft_memcmp.c\
		ft_memcpy.c\
		ft_memmove.c\
		ft_memset.c\
		ft_printf_putnbr.c\
		ft_printf.c\
		ft_putchar_fd.c\
		ft_putchar.c\
		ft_putendl_fd.c\
		ft_putnbr_fd.c\
		ft_putnbr_u.c\
		ft_putstr_fd.c\
		ft_split.c\
		ft_strchr.c\
		ft_strdup.c\
		ft_striteri.c\
		ft_strjoin.c\
		ft_strlcat.c\
		ft_strlcat.c\
		ft_strlen.c\
		ft_strmapi.c\
		ft_strncmp.c\
		ft_strnstr.c\
		ft_strrchr.c\
		ft_strtrim.c\
		ft_substr.c\
		ft_tolower.c\
		ft_toupper.c\
		ft_writing.c\
		get_next_line_utils.c\
		get_next_line.c\
		s_malloc.c
RED:=\033[0;31m
default_colour=\033[0m
OBJ = ${FUN:.c=.o}

all: $(NAME)

$(NAME):
	    cc ${CFLAGS} -c ${HEADER} ${FUN}
		ar rc ${NAME} ${OBJ}
#		@echo "${RED}RETIRAR WILDCARD NO LIBFT${default_colour}\n"
clean:
	rm -f $(OBJ) 

fclean: clean
	rm -f $(NAME)
      
re: fclean all

.PHONY: all clean fclean re
.SILENT:
