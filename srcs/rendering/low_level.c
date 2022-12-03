/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   low_level.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 00:32:37 by maabidal          #+#    #+#             */
/*   Updated: 2022/12/03 20:18:30 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include "rendering.h"

int	are_hits(double *inters, t_rayhit *hit)
{
	if (*inters > 0 && *inters < hit->t)
	{
		hit->t = *inters;
		return (TRUE);
	}
	if (inters[1] > 0 && inters[1] < hit->t)
	{
		hit->t = inters[1];
		return (TRUE);
	}
	return (FALSE);
}

int	sphere_raycast(void *sphere, t_ray ray, t_rayhit *hit)
{
	double	a;
	double	b;
	double	c;
	double	inters[2];
	t_vec	co;

	co = dif(ray.origin, ((t_sphere *)sphere)->center);
	a = sqrd_mag(ray.dir);
	b = 2 * dot(co, ray.dir);
	c = sqrd_mag(co) - sqrd(((t_sphere *)sphere)->radius);
	if (solve_2nd_degree(a, b, c, inters) && are_hits(inters, hit))
	{
		hit->point = sum(mul_d(ray.dir, hit->t), ray.origin);
		hit->normal = normalized(dif(hit->point, ((t_sphere *)sphere)->center));
		hit->albedo = ((t_sphere *)sphere)->albedo;
		return (TRUE);
	}
	return (FALSE);
}

t_ray	mk_camray(t_camera cam, int x, int y)
{
	t_ray	ray;
	t_vec	local_origin;
	t_vec	rotated_local_origin;

	local_origin.x = ((double)x - (double)HALF_WIDTH) / (double)HALF_WIDTH;
	local_origin.y = ((double)HALF_HEIGHT - (double)y) / (double)HALF_HEIGHT;
	local_origin.x *= -1 * cam.fov_scalar;
	local_origin.y *= cam.fov_scalar * ((double)WIN_HEIGHT / (double)WIN_WIDTH);
	local_origin.z = NEAR_PLANE;
	rotated_local_origin = mult_vec_by_matrix(local_origin, cam.rotation);
	ray.origin = rotated_local_origin;
	ray.dir = normalized(rotated_local_origin);
	return (ray);
}

int	plane_raycast(void *plane_ptr, t_ray ray, t_rayhit *hit)
{
	double	denominator;
	double	enumerator;
	double	t;
	t_plane	plane;

	plane = *((t_plane *)plane_ptr);
	denominator = dot(plane.normal, ray.dir);
	if (denominator == 0)
		return (FALSE);
	enumerator = dot(dif(plane.pos, ray.origin), plane.normal);
	t = enumerator / denominator;
	if (t > 0 && t < hit->t)
	{
		hit->t = t;
		hit->point = sum(ray.origin, mul_d(ray.dir, t));
		hit->normal = plane.normal;
		hit->albedo = plane.albedo;
		return (TRUE);
	}
	return (FALSE);
}
