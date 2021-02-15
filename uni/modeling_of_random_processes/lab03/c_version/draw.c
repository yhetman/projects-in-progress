/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   draw.c                                                                   */
/*                                                                            */
/*   By: yhetman <yhetman@student.unit.ua>                                    */
/*                                                                            */
/*   Created: 2021/02/15 15:30:40 by yhetman                                  */
/*   Updated: 2021/02/15 15:30:42 by yhetman                                  */
/*                                                                            */
/* ************************************************************************** */



#include "./includes/fractal.h"

void		put_pixel_to_img(t_env *e, int x, int y)
{
	if ((x >= 0 || x <= WIDTH) && (y >= 0 || y <= HEIGHT))
	{
		e->image[(x * 4) + (y * WIDTH * 4) + 2] = e->red;
		e->image[(x * 4) + (y * WIDTH * 4) + 1] = e->green;
		e->image[(x * 4) + (y * WIDTH * 4)] = e->blue;
	}
}

void			foreach_pixel(t_env *e)
{
	int x;
	int y;
	int color;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			color = e->function(e, x, y);
			choose_color(e, color);
			put_pixel_to_img(e, x, y);
			x++;
		}
		y++;
	}
}


void			next_draw(t_env *e)
{
	mlx_clear_window(e->mlx_ptr, e->win_ptr);
	foreach_pixel(e);
	mlx_put_image_to_window(e->mlx_ptr, e->win_ptr, e->image_ptr, 0, 0);
}

