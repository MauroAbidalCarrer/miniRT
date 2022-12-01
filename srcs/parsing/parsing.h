/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 17:01:04 by maabidal          #+#    #+#             */
/*   Updated: 2022/12/01 18:49:57 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# define DUPLICATE_SING_MSG "ERROR: duplicate singleton obj!"
# define NO_SING_MSG "ERROR: .rt misses singleton obj!"
# define BAD_FORMAT_MSG "ERROR: .rt file doesn't conply to norm!"
# define ALLOCATION_ERROR_MSG "ERROR: allocation error"
# include "../libft/libft.h"
# include "../math/ft_math.h"
# include "../mlx_colors/mlx_colors.h"
# include "../scene.h"
# include "header.h"
# include "get_next_line.h"
# include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
//otherwise, returns the rest of the line after the field
//								  line,   dst,    scene objes to free
typedef char	*(* field_parser)(char *, void *, t_list *);

//parses a field(color, vector3 or float)
//calls ft_exit if there is a format error

char	*parse_vector(char *str, void *dst);
char	*parse_double(char *str, void *dst);
char 	*parse_color(char *str, void *col);
int	parse_line(char *line, char *occ, field_parser*, void *dsts, int nb_fields);
void	parse_scene(char *filename, t_scene *scene);
#endif
