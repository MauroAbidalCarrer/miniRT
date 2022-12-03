/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singletons_parsing.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 20:46:07 by maabidal          #+#    #+#             */
/*   Updated: 2022/12/03 20:58:25 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

//checks if intensity is in range [0, 1]
//checks if that there were no spot_light serialized before
int	parse_spot_light(char *line, t_scene *scene)
{
	t_col			dump;
	t_field_parser	parsers[4];
	void			*dsts[3];
	int				status;

	parsers[0] = &parse_vector;
	dsts[0] = &scene->light.pos;
	parsers[1] = &parse_double;
	dsts[1] = &scene->light.intensity;
	parsers[2] = &parse_color;
	dsts[2] = &dump;
	parsers[3] = NULL;
	status = parse_obj(line, parsers, dsts, "L");
	if (status == 2)
		return (1);
	if (status == 1 || !in_range(scene->light.intensity, 0, 1))
		ft_exit(scene->objs, BAD_FORMAT_MSG, line);
	if (scene->singletons_mask & SPOT_MASK)
		ft_exit(scene->objs, "ERROR: duplicate spot light!\n", line);
	scene->singletons_mask |= SPOT_MASK;
	return (0);
}

//check that fov is in 0,180 range,
//checkthat there is not another camera
//normalize direcition
int	parse_camera(char *line, t_scene *scene)
{
	t_camera		cam_buf;
	t_field_parser	parsers[4];
	void			*dsts[3];
	int				status;

	parsers[0] = &parse_vector;
	dsts[0] = &cam_buf.pos;
	parsers[1] = &parse_vector;
	dsts[1] = &cam_buf.dir;
	parsers[2] = &parse_double;
	dsts[2] = &cam_buf.fov;
	parsers[3] = NULL;
	status = parse_obj(line, parsers, dsts, "C");
	if (status == 2)
		return (1);
	if (status == 1 || !in_range(cam_buf.fov, 0, 180))
		ft_exit(scene->objs, BAD_FORMAT_MSG, line);
	if (scene->singletons_mask & CAMERA_MASK)
		ft_exit(scene->objs, "ERROR: duplicate camera!\n", line);
	cam_buf.dir = normalized(cam_buf.dir);
	scene->camera = cam_buf;
	scene->singletons_mask |= CAMERA_MASK;
	return (0);
}

//check for ambient mask
//check ntensity range
int	parse_ambient_light(char *line, t_scene *scene)
{
	t_col			col;
	double			intensity;
	t_field_parser	parsers[3];
	void			*dsts[2];
	int				status;

	parsers[0] = &parse_double;
	dsts[0] = &intensity;
	dsts[1] = &col;
	parsers[1] = &parse_color;
	parsers[2] = NULL;
	status = parse_obj(line, parsers, dsts, "A");
	if (status == 2)
		return (1);
	if (status == 1 || !in_range(intensity, 0, 1))
		ft_exit(scene->objs, BAD_FORMAT_MSG, line);
	if (scene->singletons_mask & AMBIENT_MASK)
		ft_exit(scene->objs, "ERROR: duplicate ambiant light!\n", line);
	scene->ambiant_light = mult_color_scalar(col, intensity);
	scene->singletons_mask |= AMBIENT_MASK;
	return (0);
}
