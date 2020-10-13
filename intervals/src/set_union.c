
#include "../headers/interval.h"

int		combine_lists(t_sets_for_methods *sets) //link two list in one to make further calculations easier
{
	t_set_interval	*curr;
	int				i;

	i = -1;
	curr = sets->first_set;
	while ((++i) && curr->next != NULL)
			curr = curr->next;
	curr->next = (t_set_interval *)malloc(sizeof(t_set_interval));
	curr->next = sets->second_set;
	while ((++i) && curr->next != NULL)
		curr = curr->next;
	curr->next = NULL;
	return (i);
}

t_set_interval		*set_union(t_sets_for_methods *sets) //calculation of union of the Sets;
{
	t_set_interval	*result;
	t_set_interval	*current;
	int				list_length;
	
	list_length = combine_lists(sets) / 2;
	while (list_length)
	{
		current = sets->first_set;
		while (current != NULL)
		{
			result = union_of_intervals(current->first,
			current->next->first);
			while (result != NULL)
				result = result->next;
			current = current->next;
		}
		list_length--;
	}
	return(result);
}
