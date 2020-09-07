#include "../headers/interval.h"
#include "../headers/enums.h"

int		reading() //function for reading data
{
	FILE		*fptr;
	int			x;
	char		s;

	x = choose_an_input_method(); //user can choose how to input the data (interface.c);
	if (x == 1)
		command_line_input(); //input via command line (interface.c);
	else
	{
		printf("Enter the name of the file with the full Path\n\n");
		scanf("%s", &s);
	}
	if (x == 0)
		fptr = fopen(&s,"r");
	if (x == 2)
		fptr = fopen(&s,"rb");
	return(1);
}

int main(int argc, char **argv)
{
	t_interval	*interval;

	reading();
	return(1);
}
