/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_vector_and_color.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 20:43:49 by maabidal          #+#    #+#             */
/*   Updated: 2022/12/03 20:44:12 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*parse_vector(char *str, void *dst)
{
	int		i;
	double	*dsts[3];

	dsts[0] = &((t_vec *)dst)->x;
	dsts[1] = &((t_vec *)dst)->y;
	dsts[2] = &((t_vec *)dst)->z;
	i = -1;
	while (++i < 3)
	{
		str = parse_double(str, dsts[i]);
		if (str == NULL)
			return (NULL);
		if (i < 2 && *(str++) != ',')
			return (NULL);
	}
	return (str);
}

int	vector_in_range(t_vec vec, double min, double max)
{
	int	res;

	res = in_range(vec.x, min, max);
	res &= in_range(vec.y, min, max);
	res &= in_range(vec.z, min, max);
	return (res);
}

char	*parse_color(char *str, void *dst)
{
	int	channel;
	int	bit_shifts[3];	
	int	i;

	*(t_col *)dst = 0;
	bit_shifts[0] = 16;
	bit_shifts[1] = 8;
	bit_shifts[2] = 0;
	i = -1;
	while (++i < 3)
	{
		channel = ft_atoi(str);
		while (ft_isdigit(*str))
			str++;
		if ((i < 2 && *(str++) != ',') || channel > 255 || channel < 0)
			return (NULL);
		*(t_col *)dst |= channel << bit_shifts[i];
	}
	return (str);
}
