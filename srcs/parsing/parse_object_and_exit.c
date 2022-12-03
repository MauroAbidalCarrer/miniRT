/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_object_and_exit.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 20:45:30 by maabidal          #+#    #+#             */
/*   Updated: 2022/12/03 21:16:28 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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
//returns 2 ocurence not found
//if the line starts by the ocurence but doesn't comply to the subject

//check if the line starts by the ocurence

//while field_parers[i], skip spaces run field_pareser[i]
//if it returns one, return one

//once every field_parser has be ran,
//check that the last character == '\n' or wero
int	parse_obj(char *line, t_field_parser *parsers, void **dsts, char *oc)
{
	if (!starts_by(line, oc))
		return (2);
	line += ft_strlen(oc);
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

static void	free_obj(void *obj_interface)
{
	free(((t_obj_interface *)obj_interface)->obj);
	free(obj_interface);
}

void	ft_exit(t_list *objs, char *error_msg, char *line)
{
	if (error_msg != NULL)
		ft_putstr_fd(error_msg, 1);
	ft_lstclear(&objs, &free_obj);
	free(line);
	exit(error_msg != NULL);
}
