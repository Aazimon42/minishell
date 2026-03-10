# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: edi-maio <edi-maio@42angouleme.fr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/27 17:10:17 by edi-maio          #+#    #+#              #
#    Updated: 2026/03/10 13:27:29 by malebrun         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBFT = libft/libft.a

CFLAGS = -Wall -Wextra -Werror -g

C_FILES = main.c \
		  instruction.c \
		  parse.c \
		  builtin.c \
		  exec.c \
		  utils.c \
		  envar.c \
		  envcmd.c \
		  printenv.c \
		  exit.c \
		  envarhandler.c \
		  utils2.c \
		  path.c \
		  heredoc.c \
		  redirection.c \
		  exec_utils.c \
		  pipe.c \
		  utils3.c \
		  utils4.c

SRCS = $(addprefix srcs/,$(C_FILES))

OBJS = $(SRCS:.c=.o)

.o: .c
	cc $(CFLAGS) -I $(INCLUDES) -c $< -o $@

all: $(NAME) clean

$(LIBFT):
	make -C libft all

$(NAME): $(OBJS) $(LIBFT)
	cc $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -o $(NAME)

clean:
	rm -f $(OBJS)
	make -C libft clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean

re: fclean all

.PHONY: all clean fclean re
