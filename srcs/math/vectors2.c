/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 17:30:22 by maabidal          #+#    #+#             */
/*   Updated: 2022/05/13 17:52:08 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

#include <stdio.h>

t_vec	div_d(t_vec v, double d)
{
	v.x /= d;
	v.y /= d;
	v.z /= d;
	return (v);
}

t_vec	mul_d(t_vec v, double d)
{
	v.x *= d;
	v.y *= d;
	v.z *= d;
	return (v);
}

double	magnitude(t_vec v)
{
	return (sqrt(sqrd_mag(v)));
}

double sqrd_mag(t_vec v)
{
	return (dot(v, v));
}

double	dot(t_vec a, t_vec b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

void	print_vec2(t_vec v)
{
	printf("(%f, %f)\n", v.x, v.y);
}

void	print_vec3(t_vec v)
{
	printf("(%f, %f, %f)\n", v.x, v.y, v.z);
}
