#include "../headers/interval.h"


int			define_type(t_interval *c)
{	
	if (c->left && c->right && c->a == c->b)
		c->type = 2;
	if (c->left && c->right)
		c->type = 4;
	if (!c->left && !c->right && c->a == c->b)
		c->type = 1;
	if (!c->left && !c->right)
		c->type = 3;
	if (c->left && !c->right)
		c->type = 5;
	if (!c->left && c->right)
		c->type = 6;
	if (c->a == -INFINITY && c->b != INFINITY)
		c->type = 7;
	if (c->a != -INFINITY && c->b == INFINITY)
		c->type = 8;
	if (c->a == -INFINITY && c->b == INFINITY)
		c->type = 9;
	return (c->type);
}

t_set_interval	*union_of_intervals(t_interval *a, t_interval *b)
{
	t_interval *c;
	t_set_interval *united;

	united = (t_set_interval*)malloc(sizeof(t_set_interval));
	united->next = NULL;
	if (a->type == 1 && b->type == 1)
		united->first = empty_int_declaration();
	else if (a->type == 1)
		united->first = a;
	else if (b->type == 1)
		united->first = b;
	else
	{
		if (!(c = (t_interval*)malloc(sizeof(t_interval))))
			mal_error();
		if (a->b >= b->b)
		{
			c->a = MIN(a->a, b->a);
			c->b = MAX(a->b, b->b);
			(((a->a < b->a && a->left) || (a->a > b->a && b->left)) ? 	(c->left = true) : (c->left = false));
			(((a->b < b->b && b->right) || (a->b > b->b && a->right)) ? 	(c->right = true) : (c->right = false));
			c->type = define_type(c);
			united->first = c;
			united->next = NULL;
		}
		else
		{
			united->first = a;
			united->first->type = define_type(a);
			united->next = (t_set_interval*)malloc(sizeof(t_set_interval));
			united->next->first = b;
			united->next->first->type = define_type(b);
			united->next->next = NULL;
		}
	}
	return (united); 
}
