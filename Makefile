# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/17 14:04:43 by eamsalem          #+#    #+#              #
#    Updated: 2025/02/20 15:17:48 by eamsalem         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	miniRT

CFLAGS = -Wall -Werror -Wextra -g3

SRCDIR = ./srcs
PARSEDIR = $(SRCDIR)/parse
SRCS =	$(SRCDIR)/main.c \
		$(SRCDIR)/utils.c \
		$(PARSEDIR)/parse.c \
		$(PARSEDIR)/parse_utils.c \
		$(PARSEDIR)/parse_scene.c \
		$(PARSEDIR)/parse_objects.c

OBJDIR = ./build
OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

MLXDIR = ./includes/mlx_linux
MLXLIB = $(MLXDIR)/libmlx_Linux.a

LIBFTDIR = ../libft
LIBFT = $(LIBFTDIR)/libft.a

all: $(OBJDIR) $(NAME) $(MLXLIB) $(LIBFT)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	mkdir -p $(@D)
	cc $(CFLAGS) -I/usr/include -I$(MLXDIR) -I$(SRCDIR) -c $< -o $@

$(NAME): $(MLXLIB) $(LIBFT) $(OBJDIR) $(OBJS)
	cc $(CFLAGS) $(OBJS) $(MLXLIB) $(LIBFT) -lXext -lX11 -lm -lz -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(MLXLIB):
	make -C $(MLXDIR) all

$(LIBFT):
	make -C $(LIBFTDIR) all

clean:
	make -C $(LIBFTDIR) clean
	rm -fr $(OBJDIR)

fclean: clean
	make -C $(LIBFTDIR) fclean
	rm -fr $(NAME)

re: fclean all

.PHONY: all clean fclean re
