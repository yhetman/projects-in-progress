/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   lab1.c                                                                   */
/*                                                                            */
/*   By: yhetman <yhetman@student.unit.ua>                                    */
/*                                                                            */
/*   Created: 2021/01/30 19:38:46 by yhetman                                  */
/*   Updated: 2021/01/30 19:59:19 by yhetman                                  */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int *multicong(unsigned int alpha, int M, unsigned int beta , int *randomNums, int amount)
{
	int j;
	
	j = 0;
	randomNums[j] = alpha;
	while (++j < amount)
		randomNums[j] = (randomNums[j - 1] * beta) % M;
	return (randomNums);
}

int main()
{
	unsigned int	alpha, beta;
	int				M,
					amount,
					i;
	int				*randomNums;


	i = 0;
	alpha = 80;
	beta = 9;
	M = 1000000;
	amount = 100000;
	randomNums = (int *)malloc(amount * sizeof(int));
	while (i++ < amount)
		randomNums = multicong(alpha, M, beta, randomNums, amount);
	i = 0;
	while(i++ < amount)
		printf("|%d|%d|\n", i, randomNums[i]);
	free(randomNums);
	return (0);
}

