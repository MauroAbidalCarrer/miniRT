/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   high_level_parsing.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 20:47:53 by maabidal          #+#    #+#             */
/*   Updated: 2022/12/06 16:53:22 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

//object parsers should return one if the line is empty
//object parsers should call ft_exit if there is a format issue
//line has to be either just \n or describe an object
static void	parse_line(char *line, t_scene *scene)
{
	if (*line != '\n'
		&& parse_spot_light(line, scene)
		&& parse_ambient_light(line, scene)
		&& parse_camera(line, scene)
		&& parse_cylinder(line, scene)
		&& parse_sphere(line, scene)
		&& parse_plane(line, scene))
		ft_exit(scene->objs, BAD_FORMAT_MSG, line);
}

//makes sure the file ends in .rt
static int	get_fd(char *filename)
{
	int	fd;
	int	len;

	len = ft_strlen(filename);
	if (len < 3
		|| filename[len - 1] != 't'
		|| filename[len - 2] != 'r'
		|| filename[len - 3] != '.')
		ft_exit(0, "ERROR: file doesn't finish in \".rt\"\n", 0);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("ERROR: ");
		exit(1);
	}
	return (fd);
}

//must be called before setting up mlx
//if light, camera or ambient light hasn't been serialized
//exit with parsing error
void	parse_scene(char *filename, t_scene *scene)
{
	char	*line;
	int		fd;

	fd = get_fd(filename);
	scene->objs = NULL;
	scene->singletons_mask = 0;
	line = get_next_line(fd);
	while (line)
	{
		parse_line(line, scene);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if ((scene->singletons_mask & SPOT_MASK) == 0
		|| (scene->singletons_mask & AMBIENT_MASK) == 0
		|| (scene->singletons_mask & CAMERA_MASK) == 0)
		ft_exit(scene->objs, NO_SING_MSG, NULL);
}
