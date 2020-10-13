#include "../headers/interval.h"

t_set_interval	*init_set_interval(void) // function allocates memory for the Set of intervals and fills it with Zeroes
{
	t_set_interval	*set_interval;

	if (!(set_interval = (t_set_interval*)malloc(sizeof(t_set_interval))))
		mal_error(); // error_management.c: outputs the error if mamory allocation was FAILED
	bzero(set_interval, sizeof(t_set_interval)); // fills allocated memory with Zeroes
	set_interval->first = (t_interval*)malloc(sizeof(t_interval));
	bzero(set_interval->first, sizeof(t_interval));
	set_interval->next = NULL;
	return(set_interval);
}

t_set_interval	*difference_of_intervals(t_interval *a, t_interval *b) // A\B = A'
{
	t_set_interval	*complex_interval;

	complex_interval = init_set_interval(); // allocation of memory
	if (a->type == empty_interval || b->type == empty_interval)
		complex_interval->first = a;
	if (a->a >= b->a)
	{
		if (a->b <= b->b)
			complex_interval->first = empty_int_declaration(); // initialize_interval.c: declare the interval as an empty one
		else
		{
			complex_interval->first->a = b->b;
			complex_interval->first->b = a->b;
			((b->right == true) ? (complex_interval->first->left = false) : (complex_interval->first->left = true));
			complex_interval->first->right = a->right;	
		}
	}
	if (a->a < b->a)
	{
		complex_interval->first->a = a->a;
		complex_interval->first->b = b->a;
		complex_interval->first->left = a->left;
		((b->left == false) ? (complex_interval->first->right = true) : (complex_interval->first->right = false));
		if (a->b > b->b)
		{
			complex_interval->next = init_set_interval();
			complex_interval->next->first->a = b->b;
			complex_interval->next->first->b = a->b;
			((b->right == true) ? (complex_interval->next->first->left = false) : (complex_interval->next->first->left = true));
			complex_interval->next->first->right = a->right;
		}
	complex_interval->first->type = define_type(complex_interval->first); // union.c: defines type 
	complex_interval->next->first->type = define_type(complex_interval->next->first);
	}
	return (complex_interval);	
}
