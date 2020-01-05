/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hezzahir <hezzahir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 11:27:28 by hezzahir          #+#    #+#             */
/*   Updated: 2020/01/05 12:40:00 by hezzahir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
**	Counting number of words splited
*/

int		nb_word(char **words)
{
	int	nb;

	nb = 0;
	if(!words)
		return (0);
	while(words[nb] != 0)
		nb++;
	return (nb);
}

void		add_shape(t_shape **shapes, t_shape *new)
{
	if(!shapes || !new)
		return ;
	new->next = *shapes;
	*shapes = new;
}
