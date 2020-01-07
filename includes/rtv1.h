/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hezzahir <hamza.ezzahiry@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/27 07:08:51 by hhamdaou          #+#    #+#             */
/*   Updated: 2020/01/06 00:21:44 by hezzahir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
#define RTV1_H
# include "../libft/libft.h"
# include "mlx.h"
# include <stdio.h>
# include <math.h>
# define WIN_WIDTH 1024
# define WIN_HEIGHT 1024

typedef struct	s_img
{
	void *img_ptr;
	unsigned char *data;
	int size_l;
	int bpp;
	int endian;
}				t_img;

typedef struct	s_mlx
{
	void	*mlx_ptr;
	void	*win;
	t_img	img;
	double	fov;
} 				t_mlx;

typedef struct	s_vect
{
	double	x;
	double	y;
	double	z;
} 				t_vect;

typedef struct	s_ray
{
	t_vect origin;
	t_vect dir;
} 				t_ray;

typedef struct	s_color
{
	int		r;
	int		g;
	int		b;
}				t_color;

typedef struct	s_sphere
{
	t_vect		origin;
	double		radius;
	t_color		color;
}				t_sphere;

typedef struct	s_camera
{
	t_vect		pos;
	t_color		c;
	int			fov;

}				t_camera;

typedef struct	s_shape
{
	void			*shape;
	int				id;
	struct s_shape	*next;
}				t_shape;

typedef struct	s_rtv1
{
	int			fd;
	t_shape		*shape;
	t_camera	cam;
	int			is_okey[3];
}				t_rtv1;

/*
** VECTOR
*/
void			vector_generate(t_vect *v1, double x, double y, double z);
double			vector_scalar(t_vect v1, t_vect v2);
double			vector_snorme(t_vect v1);
void			vector_normalize(t_vect *v1);
t_vect			vector_sum(t_vect v1, t_vect v2);
t_vect			vector_sub(t_vect v1, t_vect v2);
t_vect			vector_multi(t_vect v1, double a);
t_vect			vector_div(t_vect v1, double a);

/*
** check argument
*/
void			show_usage(void);
void			check_ac(int ac);

/*
** Parsing functions
*/
int    			parse(t_rtv1 *r, char *s);
void			init_tab(char *tab);
t_vect			get_vect_from_str(char *str);
t_color			get_color_from_str(char *str);
void			set_camera(char **words, t_rtv1 *r);
int				ft_count_words(const char *s, char c);
void			set_sphere(char **words, t_rtv1  *r);
void			ft_error(int id);
/*
** destroy leaks functions
*/

void			make_free(char **words);

#endif
