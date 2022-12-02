/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 16:58:17 by maabidal          #+#    #+#             */
/*   Updated: 2022/12/02 17:34:22 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "../scene.h"
# include "../math/ft_math.h"
#include "../libft/libft.h"
#include <string.h>
#include <stdio.h>

int in_range(double val, double min, double max)
{
	return (val >= min && val <= max);
}

static int	parse_decimal_in_double(char **str, double *dst)
{
	int	parsed_something;
	double	mult;

	mult = 0.1;
	parsed_something = 0;
	while (ft_isdigit(**str))
	{
		parsed_something = 1;
		*dst += mult * (double)(**str - '0');
		mult *= 0.1;
		(*str)++;
	}
	return (parsed_something == 0);
}

static int	parse_int_in_double(char **str, double *dst)
{
	int	parsed_something;

	parsed_something = 0;
	while (ft_isdigit(**str))
	{
		parsed_something = 1;
		*dst *= 10;
		*dst += (double)(**str - '0');
		(*str)++;
	}
	return (parsed_something == 0);
}

//return NULL if there is no number
//return NULL if there is no number before the  '.'
//return NULL if there is no number after the '.'
char	*parse_double(char *str, void *dst)
{
	double sign;

	*(double *)dst = 0;
	sign = 1 - 2 * (*str == '-');
	str += (*str == '-' || *str == '+');
	if (parse_int_in_double(&str, (double *)dst))
		return (NULL);
	if (*str != '.')
	{
		*(double *)dst *= sign;
		return (str);
	}
	str++;
	if (parse_decimal_in_double(&str, (double *)dst))
		return (NULL);
	*(double *)dst *= sign;
	return (str);
}

char	*parse_vector(char *str, void *dst)
{
	int	i;
	double	*dsts[3];

	dsts[0] = &((t_vec *)dst)->x;
	dsts[1] = &((t_vec *)dst)->y;
	dsts[2] = &((t_vec *)dst)->z;
	i = -1;
	while (++i < 3)
	{
		str = parse_double(str, dsts[i]);
		if (str == NULL)
			return (NULL);
		if (i < 2 && *(str++) != ',')
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
	int	bit_shifts[3];	
	int	i;

	*(t_col *)dst = 0;
	bit_shifts[0] = 16;
	bit_shifts[1] = 8;
	bit_shifts[2] = 0;
	i = -1;
	while (++i < 3)
	{
		channel = ft_atoi(str);
		while (ft_isdigit(*str))
			str++;
		if ((i< 2 && *(str++) != ',')|| channel > 255 || channel < 0)
			return (NULL);
		*(t_col *)dst |= channel << bit_shifts[i];
//printf("channel = %8X, dst = %8X\n", channel << bit_shifts[i], *(t_col *)dst);
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
int	parse_object(char *line, t_field_parser *parsers, void **dsts, char *occ)
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
	return (*line != '\n' && *line != 0);
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
	status = parse_object(line, parsers, dsts, "L");
//printf("spot_light, line \"%s\", status %d\n", line, status);
	if (status == 2)
		return (1);
	if (status == 1 /*|| !in_range(scene->light.intensity, 0, 1)*/)
		ft_exit(scene->objs, BAD_FORMAT_MSG, line);
	if (scene->singletons_mask & SPOT_MASK)
		ft_exit(scene->objs, "ERROR: duplicate spot light!\n", line);
	scene->singletons_mask |= SPOT_MASK;
//printf("spot light, pos = ");print_vec3(scene->light.pos);printf(", intensity = %f\n", scene->light.intensity);
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
	status = parse_object(line, parsers, dsts, "C");
	if (status == 0)
		printf("fov qfter parse_object = %f\n", cam_buf.fov);
	if (status == 2)
		return (1);
	if (status == 1 || !in_range(cam_buf.fov, 0, 180))
		ft_exit(scene->objs, BAD_FORMAT_MSG, line);
	if (scene->singletons_mask & CAMERA_MASK)
		ft_exit(scene->objs, "ERROR: duplicate camera!\n", line);
	cam_buf.dir = normalized(cam_buf.dir);
	scene->camera = cam_buf;
	scene->singletons_mask |= CAMERA_MASK;
