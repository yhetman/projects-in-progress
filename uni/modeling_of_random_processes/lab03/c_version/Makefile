#* ************************************************************************** *#
#*                                                                            *#
#*                                                                            *#
#*   Makefile                                                                 *#
#*                                                                            *#
#*   By: yhetman <yhetman@student.unit.ua>                                    *#
#*                                                                            *#
#*   Created: 2021/02/15 15:32:13 by yhetman                                  *#
#*   Updated: 2021/02/15 15:32:14 by yhetman                                  *#
#*                                                                            *#
#* ************************************************************************** *#

NAME = fractal

CC = gcc

FLAG = -Wall  -Wextra -O3

SRC = main.c init_structs.c draw.c color_palettes.c fractal_math.c 
INCLUDE = ./includes

SRO = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(SRO)
	make -C ./libft/
	$(CC) $(FLAG) -I$(INCLUDE) $(SRC) -lmlx -lXext -lX11 ./libft/libft.a -o $(NAME)

%.o: %.c ./includes/fractal.h
	$(CC) $(FLAG) -c -o $@ $<

clean:
	make -C libft/ clean
	rm -f $(SRO)

fclean: clean
	make -C libft/ fclean
	rm -Rf $(NAME)

re: fclean all
	
