#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/22 18:46:54 by pguillie          #+#    #+#              #
#    Updated: 2019/05/21 10:36:52 by pguillie         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

SERVER	= ftpd
CC	= gcc
CFLAGS	= -Wall -Werror -Wextra -I$(incdir) -g

incdir = ./include/
srcdir = ./src/

# server #

server_hdr = $(addprefix server/, \
	protocol_interpreter.h \
	replies.h \
	ftp_command.h \
	data_transfer_process.h \
)

server_src = $(addprefix server/, \
	main.c \
	server.c \
	$(addprefix protocol_interpreter/, \
		protocol_interpreter.c \
		ftp_exec.c \
		send_reply.c \
		die.c \
		read_line.c \
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
	$(addprefix data_transfer_process/, \
		data_transfer_process.c \
		transfer_function.c \
		dtp_list.c \
		dtp_port.c \
		connect_dtp.c \
		close_dtp.c \
	) \
)

server_obj = $(addprefix $(srcdir), $(server_src:%.c=%.o))

# rules #

.PHONY: all server clean fclean re

all: server

server: $(SERVER)

$(SERVER): $(server_obj)
	$(CC) -o $@ $^

$(server_obj): $(addprefix $(incdir), $(server_hdr))

clean:
	$(RM) $(server_obj)

fclean: clean
	$(RM) $(SERVER)

re: fclean all
