/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   main.c                                                                   */
/*                                                                            */
/*   By: yhetman <yhetman@student.unit.ua>                                    */
/*                                                                            */
/*   Created: 2021/02/15 15:23:58 by yhetman                                  */
/*   Updated: 2021/02/15 15:24:01 by yhetman                                  */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/fractal.h"


static void parse_command_line(char *argv[], t_env *e)
{
	int 	color;

	color = ft_atoi(argv[1]);
	if (color > 0 && color < 4)
		e->choose_color = color;
	else
		e->choose_color = 1;
}

int				main(int argc, char *argv[])
{
	t_env	*e;

	if (!(e = malloc(sizeof(t_env))))
		return (0);
	if (init_mlx(e) == 0)
		return (0);
	if (argc > 1)
		parse_command_line(argv, e);
	init(e);
	foreach_pixel(e);
	next_draw(e);
	mlx_loop(e->mlx_ptr);
	return (0);
}
