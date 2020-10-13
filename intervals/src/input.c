
#include "../headers/interval.h"

int		define_interval_type(int type) // outputs the varients of the intervals to use;
{
	type = 0;
	printf("\033[01;33mChoose the type of the interval:\n\n");
	printf("\tto choose an empty interval\t\t\tpress 1;");
	printf("\n\n\tto choose a single-point interval\t\tpress 2;");
	printf("\n\n\tto choose an opened interval\t\t\tpress 3;");
	printf("\n\n\tto choose a closed interval\t\t\tpress 4;");
	printf("\n\n\tto choose a half-closed left interval\t\tpress 5;");
	printf("\n\n\tto choose a half-closed right interval\t\tpress 6;");
	printf("\n\n\tto choose an endless left interval\t\tpress 7;");
	printf("\n\n\tto choose an endless right interval\t\tpress 8;");
	printf("\n\n\tto choose an endless interval from both sides\tpress 9.\033[0m\n");
	scanf("%d", &type);
	if (type < 1 || type > 9)
		return (0);
	return(type);
}

t_interval	*interval_declaration(int type) // simple interface to input the values;
{
	t_interval  *interval;

	if (!(interval = (t_interval*)malloc(sizeof(t_interval))))
		mal_error();
	printf("\033[1;34mNow input the values of the Interval (take in a count that a < b)\n\n");
	printf("Define the first value a:\033[0m\n\n");
	scanf("%lf",&interval->a);
	printf("\033[1;34mDefine the second value b:\033[0m\n\n");
	scanf("%lf",&interval->b);
	if (interval->a > interval->b)
		val_error();
	interval->type = type;
	return(set_borders(interval));
}
