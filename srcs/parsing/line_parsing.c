/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 16:58:17 by maabidal          #+#    #+#             */
/*   Updated: 2022/11/30 02:46:49 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

//change it to fit the field_parser format
//checks that there is a number
//advances *str
//if the number is not properly formated if there is no number:
//returns one zero otherwise
//ERROR: returns zero if tere is no number behind the coma and 
//one or more after it
static int	parse_float(char **str, double *dst)
{
	double	sign;
	int		i;

	*str = skip_spaces(*str);
	i = 0;
	sign = 1;
	if (**str == '-')
		sign = -1;
	(*str) += (**str == '-' || **str == '+');
	*dst = 0;
	i = -1;
	while (ft_isdigit((*str)[++i]))
	{
		*dst *= 10;
		*dst += (double)((*str)[i] - '0') * sign;
	}
	if (**str != '.')
		return (!i);
	*str += i + 1;
	i = -1;
	while (ft_isdigit((*str)[++i]))
		*dst += (double)((*str)[i] - '0') / (10.0 * (double)i) * sign;
	*str += i;
	return (!i);
}

char	*parse_vector(char *str, void *ptr)
{
	t_vec	*vec;

	vec = (t_vec *)ptr;
	if (parse_float(&str, &vec->x) || *(str++) != ',')
		return (NULL);
	if (parse_float(&str, &vec->y) || *(str++) != ',')
		return (NULL);
	if (parse_float(&str, &vec->z))
		return (NULL);
	return (str);
}

//sale
char 	*parse_color(char *str, void *col)
{
	int		channel;

	*col = 0;
	channel = ft_atoi(str);
	str += (*str == '-' || *str == '+')
	while (ft_isdigit(*str))
		str++;
	if (*(str++) != ',' || channel > 255 || channel < 0)
		return (NULL);
	*(t_col *)col = add_colors(*(t_col *)col, mult_colors(RED, (double)channel));
	channel = ft_atoi(str);
	str += (*str == '-' || *str == '+')
	while (ft_isdigit(*str))
		str++;
	if (*(str++) != ',' || channel > 255 || channel < 0)
		return (NULL);
	*(t_col *)col = add_colors(*(t_col *)col, mult_colors(GREEN, (double)channel));
	channel = ft_atoi(str);
	str += (*str == '-' || *str == '+')
	while (ft_isdigit(*str))
		str++;
	if (*(str++) != ',' || channel > 255 || channel < 0)
		return (NULL);
	*(t_col *)col = add_colors(*(t_col *)col, mult_colors(BLUE, (double)channel));
}

void ft_exit(t_list *objs, t_mlx *mlx, char *error_msg, int status)
{
	if (status == 1)
		ft_putstr_fd(error_msg, 1);
	ft_lstclear(&objs, &free_obj);
	if (mlx != NULL)
	{
		if (mlx->win)
			mlx_destroy_window(mlx->ptr, mlx->win);
		if (mlx->ptr != NULL)
			free(to_free->mlx.ptr);
	}
	exit(1);
}

static void free_obj(void *obj_interface)
{
	free((t_obj_interface *)obj_interface->obj);
	free(obj_insterface);
}

//assumes that the line is not empty
//return one 
//if the line starts by the occurence but doesn't comply to the subject

//skip spaces
//check if the line starts by the occurence5return ! otherwise-

//for nb_fields, skip spaces run field_pareser[i]
//if it returns one, return one

//once every field_parser has be ran check that the rest of the line is empty
//or full of spaces
int	parse_object(char *line, t_object_parsing object_parsing)
{
	char*	initial_line;
	int	i;

	initial_line = line;
	i = 0;
	while (line != NULL && i < nb_fields)
	{

	}
	return (line != null && line != initial_line);
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
	{
		free(line);
		ft_exit(scene-objs, NULL, BAD_FORMAT_MSG, 1);
	}
}

//make sure the file ends in .rt
//parse file if light, camera or andambient light hasn't been serialized
//exit with parsing error
void	parse_scene(int fd, t_scene *scene)
{
	char*	line;

	scene->objs = NULL;
	scene->singleton_mask = 0;
	line = get_next_line(fd);
	while (line != null)
	{
		parse_line(line, scene);
		free(line);	
	}
	if (scene->singleton_mask & 1 == 0 ||
		 scene->singleton_mask & 2 == 0 ||
		 scene->singleton_mask & 4 == 0)
		ft_exit(scene->objs, NULL, NO_SING_MSG, 1);
}

//files: field_parsing.c, object_parsing.c, object_parsing2.c, 
