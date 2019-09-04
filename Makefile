#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/22 18:46:54 by pguillie          #+#    #+#              #
#    Updated: 2019/09/03 11:27:29 by pguillie         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME	= ftpd
CC	= gcc
CFLAGS	= -Wall -Werror -Wextra -I$(incdir)

LIBFT	= libft/libft.a

incdir = ./include/
srcdir = ./src/

# server

headers =					\
	protocol_interpreter.h			\
	ftp_command.h				\
	ftp_reply.h				\

sources =					\
	main.c					\
	server.c				\
	protocol_interpreter.c			\
	execute.c				\
	recv_command.c				\
	send_reply.c				\
	die.c					\
	user_name.c				\
	change_working_directory.c		\
	logout.c				\
	data_port.c				\
	representation_type.c			\
	retrieve.c				\
	store.c					\
	print_working_directory.c		\
	list.c					\
	system_type.c				\
	noop.c					\
	data_transfer_process.c			\
	dtp_retr.c				\
	dtp_stor.c				\
	dtp_list.c				\
	recv_data.c				\
	send_data.c				\

objects = $(addprefix $(srcdir), $(sources:%.c=%.o))

# rules

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(LIBFT) $(objects)
	$(CC) -o $@ $^ -L$(dir $(LIBFT)) -lft

$(objects): $(addprefix $(incdir), $(headers))

$(LIBFT):
	make -C $(dir $(LIBFT))

clean:
	make -C $(dir $(LIBFT)) fclean
	$(RM) $(objects)

fclean: clean
	$(RM) $(NAME)

re: fclean all
