#include "../headers/interval.h"

void	print_error(void)
{
	printf("\033[1;31mERROR! PLEASE CHECK THE INPUT VALUES!\033[0m\n\n");
	exit(EXIT_FAILURE);
}

void	mal_error(void) 
{
	printf("\033[1;31mERROR: not enough memory for initialization!\033[0m\n\n");
	exit(EXIT_FAILURE);
}

void	val_error(void)
{
	printf("\033[1;31mERROR! Value a is greater than b!\033[0m\n\n");
	exit(EXIT_FAILURE);
}