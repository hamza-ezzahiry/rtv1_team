/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anti_leaks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hezzahir <hezzahir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 21:21:21 by hezzahir          #+#    #+#             */
/*   Updated: 2020/01/03 21:21:52 by hezzahir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"


void		make_free(char **words)
{
	int	i;

	i = 0;
	while (words[i])
	{
		ft_memdel((void **) &words[i]);
		i++;
	}
	ft_memdel((void **) &words);
}
