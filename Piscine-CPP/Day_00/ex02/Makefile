#* ************************************************************************** *#
#*                                                                            *#
#*                                                        :::      ::::::::   *#
#*   Makefile                                           :+:      :+:    :+:   *#
#*                                                    +:+ +:+         +:+     *#
#*   By: yhetman <yhetman@student.unit.ua>          +#+  +:+       +#+        *#
#*                                                +#+#+#+#+#+   +#+           *#
#*   Created: 2019/12/03 18:29:11 by yhetman           #+#    #+#             *#
#*   Updated: 2019/12/03 18:29:13 by yhetman          ###   ########.fr       *#
#*                                                                            *#
#* ************************************************************************** *#

C		=	clang++
FLAGS	=	-Wall -Wextra -Werror

NAME	=	account
RES		=	resources/
SRC		=	Account.class.cpp \
			$(RES)tests.cpp
OBJ		=	$(SRC:.cpp=.o)
INC		=	-I $(RES)


all: $(NAME)

$(NAME): $(OBJ)
	@ $(C) -o $(NAME) $(FLAGS) $(OBJ)
	@ echo "account created!"
	
%.o: %.cpp
	@$(C) $(INC) $(FLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)
	@ echo "account deleted!"

re: fclean all

.PHONY: all clean fclean re
