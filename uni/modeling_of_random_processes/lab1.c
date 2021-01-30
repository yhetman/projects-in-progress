/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   lab1.c                                                                   */
/*                                                                            */
/*   By: yhetman <yhetman@student.unit.ua>                                    */
/*                                                                            */
/*   Created: 2021/01/30 19:38:46 by yhetman                                  */
/*   Updated: 2021/01/30 20:09:41 by yhetman                                  */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

double *multicong(unsigned int alpha, unsigned int M, unsigned int beta , double *randomNums, int amount)
{
	int j;
	
	j = 0;
	randomNums[j] = alpha;
	while (++j < amount)
		randomNums[j] = (double)((int)(randomNums[j - 1] * beta) % M) / M;
	return (randomNums);
}

int main()
{
	unsigned int	M, alpha, beta;
	int				amount,
					i;
	double			*randomNums;


	i = 0;
	alpha = 80;
	beta = 9;
	M = 1000000;
	amount = 100000;
	randomNums = (double *)malloc(amount * sizeof(double));
	while (i++ < amount)
		randomNums = multicong(alpha, M, beta, randomNums, amount);
	i = 0;
	while(i++ < amount)
		printf("|%d|%f|\n", i, randomNums[i]);
	free(randomNums);
	return (0);
}

