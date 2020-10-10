#* ************************************************************************** *#
#*                                                                            *#
#*                                                        :::      ::::::::   *#
#*   Makefile                                           :+:      :+:    :+:   *#
#*                                                    +:+ +:+         +:+     *#
#*   By: yhetman <yhetman@student.unit.ua>          +#+  +:+       +#+        *#
#*                                                +#+#+#+#+#+   +#+           *#
#*   Created: 2019/11/30 19:07:32 by yhetman           #+#    #+#             *#
#*   Updated: 2019/12/03 17:06:18 by yhetman          ###   ########.fr       *#
#*                                                                            *#
#* ************************************************************************** *#

NAME = phonebook
CL = clang++
FLAGS = -Wall -Wextra -Werror
SRCS := Contact.class.cpp output_phonebook.cpp main.cpp
HDRS := Contact.class.hpp
OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS) $(HDRS)
	@$(CL) $(OBJS) -o $@
	@echo '$(NAME)' "created!"

%.o: %.cpp %.hpp
	@$(CL) $(FLAGS) -o $@ -c $<

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)
	@echo '$(NAME)' "deleted!"

re: fclean all

.PHONY: all clean fclean re
