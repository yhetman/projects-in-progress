/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   color_palettes.c                                                         */
/*                                                                            */
/*   By: yhetman <yhetman@student.unit.ua>                                    */
/*                                                                            */
/*   Created: 2021/02/15 15:26:46 by yhetman                                  */
/*   Updated: 2021/02/15 15:26:49 by yhetman                                  */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/fractal.h"

static void		more_colors(t_env *e, int depth)
{
	if (e->choose_color == 2)
	{
		e->red = (SQR(depth) * 30) % 255;
		e->blue = (SQR(depth) * 80) % 255;
		e->green = (depth * 40) % 255;
	}
	else if (e->choose_color == 3)
	{
		e->red = (depth * 5) % 255;
		e->blue = (depth * 5) % 255;
		e->green = (depth * 5) % 255;
	}
}

void			choose_color(t_env *e, int depth)
{
	if (e->choose_color == 0)
	{
		if (depth == e->infinity)
		{
			e->red = 0;
			e->blue = 0;
			e->green = 0;
		}
		else
		{
			e->red = (depth * 3) % 255;
			e->blue = (depth * 7) % 255;
			e->green = (depth * 4) % 255;
		}
	}
	else if (e->choose_color == 1)
	{
		e->red = (depth * 7) % 255;
		e->blue = (depth * 2) % 70;
		e->green = (depth * 3) % 4;
		
	}
	else
		more_colors(e, depth);
}

