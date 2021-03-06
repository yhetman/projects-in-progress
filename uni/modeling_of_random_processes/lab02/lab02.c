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
	M = 10000;
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
					j,
					alpha;
	double			*rand_vars;
	time_t			seconds;
	float			probability,
					p;


	if (argc < 3)
	{
		printf("Usage:\n\n./lab02 {Number of elements to generate} {Probability to apply}\n");
		exit(1);
	}
	alpha = 0;
	amount = atoi(argv[1]);
	p = atof(argv[2]);
	probability = 0;
	rand_vars = multicong_generator(amount);
    for (j = 0;j < 1000000; j++)
    {
    	time(&seconds);
    	alpha = (int)seconds % amount;
    	// printf("%d\n",alpha);
    	if (rand_vars[alpha] < p)
    		probability += 1;
    }
    probability /= 10000000;
    printf("%s : %0.8f\n", "Relative frequency of Event  A", probability);
	free(rand_vars);
	return (0);
}

