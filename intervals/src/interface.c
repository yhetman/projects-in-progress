#include "../headers/interval.h"
#include "../headers/enums.h"

int		choose_an_input_method(void) //	catch the user's input variable
{
	int x;

	printf("\033[1;36m");
	printf("To read intervals from the text file\t\tpress 0\n\n");
	printf("To input intervals via command line\t\tpress 1\n\n");
	printf("To read intervals from the binary file\t\tpress 2\n\n\033[0m");
	scanf("%d", &x);
	printf("\n\n");
	return(x);
}

t_set_interval			*set_init(void) 
/*	
*	user input the lengths of the Sets
*	and defines what method to use with the Sets of Intervals
*/
{
	t_sets_for_methods	*sets;
	int					x;

	sets = (t_sets_for_methods*)malloc(sizeof(t_sets_for_methods));
	sets->first_set = (t_set_interval *)malloc(sizeof(t_set_interval));
	sets->second_set = (t_set_interval *)malloc(sizeof(t_set_interval));
	printf("\033[1;32mHow many intervals would you like to initialize in the first Set?\n\n");
	sets->first_set = fill_the_set_with_intervals(sets->first_set);
	printf("\033[1;32mHow many intervals would you like to initialize in the second Set?\n\n");
	sets->second_set = fill_the_set_with_intervals(sets->second_set);
	printf("\033[1;35mWhich method would you like implement?\n\n");
	printf("\033[1;35mTo count the intersection of the Sets\t\t\tPress 1\033[0m\n\n");
	printf("\033[1;35mTo count the union of the Sets\t\t\t\tPress 2\033[0m\n\n");
	printf("\033[1;35mTo count the difference of the Sets\t\t\tPress 3\033[0m\n\n");
	printf("\033[1;35mTo count the length of the Intervals in the Set\t\tPress 4\033[0m\n\n");
	scanf("%d", &x);
	return (chosen_method_for_set(sets, x));
}

/*
*	user can choose what kind of Data to use in future calcutions:
*	1) two simple Intervals;
*	2) two endless Sets of Intervals (almost endless, depends on the memory of the computer ^.^ );
*/
void	command_line_input() 
{
	t_intervals_for_methods	*intervals;
	int						val;

	intervals = (t_intervals_for_methods*)malloc(sizeof(t_intervals_for_methods));
	printf("\033[1;32mTo use methods for the Sets of Intervals\t\tPress 1\n\n");
	printf("\033[1;32mTo use methods for two simple Intervals\t\t\tPress 2\n\n");
	printf("\033[1;32mTo calculate a quadratic inequality\t\t\tPress 3\n\n");
	printf("\033[1;32mTo calculate a quadratic inequality\t\t\tPress 4\n\n");
	scanf("%i", &val);
	switch (val)
	{
		case 1:
			init_sets_of_intervals();	// init_sets_of_intervals.c: initialize the Sets with values
			break;
		case 2:
		{
			printf("\033[1;32mNow initialize two Intervals\n\n");
			printf("Firstly, initialize the first Interval.\n\n");
			if(!(intervals->first = initialize_interval()))		// initialize_interval.c: memory allocation for ONE interval
				print_error(); 
				/*
				*	error management.c: 
				*	outputs the error if there was an implicit initialization of the variables in the interval
				*/
			printf("\033[1;32mNow initialize the second Interval.\033[0m\n\n");
			if(!(intervals->second = initialize_interval()))
				print_error();
			printf("\033[1;35m\n\nNow, when the Intervals are initialized, you can choose which method to use.\033[0m\n\n");
			choose_a_method_for_intervals(intervals); 
			/*	
			*	function gives user to choose which method he'd like to implement with the Data;
			*	function also outputs the result of calculation (output.c)
			*/
		}
		case 3:
			calculation_of_quadratic_inequality();
		//case 4:
		//	calculation_of_system_of_quadratic_inequality();
}
}