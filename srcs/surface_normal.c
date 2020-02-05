/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   surface_normal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hezzahir <hamza.ezzahiry@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 13:01:36 by hezzahir          #+#    #+#             */
/*   Updated: 2020/02/05 14:16:10 by hezzahir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	normal_sphere(t_sphere *sphere, t_ray ray, t_intersection *intersect)
{
	intersect->p_inter = vector_sum(ray.origin,
			vector_multi(ray.dir, intersect->coord_min));
	intersect->normal = vector_sub(intersect->p_inter, sphere->origin);
	vector_normalize(&intersect->normal);
	intersect->inter_color = (t_color){sphere->color.r,
							sphere->color.g, sphere->color.b};
}

void	normal_plane(t_plane *pl, t_intersection *intersect)
{
	if (intersect->coord_min < 0)
		intersect->normal = vector_multi(pl->norm, -1.0);
	else
		intersect->normal = vector_multi(pl->norm, 1.0);
	intersect->inter_color = (t_color){pl->color.r, pl->color.g, pl->color.b};
}

void	normal_cylindre(t_cylindre *cy, t_ray ray, t_intersection *intersect)
{
	double	m;
	double	s;
	t_vect	x;

	x = vector_sub(ray.origin, cy->origin);
	s = intersect->coord_min;
	m = vector_scalar(ray.dir, cy->axis) * s + (vector_scalar(x, cy->axis));
	intersect->p_inter = vector_sum(ray.origin, vector_multi(ray.dir, s));
	intersect->normal = vector_sub(intersect->p_inter, cy->origin);
	intersect->normal = vector_sub(intersect->normal,
						vector_multi(cy->axis, m));
	vector_normalize(&intersect->normal);
	intersect->inter_color = (t_color){cy->color.r, cy->color.g, cy->color.b};
}

void	normal_cone(t_cone *cone, t_ray ray, t_intersection *intersect)
{
	double	k;
	double	m;
	double	s;
	t_vect	x;

	s = intersect->coord_min;
	x = vector_sub(ray.origin, cone->origin);
	k = tan(ft_deg_to_rad(cone->radius) / 2.0);
	m = vector_scalar(ray.dir, cone->axis) * s + (vector_scalar(x, cone->axis));
	intersect->p_inter = vector_sum(ray.origin, vector_multi(ray.dir, s));
	intersect->normal = vector_sub(intersect->p_inter, cone->origin);
	intersect->normal = vector_sub(intersect->normal,
				vector_multi(vector_multi(cone->axis, m), (1 + ft_sqrs(k))));
	vector_normalize(&intersect->normal);
	intersect->inter_color = (t_color){cone->color.r,
								cone->color.g, cone->color.b};
}

void	surface_normal(t_ray ray, t_shape *elem, t_intersection *intersect)
{
	if (elem->id == 1)
		normal_sphere((t_sphere *)elem->shape, ray, intersect);
	else if (elem->id == 2)
		normal_plane((t_plane *)elem->shape, intersect);
	else if (elem->id == 3)
		normal_cylindre((t_cylindre *)elem->shape, ray, intersect);
	else if (elem->id == 4)
		normal_cone((t_cone *)elem->shape, ray, intersect);
}
