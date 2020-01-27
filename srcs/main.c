/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hezzahir <hamza.ezzahiry@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 22:51:13 by hhamdaou          #+#    #+#             */
/*   Updated: 2020/01/26 14:52:16 by hezzahir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int shape_intersection(t_ray ray, t_shape *elem, t_intersection *intersect)
{
	double a;
	double b;
	double c;
	double k;
	double delta;
	double s1;
	double s2;
	double s;
	double m;
	t_cone *cone;
	t_sphere *sphere;
	t_cylindre *cy;
	t_plane *pl;
	t_vect x;

	if (elem->id == 1)
	{
		sphere = (t_sphere *)elem->shape;
		b = 2 * vector_scalar(ray.dir, vector_sub(ray.origin, sphere->origin));
		c = vector_snorme(vector_sub(ray.origin, sphere->origin)) - sphere->radius * sphere->radius;
		delta = b * b - 4 * c;
		if (delta < 0)
			return (0);
		s1 = (-b - sqrt(delta)) / 2;
		s2 = (-b + sqrt(delta)) / 2;
		if (s2 < 0 || s1 < 0)
			return (0);
		intersect->inter = 1;
		s = fmin(s1, s2);
		intersect->coord_min = fmin(intersect->coord_min, s);
		if (s <= intersect->coord_min)
		{
			intersect->p_inter = vector_sum(ray.origin, vector_multi(ray.dir, s));
			intersect->normal = vector_sub(intersect->p_inter, sphere->origin);
			vector_normalize(&intersect->normal);
			intersect->inter_color = (t_color){sphere->color.r, sphere->color.g, sphere->color.b};
		}
		return (1);
	}
	else if (elem->id == 2)
	{
		pl = (t_plane *)elem->shape;
		// printf("%f, %f, %f\n", pl->norm.x, pl->norm.y, pl->norm.z);
		a = vector_scalar(ray.dir, pl->norm);
		if (a == 0)
			return (0);
		x = vector_sub(ray.origin, pl->origin);
		b = vector_scalar(x, pl->norm);
		s = -b / a;
		if (s < 0)
			return (0);
		if (a < 0)
			intersect->normal = vector_multi(pl->norm, -1.0);
		else
			intersect->normal = vector_multi(pl->norm, 1.0);
		vector_normalize(&intersect->normal);
		intersect->inter_color = (t_color){pl->color.r, pl->color.g, pl->color.b};
		intersect->normal = pl->norm;
		return (1);
	}
	else if (elem->id == 3)
	{
		cy = (t_cylindre *)elem->shape;
		x = vector_sub(ray.origin, cy->origin);
		a = vector_scalar(ray.dir, ray.dir) - ft_sqrs(vector_scalar(ray.dir, cy->axis));
		b = vector_scalar(ray.dir, x) - ((vector_scalar(ray.dir, ray.dir)) * (vector_scalar(x, cy->axis)));
		b *= 2.0;
		c = vector_scalar(x, x) - ft_sqrs(vector_scalar(x, cy->axis)) - ft_sqrs(cy->radius);
		delta = b * b - (4 * a * c);
		if (delta < 0)
			return (0);
		s1 = (-b - sqrt(delta)) / (2 * a);
		s2 = (-b + sqrt(delta)) / (2 * a);
		if (s2 < 0 && s1 < 0)
			return (0);
		intersect->inter = 1;
		s = fmin(s1, s2);
		if (s <= intersect->coord_min)
		{
			m = vector_scalar(ray.dir, cy->axis) * s + (vector_scalar(x, cy->axis));
			intersect->p_inter = vector_sum(ray.origin, vector_multi(ray.dir, s));
			intersect->normal = vector_sub(intersect->p_inter, cy->origin);
			intersect->normal = vector_sub(intersect->normal, vector_multi(cy->axis, m));
			vector_normalize(&intersect->normal);
			intersect->inter_color = (t_color){cy->color.r, cy->color.g, cy->color.b};
		}
		return (1);
	}
	else if (elem->id == 4)
	{
		cone = (t_cone *)elem->shape;
		k = tan(cone->radius / 180.0 * M_PI);
		x = vector_sub(ray.origin, cone->origin);
		a = vector_scalar(ray.dir, ray.dir) - ((1 + ft_sqrs(k)) * ft_sqrs(vector_scalar(ray.dir, cone->axis)));
		b = 2.0 * (vector_scalar(ray.dir, x) - (1 + ft_sqrs(k)) * vector_scalar(ray.dir, cone->axis) * vector_scalar(x, cone->axis));
		c = vector_scalar(x, x) - ((1 + ft_sqrs(k)) * ft_sqrs(vector_scalar(x, cone->axis)));
		delta = b * b - (4 * a * c);
		if (delta < 0)
			return (0);
		s1 = (-b - sqrt(delta)) / (2 * a);
		s2 = (-b + sqrt(delta)) / (2 * a);
		if (s2 < 0 && s1 < 0)
			return (0);
		intersect->inter = 1;
		s = fmin(s1, s2);
		if (s <= intersect->coord_min)
		{
			k = tan(ft_deg_to_rad(cone->radius) / 2.0);
			m = vector_scalar(ray.dir, cone->axis) * s + (vector_scalar(x, cone->axis));
			intersect->p_inter = vector_sum(ray.origin, vector_multi(ray.dir, s));
			intersect->normal = vector_sub(intersect->p_inter, cone->origin);
			intersect->normal = vector_sub(intersect->normal, vector_multi(vector_multi(cone->axis, m), (1 + ft_sqrs(k))));
			vector_normalize(&intersect->normal);
			intersect->inter_color = (t_color){cone->color.r, cone->color.g, cone->color.b};
		}
		return (1);
	}
	else
		return (0);
}

void intersection(t_ray ray, t_shape *shape, t_intersection *intersect)
{
	t_shape *head;

	head = shape;
	intersect->inter = 0;
	intersect->coord_min = 1E50;
	while (head)
	{
		shape_intersection(ray, head, intersect);
		head = head->next;
	}
}

void draw(t_rtv1 *r)
{
	t_vect pix_color;
	t_intersection *intersect;
	t_intersection *sh_inter;
	t_ray ray;
	double fact;
	t_vect ambient;
	double ambient_str;
	t_vect diffuse;
	t_vect specular;
	int i;
	int j;

	fact = 0.5;
	ambient_str = 0.2;
	intersect = (t_intersection *)malloc(sizeof(t_intersection));
	sh_inter = (t_intersection *)malloc(sizeof(t_intersection));
	i = 0;
	j = 0;
	while (i < WIN_HEIGHT)
	{
		r->cam.y = -2 * (double)i / (double)WIN_HEIGHT + 1;
		while (j < WIN_WIDTH)
		{
			//vector_generate(&r->cam.dir, j - WIN_WIDTH / 2, i - WIN_HEIGHT / 2, -WIN_WIDTH / (2 * (tan(k / 2))));
			r->cam.x = 2 * (double)j / (double)WIN_WIDTH - 1;
			r->cam.dir = vector_sum(vector_sum(vector_multi(r->cam.v, r->cam.x),
											   vector_multi(r->cam.u, r->cam.y)),
									vector_multi(r->cam.w, r->cam.fov));
			vector_normalize(&r->cam.dir);
			ray.origin = r->cam.pos;
			ray.dir = r->cam.dir;
			intersection(ray, r->shape, intersect);
			r->light.dir = vector_sub(r->light.origin, intersect->p_inter);
			vector_normalize(&r->light.dir);
			if (intersect->inter)
			{
				vector_generate(&ray.origin, intersect->p_inter.x + (fact * intersect->normal.x), intersect->p_inter.y + (fact * intersect->normal.y), intersect->p_inter.z + (fact * intersect->normal.z));
				ray.dir = vector_sub(r->light.origin, ray.origin);
				vector_normalize(&ray.dir);
				intersection(ray, r->shape, sh_inter);
				sh_inter->normal = vector_sub(intersect->p_inter, sh_inter->p_inter);
				/**************AMBIENT************/
				ambient.x = ambient_str;
				ambient.y = ambient_str;
				ambient.z = ambient_str;
				/*********************************/

				/**************DIFFUSE************/
				diffuse.x = fmax(0, vector_scalar(intersect->normal, r->light.dir)) * r->light.intensity;
				diffuse.y = fmax(0, vector_scalar(intersect->normal, r->light.dir)) * r->light.intensity;
				diffuse.z = fmax(0, vector_scalar(intersect->normal, r->light.dir)) * r->light.intensity;
				/*********************************/

				/**************SPECULAR************/
				t_vect view;
				double spec_str = 0.5;
				double str;
				t_vect R;
				view = vector_sub(r->cam.pos, intersect->p_inter);
				vector_normalize(&view);
				r->light.dir = vector_multi(r->light.dir, -1);
				R = vector_sub(r->light.dir, vector_multi(intersect->normal, 2 * vector_scalar(intersect->normal, r->light.dir)));
				str = pow(fmax(vector_scalar(view, R), 0.), 250);
				specular.x = str * spec_str;
				specular.y = str * spec_str;
				specular.z = str * spec_str;
				/**********************************/
				if (sh_inter->inter && r->light.intensity/*&& sh_inter->coord_min * sh_inter->coord_min <= vector_snorme(light.dir)*/ /*&& vector_snorme(sh_inter->normal) < vector_snorme(light.dir)*/)
				{
					// sh_inter->normal = vector_sub(intersect->p_inter, sh_inter->p_inter);
					//if (vector_snorme(sh_inter->normal) < vector_snorme(light.dir))
					pix_color = (t_vect){0, 0, 0};
				}
				else
				{
					pix_color.x = intersect->inter_color.r * (ambient.x + diffuse.x + specular.x);
					pix_color.y = intersect->inter_color.g * (ambient.y + diffuse.y + specular.y);
					pix_color.z = intersect->inter_color.b * (ambient.z + diffuse.z + specular.z);
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

int main(int ac, char **av)
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