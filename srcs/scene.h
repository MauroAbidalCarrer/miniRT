/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 00:55:22 by maabidal          #+#    #+#             */
/*   Updated: 2022/05/22 16:43:52 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "rendering.h"
# include "header.h"

# ifndef BOOL
#  define BOOL uint8_t 
#  define FALSE 0
#  define TRUE 1
# endif
# ifndef RAYHIT
#  define RAYHIT
typedef struct s_rayhit
{
	t_col	albedo;
	t_vec	point;
	t_vec	normal;
	double	t;
}	t_rayhit;
# endif 

typedef BOOL (* t_ray_caster)(void *, t_ray, t_rayhit *);

typedef struct s_obj_interface
{
	t_ray_caster	ray_caster;
	void			*obj;
}	t_obj_interface;

typedef struct e_camera
{
	t_vec		pos;
	t_vec		dir;
	t_matrix	rotation;
	uint8_t		fov;
}				t_camera;

typedef struct e_light
{
	t_vec		pos;
	double		intensity;
}				t_light;

typedef struct e_sphere
{
	t_vec		center;
	double		radius;
	t_col		albedo;
}				t_sphere;

typedef struct e_plane
{
	t_vec		pos;
	t_vec		normal;
	t_col		albedo;
}				t_plane;

typedef struct e_cylinder
{
	t_vec		pos;
	t_vec		dir;
	double		radius;
	double		height;
	t_col		albedo;
}				t_cylinder;

typedef struct s_scene
{
	t_list		*objs;
	t_light		light;
	t_camera	camera;
	t_col 		ambiant_light;
}	t_scene;
#endif
