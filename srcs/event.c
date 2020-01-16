/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hezzahir <hamza.ezzahiry@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 18:18:56 by hezzahir          #+#    #+#             */
/*   Updated: 2020/01/16 18:37:33 by hezzahir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			key_press(int key, t_mlx *mlx)
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

void		init_mlx(t_mlx *mlx, char *str)
{
	mlx->fov = 60 * M_PI / 180;
	mlx->mlx_ptr = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, str);
	mlx->img.img_ptr = mlx_new_image(mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	mlx->img.data = (unsigned char *)mlx_get_data_addr(mlx->img.img_ptr,
							&mlx->img.bpp, &mlx->img.size_l, &mlx->img.endian);
}

void		mlx_hooks(t_mlx *mlx)
{
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win, mlx->img.img_ptr, 0, 0);
	mlx_hook(mlx->win, 2, 0, key_press, mlx);
	mlx_loop(mlx->mlx_ptr);
}
