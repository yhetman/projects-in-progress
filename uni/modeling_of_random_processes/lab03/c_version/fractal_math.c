/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   fractal_math.c                                                           */
/*                                                                            */
/*   By: yhetman <yhetman@student.unit.ua>                                    */
/*                                                                            */
/*   Created: 2021/02/15 15:24:20 by yhetman                                  */
/*   Updated: 2021/02/26 15:12:06 by yhetman                                  */
/*                                                                            */
/* ************************************************************************** */



#include "./includes/fractal.h"


long double	ft_map(long double x, t_map map)
{
	long double ret;

	ret = map.c + (map.d - map.c) * ((x - map.a) / (map.b - map.a));
	return (ret);
}



int		julia_math(t_env *e, int x, int y)
{
	long double mx;
	long double my;
	long double x_temp;
	long double stoch;

	e->iteration = 0;
	mx = ft_map(x, init_map(0, WIDTH, e->min_x, e->max_x));
	my = ft_map(y, init_map(0, HEIGHT, e->min_y, e->max_y));
	while (e->iteration < e->infinity)
	{

		srand48(time(NULL));
		stoch = drand48();
		x_temp = (mx * mx - my * my) + e->c_re + stoch;
		my = 2.0f * mx * my + e->c_im + stoch; 
		mx = x_temp;
		if ((mx * mx + my * my) > 4.0f)
			break ;
		e->iteration++;
	}
	return (e->iteration);
}
