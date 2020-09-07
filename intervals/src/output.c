
#include "../headers/interval.h"
#include "../headers/enums.h"

char	*define_type_of_interval_by_enum(t_interval_type type)
// function to define the outputed string based on the values of enum;
{
	char	*type_of_interval;

	switch (type)
	{
		case 1:
			type_of_interval = strdup("empty interval");
			break;
		case 2:
			type_of_interval = strdup("only point");
			break;
		case 3:
			type_of_interval = strdup("opened interval");
			break;
		case 4:
			type_of_interval = strdup("closed interval");
			break;
		case 5:
			type_of_interval = strdup("half closed left interval");
			break;
		case 6:
			type_of_interval = strdup("half closed right interval");
			break;
		case 7:
			type_of_interval = strdup("infinity from the left side");
			break;
		case 8:
			type_of_interval = strdup("infinity from the right side");
			break;
		case 9:
			type_of_interval = strdup("infinity from the both sides");
			break;
	}
	return (type_of_interval);
}


void	choose_a_method_for_intervals(t_intervals_for_methods *intervals) //user choose what method to use
{
	int				x;
	t_interval		*result;
	t_set_interval	*diff_result;

	result = (t_interval*)malloc(sizeof(t_interval));
	bzero(result, sizeof(t_interval));
	diff_result = init_set_interval(); // allocation of the memory for the set of the intevals
	printf("\033[1;35mTo count the intersection of the Intervals\t\tPress 1\033[0m\n\n");
	printf("\033[1;35mTo count the union of the Intervals\t\t\tPress 2\033[0m\n\n");
	printf("\033[1;35mTo count the difference of the Intervals\t\tPress 3\033[0m\n\n");
	scanf("%d", &x);
	switch (x)
	{
		case 1:
			result = intersection(intervals->first, intervals->second); // A ∩ B = {x | x ∈ A && x ∈ B}
			break;
		case 2:
			diff_result = union_of_intervals(intervals->first, intervals->second); // A ∪ B = {x | x Є A || x Є B}
			break;
		case 3:
			diff_result = difference_of_intervals(intervals->first, intervals->second); //calculates the difference of the first Interval
			break;
	}
	/* printing of the result */
	if (x == 1)
		printf("(%.2lf;\t%.2lf)\n%s\n", result->a, result->b,
		define_type_of_interval_by_enum(result->type));
		// function to define the outputed string based on the values of enum;
	else
		printf("(%.2lf;\t%.2lf)\n%s\n(%.2lf;\t%.2lf)\n%s\n", diff_result->first->a,
		diff_result->first->b, define_type_of_interval_by_enum(diff_result->first->type),
		diff_result->next->first->a, diff_result->next->first->b,
		define_type_of_interval_by_enum(diff_result->next->first->type));
		// function to define the outputed string based on the values of enum;
}
