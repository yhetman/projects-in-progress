#include "../headers/interval.h"

void					adding_t_interval(t_set_interval *set, t_interval *interval) // adding an Interval to list;
{
	t_set_interval	*curr;

	curr = set;
	while (curr->next != NULL)
		curr = curr->next;
	curr->next = (t_set_interval *)malloc(sizeof(t_set_interval));
	curr->next->first = interval;
	curr->next->next = NULL;
}

t_set_interval			*fill_the_set_with_intervals(t_set_interval	*set) // defines the Sets with Intervals and its values;
{
	int	count;

	scanf("%d", &count);
	set->first = (t_interval*)malloc(sizeof(t_interval));
	set->next = NULL;
	while (count)
	{
		adding_t_interval(set, initialize_interval()); // add intervals to linked list;
		count--;
	}
	return (set);
}

t_set_interval			*chosen_method_for_set(t_sets_for_methods *sets, int x) //catch the value of the process;
{
	t_set_interval		*result_set;

	switch(x)
	{
		case 1:
			result_set = set_intersection(sets);
			break;
		case 2:
			result_set = set_union(sets); // union.c
			break;
		case 3:
			result_set = set_difference(sets); 
			break;
		case 4:
			//result_set = set_length(sets);
			break;
	}
	return (result_set);
}

void	init_sets_of_intervals()
{
	t_set_interval	*result;

	result = set_init(); //interface.c
	//output_the_result_of_method();
}
