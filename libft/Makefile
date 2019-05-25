#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/22 04:54:10 by pguillie          #+#    #+#              #
#    Updated: 2019/05/25 16:23:09 by pguillie         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME	= libft.a
CC	= gcc
CFLAGS	= -Wall -Werror -Wextra -I$(incdir)
AR	= ar
ARFLAGS	= cr

incdir = ./include/
srcdir = ./src/

hdr = libft.h

src = get_next_line.c ft_memmem.c

obj = $(addprefix $(srcdir), $(src:%.c=%.o))

# rules

.PHONY: all clean fclean re
.SECONDARY: $(obj)

all: $(NAME)

$(NAME): $(NAME)($(obj))
	ranlib $@

$(obj): $(addprefix $(incdir), $(hdr))

clean:
	$(RM) $(obj)

fclean: clean
	$(RM) $(NAME)

re: fclean all
