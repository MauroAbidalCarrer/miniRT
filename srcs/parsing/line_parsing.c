/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 16:58:17 by maabidal          #+#    #+#             */
/*   Updated: 2022/12/01 18:49:07 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "../scene.h"
# include "../math/ft_math.h"
#include "../libft/libft.h"
#include <string.h>
#include <stdio.h>
/*
//return NULL if there is no number
//return NULL if there is no number before the  '.'
//return NULL if there is no number after the '.'
char	*parse_double(char *str, void *dst)
{
	double sign;
	double	multiplier;

	sign = 1 - 2 * (*str == '-');
	str += (*str == '-' || *str == '+');
	multiplier = 1;
	while (ft_is_digit(*str))
	{
		*(double *)dst += multiplier * (double)(*str - '0');
		multiplier *= 10;
		str++;
	}
	if (*str != '.')
		return ((multiplier != 1) * str);
	*str++;
	multiplier = 0.1;
	while (ft_is_digit(*str))
	{
		*(double *)dst += multiplier * (double)(*str - '0');
		multiplier /= 10;
		str++;
	}
	return ((multiplier != 0.1) * str);
}

char	*parse_vector(char *str, void *dst)
{
	int	i;
	double	*dsts[3];

	dsts[0] == &(t_ve *)dst->x;
	dsts[1] == &(t_ve *)dst->y;
	dsts[2] == &(t_ve *)dst->z;
	i = -1;
	while (++i < 3)
	{
		str = parse_double(str, dsts[i]);
		if (str++ == NULL)
			return (NULL);
		if (*(str++) != ',')
			return (NULL);
	}
	return (str);
}

int	vector_in_range(t_vec vec, double min, double max)
{
	int	res;

	res = in_range(vec.x, min, max);
	res &= in_range(vec.y, min, max);
	res &= in_range(vec.z, min, max);
	return (res); 
}

char 	*parse_color(char *str, void *dst)
{
	int	channel;
	t_col	colors[3];
	int	i;

	*(t_col *)col = 0;
	colors[0] = RED;
	colors[1] = GREEN;
	colors[2] = BLUE;
	i = -1;
	while (++i < 3)
	{
		channel = ft_atoi(str);
		str += (*str == '-' || *str == '+')
		while (ft_isdigit(*str))
			str++;
		if (*(str++) != ',' || channel > 255 || channel < 0)
			return (NULL);
		*(t_col *)col = add_colors(*(t_col *)col, mult_colors(colos[i], (double)channel));
	}
	return (str);
}

int	starts_by(char *str, char *str2)
{
	while (*str && *str2 && *str2 == *str)
	{
		str++;
		str2++;
	}
	return (*str2 == 0);
}
//assumes that the line is not empty
//returns 0 success
//returns 1 error encountered
//returns 2 occurence not found
//if the line starts by the occurence but doesn't comply to the subject

//check if the line starts by the occurence

//while field_parers[i], skip spaces run field_pareser[i]
//if it returns one, return one

//once every field_parser has be ran check that the last character == '\n' or wero
int	parse_object(char *line, t_field_parser *parsers, void *dsts, char *occ)
{
	if (!starts_by(line, occ))
		return (2);
	line += ft_strlen(occ);
	while (*parsers)
	{
		line = (*parsers)(skip_spaces(line), *dsts);
		if (line == NULL)
			return (1);
		parsers++;
		dsts++;
	}
	return (*line != '\n' || *line != 0);
}

//checks if intensity is in range [0, 1]
//checks if that there were no spot_light serialized before
int	parse_spot_light(char *line, t_scene *scene)
{
	t_col			dump;
	t_field_parser	parsers[4];
	void			dsts[3];
	int				status;

	parsers[0] = &parse_vector;
	dsts[0] = &scene->light.pos;
	parsers[1] = &parse_double;
	dsts[1] = &scene->light.intensity;
	parsers[2] = &parse_color;
	dsts[2] = &dump;
	parsers[3] = NULL;
	status = parse_object(line, parsers, dsts, "L");
	if (status == 2)
		return (1);
	if (status == 1 || !in_range(scene->light.intensity, 0, 1))
		ft_exit(scene->objs, NULL, BAD_FORMAT_MSG, line);
	if (scene->singleton_mask & SPOT_MASK)
		ft_exit(scene->objs, NULL, DUPLICATE_SING_MSG, line);
	scene->singleton_mask |= SPOT_MASK;
	return (0);
}

void	add_new_obj(char *line, t_scene *scene, void *cpy, t_ray_caster *caster)
{
	t_obj_interface	*interface;
	t_list			*new_node;

	interface = malloc(sizeof(t_obj_interface));
	new_node = malloc(sizeof(t_list));
	if (new_node == NULL || interface == NULL || cpy == NULL)
	{
		free(interfae);
		free(cpy);
		ft_exit(scene->objs, NULL, ALLOCATION_ERROR_MSG, line);
	}
	interface->obj = cpy;
	interface->ray_caster = caster;
	new_node->content = interface;
	ft_lstadd_front(&scene->objs, new_node);
}

//check dir in range [-1, 1]
//divides radius by two to get actual radius(and not diameter)
int	parse_cylinder(char *line, t_scene *scene)
{
	t_cylinder		cyl_buff;
	t_field_parser	parsers[6];
	void			dsts[5];
	int				status;
	void			*cpy;

	parsers[0] = &parse_vector;
	dsts[0] = &cyl_buff.pos;
	parsers[1] = &parse_vector;
	dsts[1] = &cyl_buff.dir;
	parsers[2] = &parse_double;
	dsts[2] = &cyl_buff.radius;
	parsers[3] = &parse_double;
	dsts[3] = &cyl_buff.height;
	parsers[4] = &parse_color;
	dsts[4] = &cyl_buff.col;
	parsers[5] = NULL;
	satus = parse_line(line, parsers, dsts, "cy");
	if (status == 2)
		return (1);
	if (status == 1 || !vector_in_range(cyl.dir, -1, 1))
		ft_exit(scene->objs, NULL, BAD_FORMAT_MSG, line);
	cyl.radius /= 2.0;
	cpy = ft_memcpy(malloc(sizeof(t_cylinder)), &cyl_buff, sizeof(t_cylinder));
	add_new_obj(line, scene->objs, &t_cylinder, cpy);
}

//object parsers should return one if the line is empty
//object parsers should call ft_exit if there is a format issue
//line has to be either just \n or describe an object
void parse_line(char *line, t_scene *scene)
{
	if (*line != '\n' &&
		parse_spot_light(line, scene) &&
		parse_ambient_light(line, scene) &&
		parse_camera(line, scene) &&
		parse_cylinder(line, scene) &&
		parse_sphere(line, scene) &&
		parse_plane(line, scene))
		ft_exit(scene-objs, NULL, BAD_FORMAT_MSG, line);
}

*/
t_scene	setup_scene()
{
	t_scene		scene;

	scene.light.pos = new_v(-11, 8, 19);
	scene.light.intensity = 100;
	scene.camera.dir = new_v(0, 0, 1);
	scene.camera.pos = new_v(0, 0, 0);
	scene.camera.fov = 70.0;
	scene.ambiant_light = 0x00900A0F;

	scene.objs = malloc(sizeof(t_list));
	scene.objs->content = malloc(sizeof(t_obj_interface));
	((t_obj_interface *)scene.objs->content)->ray_caster = &sphere_raycast;
	((t_obj_interface *)scene.objs->content)->obj = malloc(sizeof(t_sphere));
	((t_sphere *)((t_obj_interface *)scene.objs->content)->obj)->center = new_v(5, 0, 17);
	((t_sphere *)((t_obj_interface *)scene.objs->content)->obj)->radius = 5;
	((t_sphere *)((t_obj_interface *)scene.objs->content)->obj)->albedo = 0x00601A5F;
	scene.objs->next = NULL;

	scene.objs->next = malloc(sizeof(t_list));
	scene.objs->next->content = malloc(sizeof(t_obj_interface));
	((t_obj_interface *)scene.objs->next->content)->ray_caster = &plane_raycast;
	((t_obj_interface *)scene.objs->next->content)->obj = malloc(sizeof(t_plane));
	((t_plane *)((t_obj_interface *)scene.objs->next->content)->obj)->pos = new_v(2, -5, 0);
	((t_plane *)((t_obj_interface *)scene.objs->next->content)->obj)->normal = new_v(1, 0, 0);
	((t_plane *)((t_obj_interface *)scene.objs->next->content)->obj)->albedo = 0x00601A5F;

	scene.objs->next->next = malloc(sizeof(t_list));
	scene.objs->next->next->content = malloc(sizeof(t_obj_interface));
	((t_obj_interface *)scene.objs->next->next->content)->ray_caster = &cylinder_raycast;
	((t_obj_interface *)scene.objs->next->next->content)->obj = malloc(sizeof(t_cylinder));
	((t_cylinder *)((t_obj_interface *)scene.objs->next->next->content)->obj)->pos = new_v(-2, -4, 15);
	((t_cylinder *)((t_obj_interface *)scene.objs->next->next->content)->obj)->dir = new_v(0, 1, 0);
	((t_cylinder *)((t_obj_interface *)scene.objs->next->next->content)->obj)->height = 3;
	((t_cylinder *)((t_obj_interface *)scene.objs->next->next->content)->obj)->radius = 2;
	((t_cylinder *)((t_obj_interface *)scene.objs->next->next->content)->obj)->albedo = 0x00601A5F;
	scene.objs->next->next->next = NULL;

	return (scene);
}


