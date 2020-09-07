#include "../headers/interval.h"

char				*define_ineq(t_inequal_type x)
{
	switch (x)
	{
		case 1:
			return (">");
			break;
		case 2:
			return ("<");
			break;
		case 3:
			return ("=");
			break;
		case 4:
			return ("!=");
			break;
		case 5:
			return (">=");
			break;
		case 6:
			return ("<=");
			break;
	}
}

t_sqr_inequality	*declaretion_of_inequality(void)
{
	t_sqr_inequality	*ineq;

	ineq = (t_sqr_inequality	*)malloc(sizeof(t_sqr_inequality));
	bzero(ineq, sizeof(t_sqr_inequality));
	printf("\033[1;34mYou can input the coefficients of the quadratic inequality and the type of inequality\n");
	printf(" Ax * x + Bx + C \n");
	printf("A =\t");
	scanf("%lf", &ineq->a);
	printf("B =\t");
	scanf("%lf", &ineq->b);
	printf("C =\t");
	scanf("%lf", &ineq->c);
	printf("Enter the type of inequality:\n");
	printf("\t>\tpress 1;\n\t<\tpress 2;\n\t=\tpress 3;\n\t!=\tpress 4;\n\t>=\tpress 5;\n\t<=\tpress 6;\n");
	scanf("%i", &ineq->type);
	printf("THE INEQUALITY IS:\n\t\t%.3lfx * x + %.3lfx + %.3lf %s 0\n",
	ineq->a, ineq->b, ineq->c, define_ineq(ineq->type));
	return (ineq);
}

void				calculation_of_quadratic_inequality(void)
{
	t_sqr_inequality	*ineq;

	ineq = declaretion_of_inequality();
}
