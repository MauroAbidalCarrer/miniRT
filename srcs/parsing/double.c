/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 20:42:11 by maabidal          #+#    #+#             */
/*   Updated: 2022/12/03 20:50:42 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	in_range(double val, double min, double max)
{
	return (val >= min && val <= max);
}

static int	parse_decimal_in_double(char **str, double *dst)
{
	int		parsed_something;
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
	double	sign;

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
