#include "../headers/interval.h"

t_interval		*set_borders(t_interval *a) // defines some borders of the intervals;
{
	a->left = false;
	a->right = false;
	if (a->type == 4 || a->type == 5)
		a->left = true;
	if (a->type == 4 || a->type == 6)
		a->right = true;
	return(a);
}

t_interval		*empty_int_declaration(void) // declares Interval as an empty one;
{
	t_interval	*empty;

	if (!(empty = (t_interval*)malloc(sizeof(t_interval))))
		mal_error();
	empty->a = NAN;
	empty->b = NAN;
	empty->type = 1;
	empty->left = false;
	empty->right = false;
	return(empty);
}

t_interval		*single_point_declaration(void) // defines an interval with the single point
{
	t_interval	*point;

	if (!(point = (t_interval*)malloc(sizeof(t_interval))))
		mal_error(); //error_managemetn.c
	printf("\033[1;34mDefine the point\033[0m\n\n");
	scanf("%lf",&point->a);
	point->b = point->a;
	point->type = only_point;
	point->left = true;
	point->right = true;
	return(point);
}

t_interval	*infinity_interval(int type) // defines an Interval that has one INFINITY border;
{
	t_interval	*interval;

	if (!(interval = (t_interval*)malloc(sizeof(t_interval))))
		mal_error();
	interval->a = -INFINITY;
	interval->b = INFINITY;
	interval->type = type;
	if (interval->type == endless_left)
	{
		printf("\033[1;34mNow define the right side of the Interval\033[0m\n\n");
		scanf("%lf",&interval->b);
	}
	if (interval->type == endless_right)
	{
		printf("\033[1;34mNow define the left side of the Interval\033[0m\n\n");
		scanf("%lf",&interval->a);
	}
	return(interval);
}

t_interval		*initialize_interval(void) // defines what kind of interval user'd like to use
{
	int	type;

	if (!(type = define_interval_type(type))) //catch value of type
		return (NULL);
	if (type == 1)
		return (empty_int_declaration()); 
	else if (type == 2)
		return (single_point_declaration());
	else if (type >= 3 && type <= 6)
		return (interval_declaration(type));
	else if (type >= 7 && type <= 9)
		return (infinity_interval(type));
	else
		return (NULL);
}
