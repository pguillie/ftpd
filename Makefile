#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/22 18:46:54 by pguillie          #+#    #+#              #
#    Updated: 2019/05/23 13:59:36 by pguillie         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

SERVER	= ftpd
CC	= gcc
CFLAGS	= -Wall -Werror -Wextra -I$(incdir) -g

LIBFT	= libft/libft.a

incdir = ./include/
srcdir = ./src/

# server

server_hdr = $(addprefix server/, \
	protocol_interpreter.h \
	replies.h \
	ftp_command.h \
)

server_src = $(addprefix server/, \
	main.c \
	server.c \
	$(addprefix protocol_interpreter/, \
		protocol_interpreter.c \
		ftp_exec.c \
		send_reply.c \
		die.c \
		$(addprefix ftp_command/, \
			user_name.c \
			change_working_directory.c \
			logout.c \
			data_port.c \
			print_working_directory.c \
			list.c \
			system_type.c \
		) \
	) \
	$(addprefix dtp/, \
		data_transfer_process.c \
		dtp_list.c \
	) \
)

server_obj = $(addprefix $(srcdir), $(server_src:%.c=%.o))

# rules

.PHONY: all server clean fclean re

all: $(LIBFT) server

server: $(SERVER)

$(SERVER): $(server_obj)
	$(CC) -o $@ $^ -L$(dir $(LIBFT)) -lft

$(server_obj): $(addprefix $(incdir), $(server_hdr))

$(LIBFT):
	make -C $(dir $(LIBFT))

clean:
	make -C $(dir $(LIBFT)) fclean
	$(RM) $(server_obj)

fclean: clean
	$(RM) $(SERVER)

re: fclean all
