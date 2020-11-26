#* ************************************************************************** *#
#*                                                                            *#
#*                                                                            *#
#*   Makefile                                                                 *#
#*                                                                            *#
#*   By: yhetman <yhetman@student.unit.ua>                                    *#
#*                                                                            *#
#*   Created: 2020/10/28 00:02:38 by yhetman                                  *#
#*   Updated: 2020/10/28 10:45:51 by yhetman                                  *#
#*                                                                            *#
#* ************************************************************************** *#

SRCS = automateArithmeticOperator.c  automateComparisonOperator.c  automateNumber.c        checkers.c \
automateAsignationOperator.c  automateGroupingOperator.c    automatePreprosessor.c \
automateCharString.c automateIdentificator.c automatePunctuation.c   utils.c \
automateComment.c automateLogicalOperator.c automateRealNumber.c writers.c


SRCS_DIR = sources/

OBJ = $(addprefix $(OBJ_DIR), $(SRCS:.c=.o))

OBJ_DIR = obj/

CURR_PATH = .

LEXER = lexer

FLAGS = -I includes -Wall -Wextra -Werror
INC = lexer.a

DEBUG_FLAGS = -g3 -fsanitize=address

LEXER_MAIN = sources/lexer.c

all: make_obj_dir $(LEXER)

make_obj_dir:
	@mkdir -p $(OBJ_DIR)

$(LEXER): $(INC) $(LEXER_MAIN)
	gcc $(FLAGS) $(LEXER_MAIN) $(INC) -o $(LEXER)

$(INC): $(OBJ)
	ar -rv $(INC) $^
	ranlib $(INC)


$(OBJ_DIR)%.o: $(SRCS_DIR)%.c
	gcc $(FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	rm -f $(INC)

fclean: clean
	rm -f $(LEXER)
	rm -f $(INC)

re: fclean all

.PHONY: all clean fclean re