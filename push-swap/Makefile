# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yhetman <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/30 15:04:19 by yhetman           #+#    #+#              #
#    Updated: 2019/10/19 18:02:46 by yhetman          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = main.c \
	   modify_lists.c \
	   sort_list.c

OBJ = $(addprefix $(OBJDIR), $(SRCS:.c=.o))

OBJDIR = ./obj/

SRCDIR = sources/

NAME = push_swap

FLAGS = -Wall -Wextra -Werror

DEBUG = -g3 -fsanitize=address

INCLUDE = -I./includes/

LIBNAME = libft.a

LIBPATH = ./libft/

all:$(NAME)

$(NAME): $(OBJDIR) $(LIBPATH)$(LIBNAME) $(OBJ)
	@gcc $(FLAGS) $(INCLUDE) $(LIBPATH)$(LIBNAME) -o $(NAME)

$(OBJDIR):
	@mkdir $(OBJDIR)

$(OBJDIR)%.o:$(SRCDIR)%.c
	@gcc $(FLAGS) $(INCLUDE) -c $< -o $@
	@ar -rv $(LIBPATH)$(LIBNAME) $@
	@ranlib $(LIBPATH)$(LIBNAME)

$(LIBPATH)$(LIBNAME):
	@make -C $(LIBPATH)

makelib:
	@make -C $(LIBPATH)

clean:
	@make clean -C $(LIBPATH)
	@rm -rf obj/

fclean: clean
	@make fclean -C $(LIBPATH)
	@rm -rvf $(NAME)

re: fclean all

.PHONY: all clean fclean re
