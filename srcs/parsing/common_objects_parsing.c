/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_objects_parsing.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 20:47:31 by maabidal          #+#    #+#             */
/*   Updated: 2022/12/07 17:28:31 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	add_obj(t_scene *scene, void *cpy, t_ray_caster caster)
{
	t_obj_interface	*interface;
	t_list			*new_node;

	interface = malloc(sizeof(t_obj_interface));
	new_node = malloc(sizeof(t_list));
	if (new_node == NULL || interface == NULL || cpy == NULL)
	{
		free(new_node);
		free(interface);
		free(cpy);
		return (ERROR);
	}
	interface->obj = cpy;
	interface->ray_caster = caster;
	new_node->content = interface;
	new_node->next = NULL;
	ft_lstadd_front(&scene->objs, new_node);
	return (FOUND_AND_NO_ERROR);
}

//check dir in range [-1, 1]
//divides radius by two to get actual radius(and not diameter)
//add_obj in retur to gain one line
int	parse_cylinder(char *line, t_scene *scene)
{
	t_cylinder		cyl_buff;
	t_field_parser	parsers[6];
	void			*dsts[5];
	int				status;
	t_cylinder		*cpy;

	parsers[0] = &parse_vector;
	dsts[0] = &cyl_buff.pos;
	parsers[1] = &parse_vector;
	dsts[1] = &cyl_buff.dir;
	parsers[2] = &parse_double;
	dsts[2] = &cyl_buff.diameter;
	parsers[3] = &parse_double;
	dsts[3] = &cyl_buff.height;
	parsers[4] = &parse_color;
	dsts[4] = &cyl_buff.albedo;
	parsers[5] = NULL;
	status = parse_obj(line, parsers, dsts, "cy");
	if (status == NOT_FOUND)
		return (NOT_FOUND);
	if (status == ERROR || !vector_in_range(cyl_buff.dir, -1, 1))
		return (ERROR);
	cyl_buff.dir = normalized(cyl_buff.dir);
	cpy = ft_memcpy(malloc(sizeof(t_cylinder)), &cyl_buff, sizeof(t_cylinder));
	return (add_obj(scene, cpy, cylinder_raycast));
}

int	parse_sphere(char *line, t_scene *scene)
{
	t_sphere		sphere_buff;
	t_field_parser	parsers[4];
	void			*dsts[3];
	int				status;
	void			*cpy;

	parsers[0] = &parse_vector;
	dsts[0] = &sphere_buff.center;
	parsers[1] = &parse_double;
	dsts[1] = &sphere_buff.radius;
	parsers[2] = &parse_color;
	dsts[2] = &sphere_buff.albedo;
	parsers[3] = NULL;
	status = parse_obj(line, parsers, dsts, "sp");
	if (status == NOT_FOUND)
		return (NOT_FOUND);
	if (status == ERROR)
		return (ERROR);
	sphere_buff.radius /= 2.0;
	cpy = ft_memcpy(malloc(sizeof(t_sphere)), &sphere_buff, sizeof(t_sphere));
	return (add_obj(scene, cpy, sphere_raycast));
}

int	parse_plane(char *line, t_scene *scene)
{
	t_plane			plane_buff;
	t_field_parser	parsers[4];
	void			*dsts[3];
	int				status;
	void			*cpy;

	parsers[0] = &parse_vector;
	dsts[0] = &plane_buff.pos;
	parsers[1] = &parse_vector;
	dsts[1] = &plane_buff.normal;
	parsers[2] = &parse_color;
	dsts[2] = &plane_buff.albedo;
	parsers[3] = NULL;
	status = parse_obj(line, parsers, dsts, "pl");
	if (status == NOT_FOUND)
		return (NOT_FOUND);
	if (status == ERROR || !vector_in_range(plane_buff.normal, -1, 1))
		return (ERROR);
	plane_buff.normal = normalized(plane_buff.normal);
	cpy = ft_memcpy(malloc(sizeof(t_plane)), &plane_buff, sizeof(t_plane));
	return (add_obj(scene, cpy, plane_raycast));
}
