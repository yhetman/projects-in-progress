/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   fractal.h                                                                */
/*                                                                            */
/*   By: yhetman <yhetman@student.unit.ua>                                    */
/*                                                                            */
/*   Created: 2021/02/15 15:26:28 by yhetman                                  */
/*   Updated: 2021/02/15 15:26:31 by yhetman                                  */
/*                                                                            */
/* ************************************************************************** */


#ifndef FRACTAL_H
# define FRACTAL_H
# include <unistd.h>
# include <stdlib.h>
# include <mlx.h>
# include <math.h>
# include <time.h>
# include "../libft/libft.h"

# define WIDTH 		800
# define HEIGHT		600
# define SQR(x) (x * x)
# define JULIA 		"julia_set"

typedef	struct			s_map
{
	long double			a;
	long double			b;
	long double			c;
	long double			d;

}						t_map;


typedef struct			s_env
{
	int					(*function)(struct s_env *e, int x, int y);
	void				*mlx_ptr;
	void				*win_ptr;
	void				*image_ptr;
	char				*image;
	int					bpp;
	int					en;
	int					ln;
	float				infinity;
	long double			c_re;
	long double			c_im;
	long double			min_x;
	long double			max_x;
	long double			min_y;
	long double			max_y;
	int					iteration;
	int					red;
	int					green;
	int					blue;
	int					choose_color;
}						t_env;

/*
 *	
 *		init_struct.c
 *
 */
void					init(t_env *e);
int						init_mlx(t_env *e);
t_map					init_map(long double a, long double b, \
						long double c, long double d);

/*
 *	
 *		fractel_math.c
 *
 */
long double				ft_map(long double x, t_map p);
int						julia_math(t_env *e, int x, int y);

/*
 *	
 *		draw.c
 *
 */
void					foreach_pixel(t_env *e);
void					put_pixel_to_img(t_env *e, int x, int y);
void					next_draw(t_env *e);

/*
 *	
 *		color_palettes.c
 *
 */
void					choose_color(t_env *e, int color);


#endif
