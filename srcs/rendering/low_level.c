/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   low_level.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 00:32:37 by maabidal          #+#    #+#             */
/*   Updated: 2022/12/02 19:01:28 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>

#include "rendering.h"

BOOL	are_hits(double *inters, t_rayhit *hit)
{
	if(*inters > 0 && *inters < hit->t)
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

BOOL	sphere_raycast(void *sphere, t_ray ray, t_rayhit *hit)
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

//-recadrage: obtenir une valeur entre -1 et 1
//creer canvas_scale 
//-map to canvas
t_ray	mk_camray(t_camera cam, int x, int y)
{
	t_ray	ray;
	t_vec	canvas_scale;

	ray.origin.x = ((double)x - (double)HALF_WIDTH) / (double)HALF_WIDTH;
	ray.origin.y = ((double)HALF_HEIGHT - (double)y) / (double)HALF_HEIGHT;
	canvas_scale.x = tan(DEG2RAD * cam.fov);
	canvas_scale.y = canvas_scale.x * ((double)WIN_HEIGHT / (double)WIN_WIDTH);
	ray.origin = mul(ray.origin, canvas_scale);
	ray.origin.z = 1.0;
//printf("origin after mult= ");print_vec3(ray.origin);
	ray.dir = normalized(ray.origin);
	ray.dir = mult_vec_by_matrix(ray.dir, cam.rotation);
	return (ray);
}

BOOL	plane_raycast(void *plane_ptr, t_ray ray, t_rayhit *hit)
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

static BOOL	disk_raycast(t_cylinder cylinder, t_ray ray, t_rayhit *hit)
{
	t_rayhit	plane_hit;
	t_plane		plane;

	plane.normal = cylinder.dir;
	if (dot(plane.normal, ray.dir) > 0)
		plane.normal = mul_d(plane.normal, -1);
	plane.pos = sum(cylinder.pos, mul_d(plane.normal, cylinder.height));
	plane.albedo = cylinder.albedo;
	plane_hit.t = DBL_MAX;
	if (plane_raycast(&plane, ray, &plane_hit) && sqrd_dist(plane_hit.point, plane.pos) <= sqrd(cylinder.radius))
	{
		*hit = plane_hit;
		return (TRUE);
	}
	return (FALSE);
}

//a is first used as a in a 2nd degree equation,
//and then as the "t" on cylinder's ray.
BOOL	tube_raycast(t_cylinder cyl, t_ray ray, t_rayhit *hit, double *inters)
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
	c = sqrd_mag(dif(ray.origin, b_v)) - sqrd(cyl.radius);
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

BOOL	cylinder_raycast(void *cylinder_ptr, t_ray ray, t_rayhit *hit)
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
