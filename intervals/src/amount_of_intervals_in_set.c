#include "../headers/interval.h"

int	amount_of_intervals_in_set(t_set_interval *list)
{
	int				iterator;
	t_set_interval	*current;

	current = list;
	for (iterator = 0; current->next != NULL; iterator++)
		current = current->next;
	current->next = NULL;
	return(iterator);
}