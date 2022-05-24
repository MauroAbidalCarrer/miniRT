/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_scalar_ops.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:21:25 by maabidal          #+#    #+#             */
/*   Updated: 2022/05/17 15:14:05 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

#include <stdio.h>

static void	mult_channels(int color_index, t_col a, t_channel scalar, char *dst)
{
	t_channel	a_channel;
	t_channel	product;
	uint8_t		color_shift;

	color_shift = color_index * 8;
	a_channel = (a & 0xFF << color_shift) >> color_shift;
	product = (a_channel * scalar) / (t_channel)MAX_CHANNEL;
	if (product > MAX_CHANNEL)
		product = (t_channel)MAX_CHANNEL;
	dst[color_index] = (char)product;
}

t_col	mult_color_scalar(t_col col, double scalar)
{
	t_col		tmp;
	char		*add;
	t_channel	oui;

	add = (char *)&tmp;
	if (scalar > 1.0)
		scalar = 1.0;
	else if (scalar < 0)
		scalar = 0;
	oui = (t_channel)(scalar * 255.0);
	mult_channels(RED_INDEX, col, oui, add);
	mult_channels(BLUE_INDEX, col, oui, add);
	mult_channels(GREEN_INDEX, col, oui, add);
	return (tmp);

}
