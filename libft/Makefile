#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/22 04:54:10 by pguillie          #+#    #+#              #
#    Updated: 2019/05/27 08:45:11 by pguillie         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME	= libft.a
CC	= gcc
CFLAGS	= -Wall -Werror -Wextra -I$(incdir)
AS	= nasm
ASFLAGS	= $(ARCH)
AR	= ar
ARFLAGS	= crU

ifeq ($(shell uname), Linux)
	ARCH := -felf64
else
	ARCH := -fmacho64 --prefix _
endif

incdir = ./include/
srcdir = ./src/

hdr = libft.h libfts.h ft_ctype.h

obj = $(addprefix $(srcdir), \
	read_line.o \
	ft_memmem.o \
	ft_strndup.o \
	ft_atoi.o \
	ft_bzero.o \
	ft_cat.o \
	ft_memchr.o \
	ft_memcmp.o \
	ft_memcpy.o \
	ft_memset.o \
	ft_putchar.o \
	ft_puts.o \
	ft_strcat.o \
	ft_strchr.o \
	ft_strcmp.o \
	ft_strdup.o \
	ft_strlen.o \
	ft_tolower.o \
	ft_toupper.o \
		$(addprefix ctype/, \
		ft_ctype.o \
		ft_isalnum.o \
		ft_isalpha.o \
		ft_isascii.o \
		ft_isblank.o \
		ft_iscntrl.o \
		ft_isdigit.o \
		ft_isgraph.o \
		ft_islower.o \
		ft_isprint.o \
		ft_ispunct.o \
		ft_isspace.o \
		ft_isupper.o \
		ft_isxdigit.o \
	) \
)

# rules

.PHONY: all clean fclean re
.oECONDARY: $(obj)

all: $(NAME)

$(NAME): $(NAME)($(obj))
	ranlib $@

$(obj): $(addprefix $(incdir), $(hdr))

clean:
	$(RM) $(obj)

fclean: clean
	$(RM) $(NAME)

re: fclean all
