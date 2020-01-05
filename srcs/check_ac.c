/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ac.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hezzahir <hamza.ezzahiry@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 22:38:42 by hezzahir          #+#    #+#             */
/*   Updated: 2019/12/21 22:38:44 by hezzahir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		show_usage(void)
{
	ft_putendl("Usage : ./rtv1 {scene path}");
	exit(0);
}

void		check_ac(int ac)
{
	if (ac != 2)
		show_usage();
}
