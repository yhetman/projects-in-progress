#include "../headers/interval.h"

t_interval	*no_intersection(void) // 
{
	printf("The Intervals do not have an INTERSECTION!");
	return(empty_int_declaration());
}

t_interval	*intersection(t_interval *a, t_interval *b) // A ∩ B = {x | x ∈ A && x ∈ B}
{
	t_interval	*c;

	if (!(c = (t_interval*)malloc(sizeof(t_interval))))
		mal_error();
	if (a->b < b->a)
		return(no_intersection());
	else
	{
		c->a = MAX(a->a, b->a); //macros defined in interval.h
		c->b = MIN(a->b, b->b); //macros defined in interval.h
	}
	if (a->right && b->left)
		c->type = close_interval;
	else
		c->type = open_interval;
	return(set_borders(c)); // defines the type of the borders for the Interval
}
