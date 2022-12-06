/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   high_level.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 00:35:04 by maabidal          #+#    #+#             */
/*   Updated: 2022/12/06 19:41:44 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"

//check foreach object if the ray collides with it
//don't stop to the first collision, another object might collide closer to the
//origin
static int	cast_ray(t_ray ray, t_list *objs, t_rayhit *hit)
{
	int				current;
	int				next;
	t_obj_interface	*interface;

	if (objs == NULL)
		return (FALSE);
	next = cast_ray(ray, objs->next, hit);
	interface = (t_obj_interface *)objs->content;
	current = interface->ray_caster(interface->obj, ray, hit);
	if (current && dot(hit->normal, ray.dir) > 0)
		hit->normal = mul_d(hit->normal, -1);
	return (current || next);
}

static t_ray	mk_lightray(t_vec point, t_vec to_light)
{
	t_ray	light_ray;

	to_light = normalized(to_light);
	light_ray.dir = to_light;
	light_ray.origin = sum(point, mul_d(to_light, 0.01));
	return (light_ray);
}

//1: cast a ray from the pixel (in world space)
//2: if the ray doesn't hit an object, set the pixel to black
//3: if the ray hits an object, send a second one towards the spot light
//if the second ray hits an obj, it means that it is obescured by the second obj
//if there is no obstacle in the second's ray path,
//apply the lighting of the spot
static t_col	render_pixel(t_scene scene, t_ray cam_ray)
{
	t_rayhit	hit;
	t_vec		to_light;
	t_vec		to_light_norm;
	double		lighting;
	t_col		col;

	hit.t = DBL_MAX;
	if (cast_ray(cam_ray, scene.objs, &hit))
	{
		col = mult_colors(hit.albedo, scene.ambiant_light);
		to_light = dif(scene.light.pos, hit.point);
		to_light_norm = normalized(to_light);
		hit.t = DBL_MAX;
		if (!cast_ray(mk_lightray(hit.point, to_light_norm), scene.objs, &hit))
		{
			lighting = dot(hit.normal, normalized(to_light));
			lighting *= scene.light.intensity / sqrd(magnitude(to_light) + 1.0);
			col = add_colors(col, mult_color_scalar(hit.albedo, lighting));
		}
		return (col);
	}
	return (BLACK);
}

//1: create a new image to write into
//2: render each pixl one by one
//3: apply the image and destroy
void	render_img(t_scene scene, t_mlx mlx, t_to_free *to_free)
{
	int		x;
	int		y;
	t_ray	cam_ray;
	void	*img_ptr;
	t_col	*img;

	img_ptr = mlx_new_image(mlx.ptr, WIN_WIDTH, WIN_HEIGHT);
	if (img_ptr == NULL)
		ft_close(to_free);
	img = (t_col *)mlx_get_data_addr(img_ptr, &x, &x, &x);
	x = -1;
	while (++x < WIN_WIDTH)
	{
		y = -1;
		while (++y < WIN_HEIGHT)
		{
			cam_ray = mk_camray(scene.camera, x, y);
			img[x + y * WIN_WIDTH] = render_pixel(scene, cam_ray);
		}
	}
	mlx_put_image_to_window(mlx.ptr, mlx.win, img_ptr, 0, 0);
	mlx_destroy_image(mlx.ptr, img_ptr);
}
