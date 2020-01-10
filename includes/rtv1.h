/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hezzahir <hezzahir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/27 07:08:51 by hhamdaou          #+#    #+#             */
/*   Updated: 2020/01/10 10:34:57 by hezzahir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H
# include "../libft/libft.h"
# include "mlx.h"
# include <stdio.h>
# include <math.h>
# define WIN_WIDTH 1024
# define WIN_HEIGHT 1024

typedef struct	s_img
{
	void			*img_ptr;
	unsigned char	*data;
	int				size_l;
	int				bpp;
	int				endian;
}				t_img;

typedef struct	s_mlx
{
	void	*mlx_ptr;
	void	*win;
	t_img	img;
	double	fov;
}				t_mlx;

typedef struct	s_vect
{
	double	x;
	double	y;
	double	z;
}				t_vect;

typedef struct	s_ray
{
	t_vect origin;
	t_vect dir;
}				t_ray;

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
	t_vect		rot;
	t_vect		tran;
}				t_sphere;

typedef struct	s_plane
{
	t_vect		origin;
	t_color		color;
	t_vect		rot;
	t_vect		tran;
}				t_plane;

typedef struct	s_camera
{
	t_vect		pos;
	t_vect		lookat;
	int			fov;
}				t_camera;

typedef struct	s_shape
{
	void			*shape;
	int				id;
	struct s_shape	*next;
}				t_shape;

typedef struct	s_light
{
	t_vect			origin;
	double			intensity;
	t_color			color;
}				t_light;

typedef struct	s_cone
{
	t_vect			origin;
	double			radius;
	t_color			color;
	t_vect			rot;
	t_vect			tran;
}				t_cone;

typedef struct	s_cylindre
{
	t_vect			origin;
	double			radius;
	double			height;
	t_color			color;
	t_vect			rot;
	t_vect			tran;
}				t_cylindre;

typedef struct	s_rtv1
{
	int			fd;
	t_shape		*shape;
	t_camera	cam;
	t_light		light;
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
int				parse(t_rtv1 *r, char *s);
void			set_camera(char **words, t_rtv1 *r);
void			set_light(char **words, t_rtv1 *r);
void			set_sphere(char **words, t_rtv1 *r);
void			set_cylindre(char **words, t_rtv1 *r);
void			set_plane(char **words, t_rtv1 *r);
void			set_cone(char **words, t_rtv1 *r);
void			init_tab(char *tab);
t_vect			get_vect_from_str(char *str);
t_color			get_color_from_str(char *str);

int				ft_count_words(const char *s, char c);

void			ft_error(int id);
int				count(char **words);
/*
** destroy leaks functions
*/

void			make_free(char **words);

#endif
