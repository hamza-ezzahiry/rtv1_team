/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hezzahir <hamza.ezzahiry@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 22:51:13 by hhamdaou          #+#    #+#             */
/*   Updated: 2020/01/30 16:24:25 by hezzahir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double	shape_intersection(t_ray ray, t_shape *elem)
{
	double		s;

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

void		intersection(t_ray ray, t_shape *shape, t_intersection *intersect)
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
			intersect->inter = 1;
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

void		draw(t_rtv1 *r)
{
	t_lighting pix_light;
	t_vect pix_color;
	t_intersection *intersect;
	t_ray ray;
	int shadow;
	int i;
	int j;

	intersect = (t_intersection *)malloc(sizeof(t_intersection));

	i = 0;
	j = 0;
	while (i < WIN_HEIGHT)
	{
		r->cam.y = 2 * (double)i / (double)WIN_HEIGHT - 1;
		while (j < WIN_WIDTH)
		{
			//vector_generate(&r->cam.dir, j - WIN_WIDTH / 2, i - WIN_HEIGHT / 2, -WIN_WIDTH / (2 * (tan(k / 2))));
			r->cam.x = 2 * (double)j / (double)WIN_WIDTH - 1;
			r->cam.dir = vector_sum(vector_sum(vector_multi(r->cam.v, r->cam.x * r->cam.width),
											   vector_multi(r->cam.u, r->cam.y * r->cam.height)),
									r->cam.w);
			vector_normalize(&r->cam.dir);
			ray.origin = r->cam.pos;
			ray.dir = r->cam.dir;
			intersection(ray, r->shape, intersect);
			// r->light->dir = vector_sub(r->light->origin, intersect->p_inter);
			// vector_normalize(&r->light->dir);
			if (intersect->inter)
			{
				pix_light = pixel_lighting(*r, *intersect);
				shadow = shadow_light(*r, *intersect);
				// vector_generate(&ray.origin, intersect->p_inter.x + (fact * intersect->normal.x), intersect->p_inter.y + (fact * intersect->normal.y), intersect->p_inter.z + (fact * intersect->normal.z));
				// ray.dir = vector_sub(r->light->origin, ray.origin);
				// vector_normalize(&ray.dir);
				// intersection(ray, r->shape, sh_inter);
				// sh_inter->normal = vector_sub(intersect->p_inter, sh_inter->p_inter);
				t_vect pixel;
				pixel.x = intersect->inter_color.r * (pix_light.ambient.x + pix_light.diffuse.x + pix_light.specular.x);
				pixel.y = intersect->inter_color.g * (pix_light.ambient.y + pix_light.diffuse.y + pix_light.specular.y);
				pixel.z = intersect->inter_color.b * (pix_light.ambient.z + pix_light.diffuse.z + pix_light.specular.z);
				if (shadow /*&& sh_inter->coord_min * sh_inter->coord_min <= vector_snorme(light.dir)*/ /*&& vector_snorme(sh_inter->normal) < vector_snorme(light.dir)*/)
				{
					// sh_inter->normal = vector_sub(intersect->p_inter, sh_inter->p_inter);
					//if (vector_snorme(sh_inter->normal) < vector_snorme(light.dir))
					pix_color = (t_vect){pixel.x - pixel.x / 10. * (double)shadow, pixel.y - pixel.y / 10. * (double)shadow, pixel.z - pixel.z / 10. * (double)shadow};
				}
				else
				{
					pix_color.x = pixel.x;
					pix_color.y = pixel.y;
					pix_color.z = pixel.z;
				}
				r->mlx.img.data[4 * (WIN_WIDTH * (WIN_HEIGHT - i - 1) + j) + 0] = fmin(255., fmax(pix_color.z, 0.)); //blue
				r->mlx.img.data[4 * (WIN_WIDTH * (WIN_HEIGHT - i - 1) + j) + 1] = fmin(255., fmax(pix_color.y, 0.)); //green
				r->mlx.img.data[4 * (WIN_WIDTH * (WIN_HEIGHT - i - 1) + j) + 2] = fmin(255., fmax(pix_color.x, 0.)); //red
			}
			j++;
		}
		i++;
		j = 0;
	}
}

int			main(int ac, char **av)
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
	draw(&r);
	mlx_hooks(&r);
	return (0);
}
