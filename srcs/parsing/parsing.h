/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 17:01:04 by maabidal          #+#    #+#             */
/*   Updated: 2022/12/07 18:51:46 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# define NOT_FOUND 2
# define ERROR 1
# define FOUND_AND_NO_ERROR 0
# define NO_ERROR 0
# define SPOT_MASK 0b00000001
# define AMBIENT_MASK 0b00000010
# define CAMERA_MASK 0b00000100
# define BAD_FORMAT_MSG "ERROR: .rt file doesn't conply to norm!\n"
# include "libft.h"
# include "ft_math.h"
# include "mlx_colors.h"
# include "scene.h"
# include "header.h"
# include "get_next_line.h"
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <string.h>
# include <stdio.h>
//otherwise, returns the rest of the line after the field
//								  	line,   dst
typedef char *(*	t_field_parser)(char *, void *);
typedef int (*	t_object_parser)(char *, t_scene *);

//parses a field(color, vector3 or float)
//calls ft_exit if there is a format error

int		in_range(double val, double min, double max);
int		vector_in_range(t_vec vec, double min, double max);
char	*parse_vector(char *str, void *dst);
char	*parse_double(char *str, void *dst);
char	*parse_color(char *str, void *col);
int		parse_obj(char *line, t_field_parser *parsers, void **dsts, char *oc);
void	parse_scene(char *filename, t_scene *scene);
int		parse_spot_light(char *line, t_scene *scene);
int		parse_camera(char *line, t_scene *scene);
void	add_new_obj(char *line, t_scene *scene, void *cpy, t_ray_caster caster);
int		parse_cylinder(char *line, t_scene *scene);
int		parse_sphere(char *line, t_scene *scene);
int		parse_plane(char *line, t_scene *scene);
int		parse_ambient_light(char *line, t_scene *scene);
#endif
