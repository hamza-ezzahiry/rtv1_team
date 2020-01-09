/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hezzahir <hezzahir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 22:51:13 by hhamdaou          #+#    #+#             */
/*   Updated: 2020/01/09 01:23:22 by hezzahir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		main(int ac, char **av)
{
	t_rtv1		r;

	r.shape = NULL;
	check_ac(ac);
	if(parse(&r, av[1]) < 0)
	{
		ft_putendl("scene not correct");
		return (0);
	}
	t_shape *sh = r.shape;

/*
** 		camera elements
*/
	printf("=================== CAMERA : ================\n");
	printf("Position : %.0lf %.0lf %.0lf\n", r.cam.pos.x,r.cam.pos.y,r.cam.pos.z);
	printf("color : %lf %lf %lf \n", r.cam.lookat.x, r.cam.lookat.y,r.cam.lookat.z);
	printf("fov : %d\n", r.cam.fov);
	printf("===========================================\n\n");
/*
**		All the shapes
*/
	printf("=================All the shapes ==============\n");
	while (sh != NULL)
	{
		if (sh->id == 1)
		{
			t_sphere *sp = (t_sphere*)sh->shape;
			printf("coleur sphere %d %d %d\n", sp->color.r, sp->color.g, sp->color.b);
			printf("cord %.0lf %.0lf %.0lf\n", sp->origin.x, sp->origin.y, sp->origin.z);
			printf("\n\n");
		}
		sh = sh->next;
	}
	printf("===========================================\n\n");
	return (0);
}
