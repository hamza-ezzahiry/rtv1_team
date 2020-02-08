/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hezzahir <hamza.ezzahiry@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 18:18:56 by hezzahir          #+#    #+#             */
/*   Updated: 2020/02/08 12:04:58 by hezzahir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		free_list_light(t_rtv1 *r)
{
	t_light	*tmp;

	while (r->light)
	{
		tmp = r->light;
		r->light = r->light->next;
		ft_memdel((void **)&(tmp));
	}
}

void		free_list_shapes(t_rtv1 *r)
{
	t_shape	*tmp;

	while (r->shape)
	{
		tmp = r->shape;
		r->shape = r->shape->next;
		ft_memdel((void **)&(tmp));
	}
}

int			key_press(int key, t_rtv1 *r)
{
	if (key == 53)
	{
		mlx_destroy_image(r->mlx.mlx_ptr, r->mlx.img.img_ptr);
		mlx_destroy_window(r->mlx.mlx_ptr, r->mlx.win);
		ft_memdel((void **)&(r->mlx.mlx_ptr));
		free_list_light(r);
		free_list_shapes(r);
		exit(1);
	}
	return (0);
}

void		init_mlx(t_rtv1 *r, char *str)
{
	r->mlx.mlx_ptr = mlx_init();
	r->mlx.win = mlx_new_window(r->mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, str);
	r->mlx.img.img_ptr = mlx_new_image(r->mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	r->mlx.img.data = (unsigned char *)mlx_get_data_addr(r->mlx.img.img_ptr,
						&r->mlx.img.bpp,
						&r->mlx.img.size_l, &r->mlx.img.endian);
}

void		mlx_hooks(t_rtv1 *r)
{
	mlx_put_image_to_window(r->mlx.mlx_ptr, r->mlx.win,
		r->mlx.img.img_ptr, 0, 0);
	mlx_hook(r->mlx.win, 2, 0, key_press, r);
	mlx_loop(r->mlx.mlx_ptr);
}
