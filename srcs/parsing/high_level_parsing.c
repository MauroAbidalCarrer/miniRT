/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   high_level_parsing.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 20:47:53 by maabidal          #+#    #+#             */
/*   Updated: 2022/12/07 18:49:08 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

//function called by ft_lst_clear
static void	free_obj(void *obj_interface)
{
	free(((t_obj_interface *)obj_interface)->obj);
	free(obj_interface);
}

static void	ft_exit(t_list *objs, char *error_msg)
{
	if (error_msg != NULL)
		ft_putstr_fd(error_msg, 1);
	ft_lstclear(&objs, &free_obj);
	exit(error_msg != NULL);
}

//object parsers should return one if the line is empty
//object parsers should call ft_exit if there is a format issue
//line has to be either just \n or describe an object
static int	parse_line(char *line, t_scene *scene)
{
	t_object_parser	parsers[6];
	int				error;
	int				i;
	int				status;
	int				not_found;

	parsers[0] = &parse_spot_light;
	parsers[1] = &parse_ambient_light;
	parsers[2] = &parse_camera;
	parsers[3] = &parse_cylinder;
	parsers[4] = &parse_sphere;
	parsers[5] = &parse_plane;
	i = -1;
	not_found = 0;
	error = 0;
	if (*line == '\n')
		return (NO_ERROR);
	while (++i < 6)
	{
		status = (parsers[i])(line, scene);
		error = (status == ERROR || error);
		if (status == NOT_FOUND)
			not_found++;
	}
	return (error || not_found == 6);
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
		ft_exit(NULL, "ERROR: file doesn't finish in \".rt\"\n");
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
	int		status;

	fd = get_fd(filename);
	scene->objs = NULL;
	scene->singletons_mask = 0;
	line = get_next_line(fd);
	status = 0;
	while (line)
	{
		status = (status || parse_line(line, scene));
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (status == ERROR
		|| (scene->singletons_mask & SPOT_MASK) == 0
		|| (scene->singletons_mask & AMBIENT_MASK) == 0
		|| (scene->singletons_mask & CAMERA_MASK) == 0)
		ft_exit(scene->objs, BAD_FORMAT_MSG);
}
