/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   lab02_2.c                                                                */
/*                                                                            */
/*   By: yhetman <yhetman@student.unit.ua>                                    */
/*                                                                            */
/*   Created: 2021/02/12 18:41:13 by yhetman                                  */
/*   Updated: 2021/02/12 18:41:14 by yhetman                                  */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
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
					i;
	double			*rand_vars;
	float			H_array[5];
	int				A_frequency,
					frequency[4];
	float			p[4] = {0.5, 0.25, 0.125, 0.125},
					p_A_H[4] = {0.333, 0.25, 0.333, 0.5};


	bzero((void*)frequency, sizeof(int) * 4);
	bzero((void*)H_array, sizeof(float) * 5);
	H_array[0] = 0;
	for (i = 1; i < 5; i++)
		H_array[i] = H_array[i - 1] + p[i - 1];
	amount = atoi(argv[1]);
	rand_vars = multicong_generator(amount);
	for (j = 0; j < amount; j++)
    	for (i = 0; i < 5; i++)
    		if (rand_vars[j] > H_array[i] && rand_vars[j] < H_array[i + 1 ])
    			frequency[i] += 1;
    printf("H_1 = %d\n", frequency[0]);
   	printf("H_2 = %d\n", frequency[1]);
   	printf("H_3 = %d\n", frequency[2]);
   	printf("H_4 = %d\n", frequency[3]);
    printf("Probability_1 = %f\n", (float)frequency[0] / amount);
   	printf("Probability_2 = %f\n", (float)frequency[1] / amount) ;
   	printf("Probability_3 = %f\n", (float)frequency[2] / amount);
   	printf("Probability_4 = %f\n", (float)frequency[3] / amount);
   	A_frequency = 0;
	for (j = 0; j < amount; j++)
    	for (i = 0; i < 5; i++)
    		if (rand_vars[j] > H_array[i] && rand_vars[j] < H_array[i + 1 ])
    			if (rand_vars[j] < (H_array[i] + p_A_H[i] * p[i]))
    				A_frequency += 1;
	printf("Reletive frequency of event A = %d\t%f\n", A_frequency ,(float)A_frequency/amount);
	free(rand_vars);
	return (0);
}