static void free_obj(void *obj_interface)
{
	free(((t_obj_interface *)obj_interface)->obj);
	free(obj_interface);
}

static void ft_exit(t_list *objs, char *error_msg, char *line)
{
	if (error_msg != NULL)
		ft_putstr_fd(error_msg, 1);
	ft_lstclear(&objs, &free_obj);
	free(line);
	exit(error_msg != NULL);
}

//makes sure the file ends in .rt
int	get_fd(char *filename)
{
	int	fd;
	int	len;

	len = ft_strlen(filename);
	if (len < 3 ||
		filename[len - 1] != 't' ||
		filename[len - 2] != 'r' ||
		filename[len - 3] != '.')
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
	char*	line;
	int	fd;

	fd = get_fd(filename);
	scene->objs = NULL;
	scene->singletons_mask = 0;
	printf("fd = %d\n", fd);
	line = get_next_line(fd);
	while (line)
	{
		//parse_line(line, scene);
		printf("%s", line);
		free(line);	
		line = get_next_line(fd);
	}
	*scene = setup_scene();
	if ((scene->singletons_mask & SPOT_MASK) == 0 ||
		 (scene->singletons_mask & AMBIENT_MASK) == 0 ||
		 (scene->singletons_mask & CAMERA_MASK) == 0)
		ft_exit(scene->objs, NO_SING_MSG, NULL);
}

//files: field_parsing.c, object_parsing.c, object_parsing2.c
