#* ************************************************************************** *#
#*                                                                            *#
#*                                                        :::      ::::::::   *#
#*   Makefile                                           :+:      :+:    :+:   *#
#*                                                    +:+ +:+         +:+     *#
#*   By: yhetman <yhetman@student.unit.ua>          +#+  +:+       +#+        *#
#*                                                +#+#+#+#+#+   +#+           *#
#*   Created: 2019/11/30 19:07:32 by yhetman           #+#    #+#             *#
#*   Updated: 2019/11/30 19:27:45 by yhetman          ###   ########.fr       *#
#*                                                                            *#
#* ************************************************************************** *#

NAME = megaphone
CC = clang++
FLAGS = -Wall -Wextra -Werror
SRC = megaphone.cpp

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(FLAGS) $(SRC) $^ -o $(NAME)
	@echo '$(NAME)' "created!"

$(OBJ): $(SRC)
	@mkdir -p .obj
	@$(CC) -c $< -o $@

clean:
	@rm -rf .obj/

fclean: clean
	@rm -rf $(NAME)
	@echo '$(NAME)' "deleted!"

re: fclean all

.PHONY: clean fclean re all
