#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/22 18:46:54 by pguillie          #+#    #+#              #
#    Updated: 2019/05/13 14:21:30 by pguillie         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

SERVER	= ftpd
CC	= gcc
CFLAGS	= -Wall -Werror -Wextra -I$(incdir)

incdir = ./include/
srcdir = ./src/

# server #

server_hdr = $(addprefix server/, \
	server.h \
	replies.h \
	ftp_command.h \
)

server_src = $(addprefix server/, \
	main.c \
	server.c \
	protocol_interpreter.c \
	ftp_exec.c \
	send_reply.c \
	die.c \
	read_line.c \
	get_next_line.c \
	$(addprefix ftp_command/, \
		user_name.c \
		print_working_directory.c \
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
