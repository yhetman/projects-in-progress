/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   init_structs.c                                                           */
/*                                                                            */
/*   By: yhetman <yhetman@student.unit.ua>                                    */
/*                                                                            */
/*   Created: 2021/02/15 15:29:16 by yhetman                                  */
/*   Updated: 2021/02/15 15:29:20 by yhetman                                  */
/*                                                                            */
/* ************************************************************************** */


#include "./includes/fractal.h"
#include <time.h>

int			init_mlx(t_env *e)
{
	if ((e->mlx_ptr = mlx_init()) == NULL)
		return (0);
	if ((e->win_ptr = mlx_new_window(e->mlx_ptr, WIDTH, HEIGHT,
		"hello, fractal")) == NULL)
		return (0);
	if ((e->image_ptr = mlx_new_image(e->mlx_ptr, WIDTH, HEIGHT)) == NULL)
		return (0);
	if ((e->image = mlx_get_data_addr(e->image_ptr,
	&e->bpp, &e->ln, &e->en)) == NULL)
		return (0);
	e->bpp /= 8;
	return (1);
}


void			init(t_env *e)
{
	e->function = julia_math;
	srand48(time(NULL)*time(NULL));
	e->c_re = -1 + 2 * drand48(); //-0.70176f;
	e->c_im = 1 - 2 * drand48(); //-0.3842f;
	e->min_x = -1.5f;
	e->max_x = 1.5f;
	e->min_y = -1.0f;
	e->max_y = 1.0f;
	e->infinity = 3000;
}


t_map		init_map(long double a, long double b,
						long double c, long double d)
{
	t_map map;

	map.a = a;
	map.b = b;
	map.c = c;
	map.d = d;
	return (map);
}

