#ifndef STRUCTS_H
# define STRUCTS_H
#include "enums.h"
#include "interval.h"

typedef struct				s_interval
{
	double					a;
	double					b;
	bool					left;
	bool					right;
	t_interval_type			type;
}							t_interval;

typedef struct				s_intervals_for_methods
{
	t_interval				*first;
	t_interval				*second;
}							t_intervals_for_methods;

typedef struct				s_set_interval
{
	t_interval				*first;
	struct s_set_interval	*next;
}							t_set_interval;

typedef struct				s_sets_for_methods
{
	t_set_interval			*first_set;
	t_set_interval			*second_set;
}							t_sets_for_methods;

typedef struct				s_sqr_inequality
{
	double					a;
	double					b;
	double					c;
	t_inequal_type			type;
}							t_sqr_inequality;

typedef struct				s_system_of_sqr_inequalities
{
	t_sqr_inequality		*first;
	t_sqr_inequality		*next;
}							t_system_of_sqr_inequalities;


#endif
