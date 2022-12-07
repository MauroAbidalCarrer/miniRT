/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 00:55:22 by maabidal          #+#    #+#             */
/*   Updated: 2022/12/07 16:39:58 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "libft.h"
# ifndef BOOL
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

//raycaster is a funciton pointer that takes in this order:
//an object, a ray and a rayhit
//returns one if ray has hit the object
//writes the rayhit if the ray collides with the object
typedef int (* t_ray_caster)(void *, t_ray, t_rayhit *);

//object_interface is used to knoz if a ray collides with an object
//ray_caster is called to know if a ray collides with an object
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
	double		fov;
	double		fov_scalar;
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
	double		diameter;
	double		height;
	t_col		albedo;
}				t_cylinder;

//struct that represents the entire scene
//singletons_mask is a bit mask that is use to check
//that there is exactly one camera, ambent_light and ambient_light
//objs is a list of obj_interfaces
typedef struct s_scene
{
	t_list		*objs;
	t_light		light;
	t_camera	camera;
	t_col 		ambiant_light;
	char		singletons_mask;
}	t_scene;
#endif
