/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 17:24:49 by maabidal          #+#    #+#             */
/*   Updated: 2022/12/03 20:26:03 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"

t_vec	new_v(double x, double y, double z)
{
	t_vec	v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

double	dist(t_vec a, t_vec b)
{
	return (magnitude(dif(a, b)));
}

double	sqrd_dist(t_vec a, t_vec b)
{
	return (sqrd_mag(dif(a, b)));
}

t_vec	cross(t_vec a, t_vec b)
{
	t_vec	c;

	c.x = a.y * b.z - a.z * b.y;
	c.y = a.z * b.x - a.x * b.z;
	c.z = a.x * b.y - a.y * b.x;
	return (c);
}
