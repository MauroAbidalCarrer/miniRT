/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_color_ops.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 14:22:43 by maabidal          #+#    #+#             */
/*   Updated: 2022/05/17 21:36:12 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_colors.h"

#include <stdio.h>

static void	mult_channels(int color_index, t_col a, t_col b, char *dst)
{
	t_channel	a_channel;
	t_channel	b_channel;
	t_channel	product;
	uint8_t		color_shift;

	color_shift = color_index * 8;
	a_channel = (a & 0xFF << color_shift) >> color_shift;
	b_channel = (b & 0xFF << color_shift) >> color_shift;
	product = (a_channel * b_channel) / (t_channel)MAX_CHANNEL;
//printf("a = %d, b = %d, product= %d\n", a_channel, b_channel, product);
	dst[color_index] = (char)product;
}

t_col	mult_colors(t_col a, t_col b)
{
	t_col	tmp;
	char	*add;

	add = (char *)&tmp;
	mult_channels(RED_INDEX, a, b, add);
	mult_channels(BLUE_INDEX, a, b, add);
	mult_channels(GREEN_INDEX, a, b, add);
	return (tmp);
}

static void	add_channels(int color_index, t_col a, t_col b, char *dst)
{
	t_channel	a_channel;
	t_channel	b_channel;
	t_channel	product;
	uint8_t		color_shift;

	color_shift = color_index * 8;
	a_channel = (a & 0xFF << color_shift) >> color_shift;
	b_channel = (b & 0xFF << color_shift) >> color_shift;
	product = a_channel + b_channel;
	if (product > MAX_CHANNEL)
		dst[color_index] = (char)MAX_CHANNEL;
	else
		dst[color_index] = (char)product;
}

t_col	add_colors(t_col a, t_col b)
{
	t_col	tmp;
	char	*add;

	add = (char *)&tmp;
	add_channels(RED_INDEX, a, b, add);
	add_channels(BLUE_INDEX, a, b, add);
	add_channels(GREEN_INDEX, a, b, add);
	return (tmp);
}