//printf("camera, pos = ");print_vec3(cam_buf.pos);printf(", dir = ");print_vec3(cam_buf.dir);printf(", fov %f\n", cam_buf.fov);
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
	status = parse_object(line, parsers, dsts, "A");
	if(status == 2)
		return (1);
	if (status == 1 /*|| !in_range(intensity, 0, 1)*/)
		ft_exit(scene->objs, BAD_FORMAT_MSG, line);
	if (scene->singletons_mask & AMBIENT_MASK)
		ft_exit(scene->objs, "ERROR: duplicate ambiant light!\n", line);
	scene->ambiant_light = mult_color_scalar(col, intensity);
	scene->singletons_mask |= AMBIENT_MASK;
//printf("ambient light, col = %8X\n", scene->ambiant_light);
	return (0);
}

void	add_new_obj(char *line, t_scene *scene, void *cpy, t_ray_caster caster)
{
	t_obj_interface	*interface;
	t_list			*new_node;

	interface = malloc(sizeof(t_obj_interface));
	new_node = malloc(sizeof(t_list));
	if (new_node == NULL || interface == NULL || cpy == NULL)
	{
		free(interface);
		free(cpy);
		ft_exit(scene->objs, ALLOCATION_ERROR_MSG, line);
	}
	interface->obj = cpy;
	interface->ray_caster = caster;
	new_node->content = interface;
	new_node->next = NULL;
	ft_lstadd_front(&scene->objs, new_node);
}

//check dir in range [-1, 1]
//divides radius by two to get actual radius(and not diameter)
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
	dsts[2] = &cyl_buff.radius;
	parsers[3] = &parse_double;
	dsts[3] = &cyl_buff.height;
	parsers[4] = &parse_color;
	dsts[4] = &cyl_buff.albedo;
	parsers[5] = NULL;
	status = parse_object(line, parsers, dsts, "cy");
	if (status == 2)
		return (1);
	if (status == 1 || !vector_in_range(cyl_buff.dir, -1, 1))
		ft_exit(scene->objs, BAD_FORMAT_MSG, line);
	cyl_buff.radius /= 2.0;
	cyl_buff.dir = normalized(cyl_buff.dir);
//printf("cylinder pos = ");print_vec3(cyl_buff.pos);printf(", dir = ");print_vec3(cyl_buff.dir);printf(", radius = %f, height = %f, albedo = %8X\n", cyl_buff.radius, cyl_buff.height, cyl_buff.albedo);
	cpy = ft_memcpy(malloc(sizeof(t_cylinder)), &cyl_buff, sizeof(t_cylinder));
//printf("cylinder pos = ");print_vec3(cpy->pos);printf(", dir = ");print_vec3(cpy->dir);printf(", radius = %f, height = %f, albedo = %8X\n", cpy->radius, cpy->height, cpy->albedo);
	return (add_new_obj(line, scene, cpy, cylinder_raycast), 0);
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
	status = parse_object(line, parsers, dsts, "sp");
	if (status == 2)
		return (1);
	if (status == 1)
		ft_exit(scene->objs, BAD_FORMAT_MSG, line);
	sphere_buff.radius /= 2.0;
	cpy = ft_memcpy(malloc(sizeof(t_sphere)), &sphere_buff, sizeof(t_sphere));
	return (add_new_obj(line, scene, cpy, sphere_raycast), 0);
}

int parse_plane(char *line, t_scene *scene)
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
	status = parse_object(line, parsers, dsts, "pl");
	if (status == 2)
		return (1);
	if (status == 1 || !vector_in_range(plane_buff.normal, -1, 1))
		ft_exit(scene->objs, BAD_FORMAT_MSG, line);
	plane_buff.normal = normalized(plane_buff.normal);
	cpy = ft_memcpy(malloc(sizeof(t_plane)), &plane_buff, sizeof(t_plane));
	return (add_new_obj(line, scene, cpy, plane_raycast), 0);
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
		ft_exit(scene->objs, BAD_FORMAT_MSG, line);
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
	line = get_next_line(fd);
	while (line)
	{
		parse_line(line, scene);
		free(line);	
		line = get_next_line(fd);
	}

//printf("spot light, pos = ");print_vec3(scene->light.pos);printf(", intensity = %f\n", scene->light.intensity);
//printf("\nambient = %8X\n", scene->ambiant_light);
	//*scene = setup_scene();
	if ((scene->singletons_mask & SPOT_MASK) == 0 ||
		 (scene->singletons_mask & AMBIENT_MASK) == 0 ||
		 (scene->singletons_mask & CAMERA_MASK) == 0)
		ft_exit(scene->objs, NO_SING_MSG, NULL);
}

//files: field_parsing.c, object_parsing.c, object_parsing2.c
