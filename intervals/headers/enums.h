
#ifndef ENUMS_H
# define ENUMS_H

#include "interval.h"

typedef enum		e_interval_type
{
	empty_interval = 1,
	only_point,
	open_interval,
	close_interval,
	half_close_left,
	half_close_right,
	endless_left,
	endless_right,
	endless_both = 9
}					t_interval_type;

typedef enum		e_inequality_type
{
	greater = 1,
	less,
	equal,
	not_equal,
	greater_or_equal,
	less_or_equal
}					t_inequal_type;

#endif