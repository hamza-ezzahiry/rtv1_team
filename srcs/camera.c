/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hezzahir <hamza.ezzahiry@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 17:30:15 by hezzahir          #+#    #+#             */
/*   Updated: 2020/02/09 16:15:33 by hezzahir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		is_fov(char *word)
{
	int	i;
	int	res;

	i = 0;
	if (ft_strlen(word) > 3)
		return (60);
	while (word[i])
	{
		if (!ft_isdigit(word[i]))
			return (60);
		i++;
	}
	res = ft_atoi(word);
	if (res > 180 || res <= 0)
		return (60);
	return (res);
}

void	set_camera(char **words, t_rtv1 *r)
{
	r->cam.pos = get_vect_from_str(words[1]);
	r->cam.lookat = get_vect_from_str(words[2]);
	r->cam.fov = is_fov(words[3]);
	r->is_okey[0] = '1';
}

void	init_cam(t_rtv1 *r)
{
	t_vect up;

	up = (t_vect){0., 1., 0.};
	r->cam.fov = r->cam.fov * M_PI / 180;
	r->cam.pos.z += EPS;
	r->cam.w = vector_sub(r->cam.lookat, r->cam.pos);
	vector_normalize(&r->cam.w);
	r->cam.v = vector_cross(r->cam.w, up);
	vector_normalize(&r->cam.v);
	r->cam.u = vector_cross(r->cam.v, r->cam.w);
	r->cam.height = tan(r->cam.fov / 2) * 2;
	r->cam.width = r->cam.height * (WIN_WIDTH / WIN_HEIGHT);
}
