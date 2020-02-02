/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hezzahir <hamza.ezzahiry@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/27 07:08:51 by hhamdaou          #+#    #+#             */
/*   Updated: 2020/02/02 11:40:49 by hezzahir         ###   ########.fr       */
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

typedef struct	s_intersection
{
	int		inter;
	t_color	inter_color;
	t_vect	p_inter;
	t_vect	normal;
	double	coord_min;
}				t_intersection;

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
	t_vect		norm;
	t_vect		rot;
	t_vect		tran;
}				t_plane;

typedef struct	s_camera
{
	t_vect		pos;
	t_vect		lookat;
	t_vect		dir;
	t_vect		w;
	t_vect		v;
	t_vect		u;
	double		x;
	double		y;
	double		fov;
	double		height;
	double		width;
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
	t_vect			dir;
	double			intensity;
	t_color			color;
	struct s_light	*next;
}				t_light;

typedef struct	s_cone
{
	t_vect			origin;
	double			radius;
	double			height;
	t_color			color;
	t_vect			axis;
	t_vect			rot;
	t_vect			tran;
}				t_cone;

typedef struct	s_cylindre
{
	t_vect			origin;
	double			radius;
	double			height;
	t_color			color;
	t_vect			axis;
	t_vect			rot;
	t_vect			tran;
}				t_cylindre;

typedef struct	s_equation
{
	double	a;
	double	b;
	double	c;
	double	delta;
	double	s1;
	double	s2;
}				t_equation;

typedef struct	s_lighting
{
	t_vect		ambient;
	t_vect		diffuse;
	t_vect		specular;
}				t_lighting;

typedef struct	s_rtv1
{
	int			fd;
	t_mlx		mlx;
	t_shape		*shape;
	t_camera	cam;
	t_light		*light;
	char		is_okey[3];
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
t_vect			vector_cross(t_vect u, t_vect v);
double			distance(t_vect v1, t_vect v2);
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

/*
** mlx functions
*/

void			init_mlx(t_rtv1 *r, char *str);
int				key_press(int key, t_rtv1 *r);
void			mlx_hooks(t_rtv1 *r);

/*
** maths calcul functions
*/
double			ft_sqrs(double x);
double			ft_deg_to_rad(double angle);

/*
** Rotation/Translation functions
*/

t_vect			trans(t_vect v, t_vect t);
t_vect			rotate(t_vect v, t_vect r);
void			init_cam(t_rtv1 *r);
t_lighting		pixel_lighting(t_rtv1 r, t_intersection inter);
int				shadow_light(t_rtv1 r, t_intersection intersect);
void			intersection(t_ray ray, t_shape *shape,
					t_intersection *intersect);

/*
** Intersection functions
*/

void			intersection(t_ray ray, t_shape *shape,
					t_intersection *intersect);
double			solve_sphere(t_sphere *sphere, t_ray ray);
double			solve_cylindre(t_cylindre *cy, t_ray ray);
double			solve_plane(t_plane *pl, t_ray ray);
double			solve_cone(t_cone *cone, t_ray ray);
void			surface_normal(t_ray ray, t_shape *elem,
											t_intersection *intersect);
void			draw(t_rtv1 *r);
void			sphere_checker(t_rtv1 *r, t_sphere sphere);
void			cylindre_checker(t_rtv1 *r, t_cylindre cylindre);
#endif
