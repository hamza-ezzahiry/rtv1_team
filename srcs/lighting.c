/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hezzahir <hamza.ezzahiry@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 15:15:25 by hhamdaou          #+#    #+#             */
/*   Updated: 2020/02/06 19:10:37 by hezzahir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vect		ft_ambient(void)
{
	t_vect ambient;
	double ambient_str;

	ambient_str = 0.2;
	ambient.x = ambient_str;
	ambient.y = ambient_str;
	ambient.z = ambient_str;
	return (ambient);
}

t_vect		ft_diffuse(t_light light, t_intersection inter)
{
	t_vect diffuse;
	double power;

	power = vector_scalar(inter.normal, light.dir);
	diffuse.x = fmax(0, power) * light.intensity;
	diffuse.y = fmax(0, power) * light.intensity;
	diffuse.z = fmax(0, power) * light.intensity;
	return (diffuse);
}

t_vect		ft_specular(t_rtv1 r, t_light light, t_intersection inter)
{
	t_vect specular;
	t_vect view;
	double spec_str;
	double str;
	t_vect reflect;

	if (light.intensity)
		spec_str = 0.5;
	else
		spec_str = 0;
	view = vector_sub(r.cam.pos, inter.p_inter);
	vector_normalize(&view);
	light.dir = vector_multi(light.dir, -1);
	reflect = vector_sub(light.dir, vector_multi(inter.normal,
				2 * vector_scalar(inter.normal, light.dir)));
	str = pow(fmax(vector_scalar(view, reflect), 0.), 255);
	specular.x = str * spec_str * light.color.r;
	specular.y = str * spec_str * light.color.g;
	specular.z = str * spec_str * light.color.b;
	return (specular);
}

t_lighting	pixel_lighting(t_rtv1 r, t_intersection inter)
{
	t_lighting	res;
	t_light		*head;

	head = r.light;
	res.ambient = (t_vect){0, 0, 0};
	res.diffuse = (t_vect){0, 0, 0};
	res.specular = (t_vect){0, 0, 0};
	while (head)
	{
		head->dir = vector_sub(head->origin, inter.p_inter);
		vector_normalize(&head->dir);
		res.ambient = vector_sum(res.ambient, ft_ambient());
		res.diffuse = vector_sum(res.diffuse, ft_diffuse(*head, inter));
		res.specular = vector_sum(res.specular, ft_specular(r, *head, inter));
		head = head->next;
	}
	return (res);
}

int			shadow_light(t_rtv1 r, t_intersection intersect)
{
	t_intersection	*sh_inter;
	t_ray			ray;
	t_light			*head;
	int				count;

	sh_inter = (t_intersection *)malloc(sizeof(t_intersection));
	count = 0;
	head = r.light;
	while (head)
	{
		head->dir = vector_sub(head->origin, intersect.p_inter);
		vector_normalize(&head->dir);
		ray.origin = vector_sum(intersect.p_inter,
				vector_div(intersect.normal, 1E10));
		ray.dir = vector_sub(head->origin, ray.origin);
		vector_normalize(&ray.dir);
		intersection(ray, r.shape, sh_inter);
		if (sh_inter->inter && head->intensity)
			count++;
		head = head->next;
	}
	count += sh_inter->inter;
	free(sh_inter);
	return (count);
}
