
#ifndef INTERVAL_H
# define INTERVAL_H

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX(X, Y)	(((X) > (Y)) ? (X) : (Y))
#define MIN(X, Y)	(((X) < (Y)) ? (X) : (Y))

#include "enums.h"
#include "structs.h"

t_set_interval			*set_intersection(t_sets_for_methods *sets);
t_set_interval			*set_difference(t_sets_for_methods *sets);
int						amount_of_intervals_in_set(t_set_interval *list);
char					*define_ineq(t_inequal_type x);
t_sqr_inequality		*declaretion_of_inequality(void);
void					calculation_of_quadratic_inequality(void);
t_set_interval			*set_union(t_sets_for_methods *sets);
int						combine_lists(t_sets_for_methods *sets);
t_set_interval			*chosen_method_for_set(t_sets_for_methods *sets, int x);
void					adding_t_interval(t_set_interval *set, t_interval *interval);
t_set_interval			*fill_the_set_with_intervals(t_set_interval	*set);
t_set_interval			*set_init(void);
void					init_sets_of_intervals();
int						reading(void);
void					command_line_input(void);
int						choose_an_input_method(void);
void					choose_a_method_for_intervals(t_intervals_for_methods *intervals);
char					*define_type_of_interval_by_enum(t_interval_type type);
int						define_type(t_interval *c);
t_set_interval			*difference_of_intervals(t_interval *a, t_interval *b);
t_set_interval			*init_set_interval(void);
t_set_interval			*union_of_intervals(t_interval *a, t_interval *b); 
t_interval				*initialize_interval(void);
t_interval				*set_borders(t_interval *a);
t_interval				*intersection(t_interval *a, t_interval *b);
t_interval				*no_intersection(void);
t_interval				*empty_int_declaration(void);
void					print_error(void);
void					mal_error(void);
void					val_error(void);
int						define_interval_type(int type);
t_interval				*single_point_declaration(void);
t_interval				*interval_declaration(int type);
t_interval				*infinity_interval(int type);
#endif
