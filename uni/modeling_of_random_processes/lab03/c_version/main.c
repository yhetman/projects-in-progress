/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   main.c                                                                   */
/*                                                                            */
/*   By: yhetman <yhetman@student.unit.ua>                                    */
/*                                                                            */
/*   Created: 2021/02/15 15:23:58 by yhetman                                  */
/*   Updated: 2021/02/26 14:53:41 by yhetman                                  */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/fractal.h"


static void		check_argv34(char *argv[], t_env *e)
{
	long double x,
				y;

	char		*ptr;
	
	x = 0;
	y = 0;
	srand48(time(NULL)*time(NULL));
	if (argv[3] != NULL)
		x = strtod(argv[3], &ptr); 
	if (argv[4] != NULL)
		y = strtod(argv[4], &ptr); 
	if (x == 0 || x > 1.0 || x < -1.0) // || e->c_re == 0.0)	
		e->c_re = -1 + 2 * drand48();
	else
		e->c_re = x;
	if (y == 0 || y > 1.0 || y < -1.0) // || e->c_im == 0.0 )
		e->c_im = 1 - 2 * drand48();
	else
		e->c_im = y;
}

static void 	parse_command_line(char *argv[], t_env *e)
{
	int 		color,
				iterations;

	color = ft_atoi(argv[1]);
	check_argv34(argv, e);	
	if (argv[2] != NULL)
		iterations = ft_atoi(argv[2]);
	else
		iterations = 3000;

	if (color >= 0 && color <= 4)
		e->choose_color = color;
	else
		e->choose_color = 1;
	if (iterations <= 5000 && iterations > 100)
		e->infinity = iterations;
	else
		e->infinity = 3000;
	printf("x = %Le\ny= %Le\niterations=%f\n", e->c_re, e->c_im, e->infinity);
}

int				main(int argc, char *argv[])
{
	t_env	*e;

	if (argc == 1)
	{
		printf("Usage:\n\t./fractal {color_pallette=int(0,4)} {iterations=int} {x=float} {y=float}\n");
		return (0);
	}
	if (!(e = malloc(sizeof(t_env))))
		return (0);
	if (init_mlx(e) == 0)
		return (0);
	parse_command_line(argv, e);
	init(e);
	foreach_pixel(e);
	next_draw(e);
	mlx_loop(e->mlx_ptr);
	return (0);
}
