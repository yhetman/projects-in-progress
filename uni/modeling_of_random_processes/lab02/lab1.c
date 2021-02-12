/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   lab1.c                                                                   */
/*                                                                            */
/*   By: yhetman <yhetman@student.unit.ua>                                    */
/*                                                                            */
/*   Created: 2021/01/30 19:38:46 by yhetman                                  */
/*   Updated: 2021/02/02 01:54:00 by yhetman                                  */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


double *multicong(int amount)
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


int			find_minimum(double *a, int n)
{
	int		c,
			index;
	
	index = 0;
	for (c = 1; c < n; c++)
		if (a[c] < a[index])
			index = c;
	return index;
}


int			find_maximum(double *a, int n)
{
	int		c,
			index;
	
	index = 0;
	for (c = 1; c < n; c++)
		if (a[c] > a[index])
			index = c;
	return index;
}

typedef struct	s_dictionary
{
	double		key;
	double			value;
}				t_dictionary;

void dictionaries(double minimal, int steps, double H, double *bvv, int n)
{
	t_dictionary	*dictionary1,
					*dictionary2;
	int				i, j;
	double			phi;
	
	dictionary1 = (t_dictionary*)malloc(sizeof(t_dictionary) * steps);
	dictionary2 = (t_dictionary*)malloc(sizeof(t_dictionary) * steps);
	phi = 0;
	for (i = 0; i < steps; i++)
	{
		dictionary1[i].key = minimal + H * i;
		dictionary1[i].value = 0;
		dictionary2[i].key = minimal + H * i;
		dictionary2[i].value = 0;
	}

	for (i = 0; i < n; i++ )
	{
		for (j = 0; j < steps; j++)
		{
			if (bvv[i] > dictionary1[j].key && bvv[i] < (dictionary1[j].key + H))
			{
				dictionary1[j].value += 1;
				dictionary2[j].value += bvv[i] - dictionary1[j].key + minimal;
			}
		}
	}
	for (i = 0; i < steps ; i++)
	{
		phi += pow((dictionary1[i].value - n / steps), 2) / (n / steps);
//		printf("|%d|%.9f|\n",i, (double)(dictionary2[i].value / dictionary1[i].value));
	}
//	printf("Phi = %.9f\n", phi);
}

int main()
{
	int				amount,
					i,
					min,
					max,
					number_of_intervals;
	double			H,
					*rand_vars;

	i = 0;
	amount = 10000;
	rand_vars = multicong(amount);
	number_of_intervals = (int)(1 + log2(amount));
	while(i++ < amount)
		printf("%.9f\n", rand_vars[i]);
//	printf("Number of intervals : %d\n",number_of_intervals);
	min = find_minimum(rand_vars, amount);
//	printf("Minimal value : %.9f\n", rand_vars[min]);
	max = find_maximum(rand_vars, amount);
//	printf("Maximal value : %.9f\n",rand_vars[max]);
	H = (rand_vars[max] - rand_vars[min]) / number_of_intervals;
	dictionaries(rand_vars[min], number_of_intervals, H, rand_vars, amount);
	free(rand_vars);
	return (0);
}

