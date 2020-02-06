/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_equation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hezzahir <hamza.ezzahiry@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 09:30:07 by hezzahir          #+#    #+#             */
/*   Updated: 2020/02/06 23:24:21 by hezzahir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double		solve_sphere(t_sphere *sphere, t_ray ray)
{
	t_equation	e;

	e.b = 2 * vector_scalar(ray.dir, vector_sub(ray.origin, sphere->origin));
	e.c = vector_snorme(vector_sub(ray.origin, sphere->origin))
				- sphere->radius * sphere->radius;
	e.delta = e.b * e.b - 4 * e.c;
	if (e.delta < 0)
		return (0);
	e.s1 = (-e.b - sqrt(e.delta)) / 2;
	e.s2 = (-e.b + sqrt(e.delta)) / 2;
	if (e.s2 < 0 && e.s1 < 0)
		return (0);
	return (fmin(e.s1, e.s2));
}

double		solve_cylindre(t_cylindre *cy, t_ray ray)
{
	t_equation		e;
	t_vect			x;

	x = vector_sub(ray.origin, cy->origin);
	e.a = vector_scalar(ray.dir, ray.dir) -
				ft_sqrs(vector_scalar(ray.dir, cy->axis));
	e.b = vector_scalar(ray.dir, x) -
			((vector_scalar(ray.dir, cy->axis)) * (vector_scalar(x, cy->axis)));
	e.b *= 2.0;
	e.c = vector_scalar(x, x) -
				ft_sqrs(vector_scalar(x, cy->axis)) - ft_sqrs(cy->radius);
	e.delta = e.b * e.b - (4 * e.a * e.c);
	if (e.delta < 0)
		return (0);
	e.s1 = (-e.b - sqrt(e.delta)) / (2 * e.a);
	e.s2 = (-e.b + sqrt(e.delta)) / (2 * e.a);
	if (e.s2 < 0 && e.s1 < 0)
		return (0);
	if (e.s1 < 0 && e.s2 > 0)
		return (e.s2);
	if (e.s2 < 0 && e.s1 > 0)
		return (e.s1);
	return (fmin(e.s1, e.s2));
}

double		solve_plane(t_plane *pl, t_ray ray)
{
	t_equation	e;
	t_vect		x;

	e.a = vector_scalar(ray.dir, pl->norm);
	if (e.a == 0)
		return (0);
	x = vector_sub(ray.origin, pl->origin);
	e.b = vector_scalar(x, pl->norm);
	e.s1 = -e.b / e.a;
	if (e.s1 < 0)
		return (0);
	return (e.s1);
}

double		solve_cone(t_cone *cone, t_ray ray)
{
	t_equation	e;
	t_vect		x;
	double		k;

	k = tan(cone->radius / 180.0 * M_PI);
	x = vector_sub(ray.origin, cone->origin);
	e.a = vector_scalar(ray.dir, ray.dir) - ((1 + ft_sqrs(k))
			* ft_sqrs(vector_scalar(ray.dir, cone->axis)));
	e.b = 2.0 * (vector_scalar(ray.dir, x) - (1 + ft_sqrs(k))
		* vector_scalar(ray.dir, cone->axis) * vector_scalar(x, cone->axis));
	e.c = vector_scalar(x, x) - ((1 + ft_sqrs(k))
				* ft_sqrs(vector_scalar(x, cone->axis)));
	e.delta = e.b * e.b - (4 * e.a * e.c);
	if (e.delta < 0)
		return (0);
	e.s1 = (-e.b - sqrt(e.delta)) / (2 * e.a);
	e.s2 = (-e.b + sqrt(e.delta)) / (2 * e.a);
	if (e.s2 < 0 && e.s1 < 0)
		return (0);
	return (fmin(e.s1, e.s2));
}
