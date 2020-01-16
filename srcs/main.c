/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hezzahir <hezzahir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 22:51:13 by hhamdaou          #+#    #+#             */
/*   Updated: 2020/01/16 17:34:58 by hezzahir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hezzahir <hezzahir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 22:51:13 by hhamdaou          #+#    #+#             */
/*   Updated: 2020/01/16 17:31:55 by hezzahir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int key_press(int key, t_mlx *mlx)
{
	if (key == 53)
	{
		mlx_destroy_image(mlx->mlx_ptr, mlx->img.img_ptr);
		mlx_destroy_window(mlx, mlx->win);
		ft_memdel((void **)&(mlx->mlx_ptr));
		exit(1);
	}
	return (0);
}

void init_mlx(t_mlx *mlx, char *str)
{
	mlx->fov = 60 * M_PI / 180;
	mlx->mlx_ptr = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, str);
	mlx->img.img_ptr = mlx_new_image(mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	mlx->img.data = (unsigned char *)mlx_get_data_addr(mlx->img.img_ptr,
													   &mlx->img.bpp, &mlx->img.size_l, &mlx->img.endian);
}

double	ft_sqrs(double x)
{
	return (x * x);
}

float	ft_deg_to_rad(float angle)
{
	return ((angle / 180.0) * M_PI);
}

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
	t_vect x;

	cone = (t_cone *)elem->shape;
	if (elem->id == 4)
	{
		k = tan(cone->radius / 180.0 * M_PI);
		x = vector_sub(ray.origin, cone->origin);
		//a = 1 - (1 + tan) * pow(vector_scalar(ray.dir, cone->axis), 2);

		a = vector_scalar(ray.dir, ray.dir) - ((1 + ft_sqrs(k)) * ft_sqrs(vector_scalar(ray.dir, cone->axis)));
		b = 2.0 * (vector_scalar(ray.dir, x) - (1 + ft_sqrs(k))
			* vector_scalar(ray.dir, cone->axis) * vector_scalar(x, cone->axis));
		c = vector_scalar(x, x) - ((1 + ft_sqrs(k)) * ft_sqrs(vector_scalar(x, cone->axis)));
		//b = vector_scalar(ray.dir, x) - ((1 + tan) * vector_scalar(ray.dir, cone->axis) * vector_scalar(x, cone->axis));
		//b *= 2.0;
		//c = vector_snorme(x) - ((1 + tan) * pow(vector_scalar(x, cone->axis),2));
		delta = b * b - (4 * a * c);
		if (delta < 0)
			return (0);
		s1 = (-b - sqrt(delta)) / (2 * a);
		s2 = (-b + sqrt(delta)) / (2 * a);
		if (s2 < 0 && s1 < 0)
			return (0);
		intersect->inter = 1;
		s = fmin(s1, s2);

		//intersect->coord_min = fmin(intersect->coord_min, s);
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


void		intersection(t_ray ray, t_shape *shape, t_intersection *intersect)
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

void		mlx_hooks(t_mlx *mlx)
{
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win, mlx->img.img_ptr, 0, 0);
	mlx_hook(mlx->win, 2, 0, key_press, mlx);
	mlx_loop(mlx->mlx_ptr);
}

int main(int ac, char **av)
{
	t_rtv1 r;
	t_mlx mlx;
	t_ray ray;
	t_ray light;
	double light_intensity;
	t_vect pix_color;
	t_intersection *intersect;
	//0, 10, 50
	vector_generate(&ray.origin, 0, 0, 70);
	vector_generate(&light.origin, 0, 0, 0);
	r.shape = NULL;
	check_ac(ac);
	if (parse(&r, av[1]) < 0)
	{
		ft_putendl("scene not correct");
		return (0);
	}
	int i = 0;
	int j = 0;
	intersect = (t_intersection *)malloc(sizeof(t_intersection));
	light_intensity = 1;
	init_mlx(&mlx, "TEST");
	while (i < WIN_HEIGHT)
	{
		while (j < WIN_WIDTH)
		{
			vector_generate(&ray.dir, j - WIN_WIDTH / 2, i - WIN_HEIGHT / 2, -WIN_WIDTH / (2 * (tan(mlx.fov / 2))));
			vector_normalize(&ray.dir);
			intersection(ray, r.shape, intersect);
			light.dir = vector_sub(light.origin, intersect->p_inter);
			vector_normalize(&light.dir);
			if (intersect->inter)
			{
				// if (intersect->inter_color.b)
				// 	printf("red = %lf      blue = %lf     green = %lf\n", pix_color.x, pix_color.y, pix_color.z);
				pix_color.x = intersect->inter_color.r * light_intensity * fmax(0, vector_scalar(intersect->normal, light.dir)) / vector_snorme(light.dir);
				pix_color.y = intersect->inter_color.g * light_intensity * fmax(0, vector_scalar(intersect->normal, light.dir)) / vector_snorme(light.dir);
				pix_color.z = intersect->inter_color.b * light_intensity * fmax(0, vector_scalar(intersect->normal, light.dir)) / vector_snorme(light.dir);
				// mlx.img.data[(j * 4 + 4 * WIN_HEIGHT * (WIN_HEIGHT - i)) + 0] = fmin(255., fmax(pix_color.z, 0.)); //blue
				mlx.img.data[4 * (WIN_WIDTH * (WIN_HEIGHT - i - 1) + j) + 0] = fmin(255., fmax(pix_color.z, 0.)); //blue
				mlx.img.data[4 * (WIN_WIDTH * (WIN_HEIGHT - i - 1) + j) + 1] = fmin(255., fmax(pix_color.y, 0.)); //green
				mlx.img.data[4 * (WIN_WIDTH * (WIN_HEIGHT - i - 1) + j) + 2] = fmin(255., fmax(pix_color.x, 0.)); //red
			}
			j++;
		}
		i++;
		j = 0;
	}
	//mlx_put_image_to_window(mlx.mlx_ptr, mlx.win, mlx.img.img_ptr, 0, 0);
	//mlx_hook(mlx.win, 2, 0, key_press, &mlx);
	//mlx_loop(mlx.mlx_ptr);
	mlx_hooks(&mlx);
	return (0);
}
