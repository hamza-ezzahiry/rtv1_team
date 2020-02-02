/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamdaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 01:19:34 by hhamdaou          #+#    #+#             */
/*   Updated: 2020/02/01 15:59:08 by hhamdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vect	pixel_color(t_intersection inter, t_lighting pix_light)
{
	t_vect pixel;

	pixel.x = inter.inter_color.r *
		(pix_light.ambient.x +
		pix_light.diffuse.x +
		pix_light.specular.x);
	pixel.y = inter.inter_color.g *
		(pix_light.ambient.y +
		pix_light.diffuse.y +
		pix_light.specular.y);
	pixel.z = inter.inter_color.b *
		(pix_light.ambient.z +
		pix_light.diffuse.z +
		pix_light.specular.z);
	return (pixel);
}

t_vect	light_shadow(t_rtv1 *r, t_intersection *intersect,
		t_vect pixel, t_lighting pix_light)
{
	int		shadow;
	t_vect	pix_color;

	shadow = shadow_light(*r, *intersect);
	if (shadow)
	{
		pixel.x = intersect->inter_color.r *
			(pix_light.ambient.x);
		pixel.y = intersect->inter_color.g *
			(pix_light.ambient.y);
		pixel.z = intersect->inter_color.b *
			(pix_light.ambient.z);
		pix_color = (t_vect){
			(pixel.x - pixel.x / 10. * (double)shadow),
			(pixel.y - pixel.y / 10. * (double)shadow),
			(pixel.z - pixel.z / 10. * (double)shadow)};
	}
	else
		pix_color = pixel;
	return (pix_color);
}

void	color(t_rtv1 *r, t_ray *ray, int i, int j)
{
	t_intersection	*intersect;
	t_lighting		pix_light;
	t_vect			pix_color;
	int				pos;

	pos = 4 * (WIN_WIDTH * i + j);
	intersect = (t_intersection *)malloc(sizeof(t_intersection));
	intersection(*ray, r->shape, intersect);
	if (intersect->inter)
	{
		pix_light = pixel_lighting(*r, *intersect);
		pix_color = pixel_color(*intersect, pix_light);
		pix_color = light_shadow(r, intersect, pix_color, pix_light);
		r->mlx.img.data[pos + 0] = fmin(255., fmax(pix_color.z, 0.));
		r->mlx.img.data[pos + 1] = fmin(255., fmax(pix_color.y, 0.));
		r->mlx.img.data[pos + 2] = fmin(255., fmax(pix_color.x, 0.));
	}
	free(intersect);
}

void	draw(t_rtv1 *r)
{
	t_ray	ray;
	int		i;
	int		j;

	i = 0;
	while (i < WIN_HEIGHT)
	{
		j = 0;
		r->cam.y = -2 * (double)i / (double)WIN_HEIGHT + 1;
		while (j < WIN_WIDTH)
		{
			r->cam.x = 2 * (double)j / (double)WIN_WIDTH - 1;
			r->cam.dir = vector_sum(
					vector_sum(
						vector_multi(r->cam.v, r->cam.x * r->cam.width),
						vector_multi(r->cam.u, r->cam.y * r->cam.height)),
					r->cam.w);
			vector_normalize(&r->cam.dir);
			ray.origin = r->cam.pos;
			ray.dir = r->cam.dir;
			color(r, &ray, i, j);
			j++;
		}
		i++;
	}
}
