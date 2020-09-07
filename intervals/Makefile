NAME := Interval

SRC_PATH := src/
H_PATH := headers/
OBJ_PATH := obj/

CC := gcc -g
HFLAGS := -I $(H_PATH)

HFILES :=	interval	\
			enums		\
			structs

FILES :=	initialize_interval	\
			intersection		\
			error_management	\
			union				\
			difference			\
			interface			\
			init_sets_of_intervals\
			input				\
			output				\
			set_union			\
			set_difference		\
			set_intersection	\
			sqr_inequalities	\
			amount_of_intervals_in_set \
			main

HDRS := $(addprefix $(H_PATH), $(addsuffix .h, $(HFILES)))
SRCS := $(addprefix $(SRC_PATH), $(addsuffix .c, $(FILES)))
OBJS := $(addprefix $(OBJ_PATH), $(SRCS:%.c=%.o))

all: $(NAME)

$(NAME): $(OBJ_PATH) $(OBJS)
	$(CC) $(HFLAGS) $(OBJS) -o $(NAME)

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)$(SRC_PATH)

$(OBJ_PATH)%.o: %.c $(HDRS)
		$(CC) $(HFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_PATH)

fclean: clean
	rm -rf $(NAME)

re: fclean all
