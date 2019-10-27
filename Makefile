#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/22 18:46:54 by pguillie          #+#    #+#              #
#    Updated: 2019/10/27 06:50:15 by pguillie         ###   ########.fr        #
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
	session_manager.c			\
	auth.c					\
	protocol_interpreter.c			\
	server_log.c				\
	set_command.c				\
	recv_command.c				\
	send_reply.c				\
	close_session.c				\
	die.c					\
	ftp_user.c				\
	ftp_pass.c				\
	ftp_cwd.c				\
	ftp_quit.c				\
	ftp_port.c				\
	ftp_type.c				\
	ftp_retr.c				\
	ftp_stor.c				\
	ftp_pwd.c				\
	ftp_list.c				\
	ftp_syst.c				\
	ftp_noop.c				\
	ftp_eprt.c				\
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
	$(CC) -lcrypt -o $@ $^ -L$(dir $(LIBFT)) -lft

$(objects): $(addprefix $(incdir), $(headers))

$(LIBFT):
	make -C $(dir $(LIBFT))

clean:
	make -C $(dir $(LIBFT)) fclean
	$(RM) $(objects)

fclean: clean
	$(RM) $(NAME)

re: fclean all
