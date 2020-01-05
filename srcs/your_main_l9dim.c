/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   your_main_l9dim.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hezzahir <hezzahir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 22:51:13 by hhamdaou          #+#    #+#             */
/*   Updated: 2020/01/05 13:36:13 by hezzahir         ###   ########.fr       */
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

int intersection(t_ray ray, t_sphere sphere, t_vect *inter, t_vect *N)
{
	double b;
	double c;
	double delta;
	double s1;
	double s2;
	double s;

	b = 2 * vector_scalar(ray.dir, vector_sub(ray.origin, sphere.origin));
	c = vector_snorme(vector_sub(ray.origin, sphere.origin)) - sphere.radius * sphere.radius;
	delta = b * b - 4 * c;
	if (delta < 0)
		return (0);
	s1 = (-b - sqrt(delta)) / 2;
	s2 = (-b + sqrt(delta)) / 2;
	if (s2 < 0 || s1 < 0)
		return (0);
	if (s2 > s1)
		s = s1;
	else
		s = s2;
	*inter = vector_sum(ray.origin, vector_multi(ray.dir, s));
	*N = vector_sub(*inter, sphere.origin);
	vector_normalize(N);
	return (1);
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

int     main(int ac, char **av)
{
	t_mlx mlx;
	t_ray ray;
	t_ray light;
	t_sphere sphere;
	t_vect inter;
	t_vect N;
	double light_intensity;
	t_vect pix_color;

	vector_generate(&ray.origin, 0, 0, 0);
	vector_generate(&light.origin, 0, 100, 0);
	vector_generate(&sphere.origin, 0, 0, -100);
	sphere.radius = 30;
	sphere.color = (t_vect){255, 231, 54};
	int i = 0;
	int j = 0;
	light_intensity = 0.95;

	init_mlx(&mlx, "TEST");
	while (i < WIN_HEIGHT)
	{
		while (j < WIN_WIDTH)
		{
			vector_generate(&ray.dir, j - WIN_WIDTH / 2, i - WIN_HEIGHT / 2, -WIN_WIDTH / (2 * (tan(mlx.fov / 2))));
			vector_normalize(&ray.dir);
			int intersect = intersection(ray, sphere, &inter, &N);
			light.dir = vector_sub(light.origin, inter);
			vector_normalize(&light.dir);
			if (intersect)
			{
				pix_color.x = sphere.color.x * light_intensity * vector_scalar(N, light.dir) / vector_snorme(light.dir);
				pix_color.y = sphere.color.y * light_intensity * vector_scalar(N, light.dir) / vector_snorme(light.dir);
				pix_color.z = sphere.color.z * light_intensity * vector_scalar(N, light.dir) / vector_snorme(light.dir);
				mlx.img.data[(j * 4 + 4 * WIN_HEIGHT * (WIN_HEIGHT - i)) + 0] = fmin(255., fmax(pix_color.z, 0.)); //blue
				mlx.img.data[(j * 4 + 4 * WIN_HEIGHT * (WIN_HEIGHT - i)) + 1] = fmin(255., fmax(pix_color.y, 0.)); //green
				mlx.img.data[(j * 4 + 4 * WIN_HEIGHT * (WIN_HEIGHT - i)) + 2] = fmin(255., fmax(pix_color.x, 0.)); //red
			}
			j++;
		}
		i++;
		j = 0;
	}
	//printf("maxx = %lf\n", maxx);
	mlx_put_image_to_window(mlx.mlx_ptr, mlx.win, mlx.img.img_ptr, 0, 0);
	mlx_hook(mlx.win, 2, 0, key_press, &mlx);
	mlx_loop(mlx.mlx_ptr);
	return (0);
}


