/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hezzahir <hamza.ezzahiry@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 22:51:13 by hhamdaou          #+#    #+#             */
/*   Updated: 2020/02/02 11:33:53 by hezzahir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double	shape_intersection(t_ray ray, t_shape *elem)
{
	double s;

	s = 0;
	if (elem->id == 1)
		s = solve_sphere((t_sphere *)elem->shape, ray);
	else if (elem->id == 2)
		s = solve_plane((t_plane *)elem->shape, ray);
	else if (elem->id == 3)
		s = solve_cylindre((t_cylindre *)elem->shape, ray);
	else if (elem->id == 4)
		s = solve_cone((t_cone *)elem->shape, ray);
	return (s);
}

void	intersection(t_ray ray, t_shape *shape, t_intersection *intersect)
{
	double	s;
	t_shape	*head;
	t_shape	*closer;

	head = shape;
	closer = shape;
	intersect->inter = 0;
	intersect->coord_min = 1E50;
	while (head)
	{
		s = shape_intersection(ray, head);
		if (s)
		{
			intersect->inter += 1;
			if (s <= intersect->coord_min)
			{
				intersect->coord_min = s;
				closer = head;
			}
		}
		head = head->next;
	}
	surface_normal(ray, closer, intersect);
}

void	light_off(t_rtv1 *r)
{
	t_shape *shape;

	shape = r->shape;
	while (shape)
	{
		if (shape->id == 1)
			sphere_checker(r, *(t_sphere *)shape->shape);
		if (shape->id == 2)
			cylindre_checker(r, *(t_cylindre *)shape->shape);
		shape = shape->next;
	}
}

int		main(int ac, char **av)
{
	t_rtv1 r;

	r.shape = NULL;
	check_ac(ac);
	if (parse(&r, av[1]) < 0)
	{
		ft_putendl("scene not correct");
		return (0);
	}
	init_mlx(&r, "rtv1");
	init_cam(&r);
	light_off(&r);
	draw(&r);
	mlx_hooks(&r);
	return (0);
}
