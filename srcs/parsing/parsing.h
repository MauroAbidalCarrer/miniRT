/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 17:01:04 by maabidal          #+#    #+#             */
/*   Updated: 2022/11/30 02:49:46 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# define NO_SING_MSG "ERROR: duplicate singleton obj!"
# define DUPLICATE_SING_MSG "ERROR: .rt misses singleton obj!"
# define BAD_FORMAT_MSG "ERROR: .rt file doesn't conply to norm!"
typedef struct s_object_parsing
{
	char *occ;
	field_parser* field_parses;
	void *dsts;
	int nb_fields;
}	t_object_parsing;

//parses a field(color, vector3 or float)
//calls ft_exit if there is a format error

//otherwise, returns the rest of the line after the field
//								  line,   dst,    scene objes to free
typedef char	*(field_parser *)(char *, void *, t_list *);

char	*parse_vector(char *str, void *dst);
char	*parse_double(char *str, void *dst);
char 	*parse_color(char *str, void *col);
int	parse_line(char *line, char *occ, field_parser*, void *dsts, int nb_fields);
#endif
