/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   lab02.c                                                                  */
/*                                                                            */
/*   By: yhetman <yhetman@student.unit.ua>                                    */
/*                                                                            */
/*   Created: 2021/02/12 17:46:02 by yhetman                                  */
/*   Updated: 2021/02/12 17:46:03 by yhetman                                  */
/*                                                                            */
/* ************************************************************************** */



#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

double *multicong_generator(int amount)
{
	unsigned int	M,
					alpha0,
					beta;
	int				j;
	double			*alpha,
					*rand_vars;

	
	j = 0;
	alpha0 = 8;
	beta = 77;
	M = 10000000;
	alpha = (double *)malloc((amount + 1)* sizeof(double));
	rand_vars = (double *)malloc(amount * sizeof(double));
	alpha[j] = alpha0;
	while (++j < amount + 1)
	{
		alpha[j] = ((int)(alpha[j - 1] * beta) % M);
		rand_vars[j - 1] = (double)(alpha[j - 1] / M);
	}
	free(alpha);
	return (rand_vars);
}

int main(int argc, char **argv)
{
	int				amount,
					alpha,
					min,
					max,
					number_of_intervals;
	double			H,
					*rand_vars;
	time_t			seconds;
	float			probability;


	if (argc < 3)
		printf("Usage: ./lab02 {N - number of elements to generate} {p - probability to apply}\n");
	alpha = 0;
	amount = 10000; // atoi(argv[1])
	p = 1/3; //atoi(argv[2])
	rand_vars = multicong_generator(amount);
    time(&seconds);
    i = (int)seconds % amount;
    if (rand_vars[alpha] < probability)
    	printf("Настання події : 1");
    else 
    	printf("Настання події : 0");
	free(rand_vars);
	return (0);
}

