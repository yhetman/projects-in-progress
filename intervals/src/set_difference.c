#include "../headers/interval.h"

t_set_interval		*set_difference(t_sets_for_methods *sets)
{
	t_set_interval	*result;
	t_set_interval	*first;
	t_set_interval	*second;
	int				i;
	int				j;

	first = sets->first_set;
	second = sets->second_set;
	i = amount_of_intervals_in_set(sets->first_set) + 1;
	j = amount_of_intervals_in_set(sets->second_set) + 1;
	while (--i && first->next != NULL)
	{
		while(--j && second->next != NULL)
		{
			result = difference_of_intervals(first->first, second->first);
			while (result->next != NULL)
				result = result->next;
			result->next = (t_set_interval *)malloc(sizeof(t_set_interval));
			second = second->next;
		}
		first = first->next;
	}
	return(result);
}
