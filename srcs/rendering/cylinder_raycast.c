/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_raycast.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 20:18:44 by maabidal          #+#    #+#             */
/*   Updated: 2022/12/03 20:19:07 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include "rendering.h"

static int	disk_raycast(t_cylinder cylinder, t_ray ray, t_rayhit *hit)
{
	t_rayhit	plane_hit;
	t_plane		plane;

	plane.normal = cylinder.dir;
	if (dot(plane.normal, ray.dir) > 0)
		plane.normal = mul_d(plane.normal, -1);
	plane.pos = sum(cylinder.pos, mul_d(plane.normal, cylinder.height));
	plane.albedo = cylinder.albedo;
	plane_hit.t = DBL_MAX;
	if (plane_raycast(&plane, ray, &plane_hit)
		&& sqrd_dist(plane_hit.point, plane.pos) <= sqrd(cylinder.diameter / 2))
	{
		*hit = plane_hit;
		return (TRUE);
	}
	return (FALSE);
}

//a is first used as a in a 2nd degree equation,
//and then as the "t" on cylinder's ray.
int	tube_raycast(t_cylinder cyl, t_ray ray, t_rayhit *hit, double *inters)
{
	t_vec	a_v;
	t_vec	b_v;
	double	a;
	double	b;
	double	c;

	a_v = mul_d(cyl.dir, dot(cyl.dir, ray.dir));
	b_v = sum(cyl.pos, mul_d(cyl.dir, dot(cyl.dir, dif(ray.origin, cyl.pos))));
	a = sqrd_mag(dif(ray.dir, a_v));
	b = dot(dif(ray.origin, b_v), dif(ray.dir, a_v)) * 2;
	c = sqrd_mag(dif(ray.origin, b_v)) - sqrd(cyl.diameter / 2);
	if (solve_2nd_degree(a, b, c, inters) && are_hits(inters, hit))
	{
		hit->point = sum(ray.origin, mul_d(ray.dir, hit->t));
		a = dot(cyl.dir, dif(hit->point, cyl.pos));
		a_v = sum(cyl.pos, mul_d(cyl.dir, a));
		hit->normal = normalized(dif(hit->point, a_v));
		hit->albedo = cyl.albedo;
		if (a >= -cyl.height && a <= cyl.height)
			return (TRUE);
	}
	return (FALSE);
}

int	cylinder_raycast(void *cylinder_ptr, t_ray ray, t_rayhit *hit)
{
	t_cylinder	cyl;
	double		inters[2];
	t_rayhit	tube_hit;

	cyl = *(t_cylinder *)cylinder_ptr;
	if (disk_raycast(cyl, ray, hit))
		return (TRUE);
	tube_hit.t = DBL_MAX;
	if (tube_raycast(cyl, ray, &tube_hit, inters))
	{
		*hit = tube_hit;
		return (TRUE);
	}
	return (FALSE);
}
