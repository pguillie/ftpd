#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/22 18:46:54 by pguillie          #+#    #+#              #
#    Updated: 2019/11/24 15:30:59 by pguillie         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME	= ftpd
CC	= gcc
CFLAGS	= -Wall -Werror -Wextra -I$(incdir) $(DEBUG)

LIBFT	= libft/libft.a
LIBS	= -L$(dir $(LIBFT)) -lft

os != uname
ifeq ($(os), Linux)
	LIBS += -lcrypt
endif

incdir = ./include/
srcdir = ./src/

# server

headers =					\
	protocol_interpreter.h			\
	ftp_command.h				\
	ftp_reply.h				\

sources =					\
	main.c					\
	invocation.c				\
	server.c				\
	run_service.c				\
	connection_manager.c			\
	session_manager.c			\
	auth.c					\
	sys_auth.c				\
	login.c					\
	protocol_interpreter.c			\
	ftp_log.c				\
	set_command.c				\
	recv_command.c				\
	send_reply.c				\
	close_session.c				\
	chroot_home.c				\
	die.c					\
	ftp_user.c				\
	ftp_pass.c				\
	ftp_cwd.c				\
	ftp_quit.c				\
	ftp_port.c				\
	ftp_type.c				\
	ftp_retr.c				\
	ftp_stor.c				\
	ftp_abor.c				\
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
	$(CC) -o $@ $^ $(LIBS) $(DEBUG)

$(objects): $(addprefix $(incdir), $(headers))

$(LIBFT):
	make -C $(dir $(LIBFT))

debug:
	make re DEBUG='-fsanitize=address'

clean:
	make -C $(dir $(LIBFT)) fclean
	$(RM) $(objects)

fclean: clean
	$(RM) $(NAME)

re: fclean all
